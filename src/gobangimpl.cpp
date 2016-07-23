#include "gobangimpl.h"

#include <cassert>
#include <stdint.h>
#include <boost/timer.hpp>
using namespace std;

#include <wx/dcbuffer.h>

#include "checkerboard.h"
#include "recorder.h"
#include "evaluation.h"
#include "negamaxalgo.h"

GobangDialogImpl::GobangDialogImpl(wxWindow* parent) :
    GobangDialog(parent),
    _brushBG(wxColor(200, 224, 200), wxSOLID),
    _penBG(wxColor(200, 224, 200)),
    _bmpBG(),
    _mousex(0xff),
    _mousey(0xff),
#ifdef _WIN32
    _icon(wxICON(gobangicon)),
#endif
    _timer(this, 9527),
    _elapsed(0)
{
    this->SetSize(30 * (checkerboard::BOARD_GRID + 1) + 10, 30 * (checkerboard::BOARD_GRID + 1) + 20);
    this->Connect(wxEVT_TIMER, wxTimerEventHandler(GobangDialogImpl::OnTimer));
    _p_gobangai = new negamaxalgo;
}

GobangDialogImpl::~GobangDialogImpl()
{
    this->Disconnect(wxEVT_TIMER, wxTimerEventHandler(GobangDialogImpl::OnTimer));
    delete _p_gobangai;
}

void GobangDialogImpl::OnInitDialog(wxInitDialogEvent& event)
{
    wxSize size = this->GetSize();
    _bmpBG.SetHeight(size.GetHeight());
    _bmpBG.SetWidth(size.GetWidth());
    //_bmpBG.SetSize(GetSize());
    //SetIcon(_icon);
    _timer.Start(500, true);
}

void GobangDialogImpl::OnMouseMove(wxMouseEvent& event)
{
    wxPoint pos = event.GetPosition();
    uint32_t x = (pos.x + 15) / 30 - 1;
    uint32_t y = (pos.y + 15) / 30 - 1;

    if (x == _mousex && y == _mousey)
    {
        return;
    }

    if (checkerboard::posavailable(x, y))
    {
        _mousex = (uint8_t)x;
        _mousey = (uint8_t)y;
    }
    else
    {
        _mousex = _mousey = 0xff;
    }
    Refresh(false);
}

void GobangDialogImpl::OnLeaveWindow(wxMouseEvent& event)
{
    if (checkerboard::posavailable(_mousex, _mousey))
    {
        _mousex = _mousey = 0xff;
        Refresh(false);
    }
}


void GobangDialogImpl::OnPaint(wxPaintEvent& event)
{
    wxBufferedPaintDC dc(this, _bmpBG);
    //back
    DrawBackground(dc);

    dc.SetPen(*wxBLACK_PEN);
    //Checkerboard
    DrawCheckerboard(dc);

    //pieces
    checkerboard& board = checkerboard::getinstance();
    for (uint8_t x = 0; x < checkerboard::BOARD_GRID; ++x)
    {
        for (uint8_t y = 0; y < checkerboard::BOARD_GRID; ++y)
        {
            if (board.haspiece(x, y))
            {
                DrawPiece(dc, x, y, board.getpiece(x, y) == checkerboard::PIECE_WHITE);
            }
        }
    }

    dc.SetBrush(*wxTRANSPARENT_BRUSH);
    //last position
    recorder& r = ::get_recorder();
    if (!r.empty())
    {
        record& t = r.top();
        dc.DrawRectangle((t.pos.x + 1) * 30 - 14, (t.pos.y + 1) * 30 - 14, 30, 30);
    }

    //mouse position
    if (((!r.empty() && r.top().piece != checkerboard::PIECE_BLACK) || (r.empty()))
            && checkerboard::posavailable(_mousex, _mousey) && !board.haspiece(_mousex, _mousey))
    {
        dc.DrawRectangle((_mousex + 1) * 30 - 10, (_mousey + 1) * 30 - 10, 20, 20);
    }

    wxString s = wxString::Format(wxT("Elapsed: %.3f sec"), _elapsed);
    dc.DrawText(s, wxPoint(1, 1));
}

void GobangDialogImpl::OnEraseBackground(wxEraseEvent& event)
{
}

void GobangDialogImpl::DrawBackground(wxDC& dc)
{
    dc.SetBrush(_brushBG);
    dc.SetPen(_penBG);
    wxSize size = this->GetClientSize();
    dc.DrawRectangle(0, 0, size.GetWidth(), size.GetHeight());
}

void GobangDialogImpl::DrawCheckerboard(wxDC& dc)
{
    for (int i = 1; i <= checkerboard::BOARD_GRID; ++i)
    {
        dc.DrawLine(30, 30 * i, 30 * checkerboard::BOARD_GRID, 30 * i);
    }
    for (int i = 1; i <= checkerboard::BOARD_GRID; ++i)
    {
        dc.DrawLine(30 * i, 30, 30 * i, 30 * checkerboard::BOARD_GRID);
    }
}

void GobangDialogImpl::DrawPiece(wxDC& dc, uint8_t posx, uint8_t posy, bool white)
{
    if (white)
    {
        dc.SetBrush(*wxWHITE_BRUSH);
    }
    else
    {
        dc.SetBrush(*wxBLACK_BRUSH);
    }
    assert(checkerboard::posavailable(posx, posy));

    dc.DrawCircle((posx + 1) * 30 + 1, (posy + 1) * 30 + 1, 12);
}

void GobangDialogImpl::OnLeftDown(wxMouseEvent& event)
{
    wxPoint pos = event.GetPosition();
    uint32_t x = (pos.x + 15) / 30 - 1;
    uint32_t y = (pos.y + 15) / 30 - 1;

    recorder& r = ::get_recorder();
    if (((!r.empty() && r.top().piece != checkerboard::PIECE_BLACK) || (r.empty()))
            && checkerboard::posavailable(x, y) && !checkerboard::getinstance().haspiece(x, y))
    {
        checkerboard::getinstance().setpiece(x, y, checkerboard::PIECE_BLACK);
        r.push(record(x, y, checkerboard::PIECE_BLACK));
        this->Refresh(false);
        _timer.Start(500, true);
    }
}

void GobangDialogImpl::game_over(int8_t ret)
{
    wxString msg;
    switch (ret)
    {
    case gobangai::BLACK_WIN:
        msg = wxT("Black Win!");
        break;
    case gobangai::PEACE:
        msg = wxT("Draw!");
        break;
    case gobangai::WHITE_WIN:
        msg = wxT("White Win!");
        break;
    default:
        assert(0);
        break;
    }
    wxMessageBox(msg);
    checkerboard::getinstance().clearall();
    while (!::get_recorder().empty())
    {
        ::get_recorder().pop();
    }
    _elapsed = 0.0;
}

void GobangDialogImpl::OnTimer(wxTimerEvent& event)
{
    int8_t ret = _p_gobangai->get_result(checkerboard::getinstance(), checkerboard::PIECE_BLACK);
    if (ret != gobangai::UNFINISHED)
    {
        game_over(ret);
        this->Refresh(false);
    }
    else
    {
        checkerboard& boarder = checkerboard::getinstance();
        boost::timer t;
        position pos = _p_gobangai->next_step(boarder);
        _elapsed = t.elapsed();
        checkerboard::getinstance().setpiece(pos, checkerboard::PIECE_WHITE);
        ::get_recorder().push(record(pos, checkerboard::PIECE_WHITE));
        this->Refresh(false);
        int8_t ret = _p_gobangai->get_result(boarder, checkerboard::PIECE_WHITE);

        if (ret != gobangai::UNFINISHED)
        {
            game_over(ret);
            this->Refresh(false);
        }
    }
}
