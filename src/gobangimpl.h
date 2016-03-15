/**
 * @file gobangimpl.h
 * @brief
 * @author hulei
 * @version 1.0
 * @date 2012-02-14
 */

#ifndef __GOBANGIMPL_H__
#define __GOBANGIMPL_H__

#include <stdint.h>
using namespace std;
#include <wx/wx.h>
#include "gobang.h"
#include "gobangai.h"

class GobangDialogImpl : public GobangDialog
{

protected:

    // Virtual event handlers, overide them in your derived class
    virtual void OnEraseBackground(wxEraseEvent& event);
    virtual void OnLeftDown(wxMouseEvent& event);
    virtual void OnMouseMove(wxMouseEvent& event);
    virtual void OnPaint(wxPaintEvent& event);
    virtual void OnInitDialog(wxInitDialogEvent& event);
    virtual void OnLeaveWindow(wxMouseEvent& event);
    virtual void OnTimer(wxTimerEvent& event);

public:

    GobangDialogImpl(wxWindow* parent);
    ~GobangDialogImpl();


private:
    void DrawBackground(wxDC& dc);
    void DrawCheckerboard(wxDC& dc);
    void DrawPiece(wxDC& dc, uint8_t posx, uint8_t posy, bool white);
    void game_over(int8_t);

private:
    wxBrush _brushBG;
    wxPen _penBG;
    wxBitmap _bmpBG;
    uint8_t _mousex;
    uint8_t _mousey;
    wxIcon _icon;
    wxTimer _timer;
    double _elapsed;

    gobangai* _p_gobangai;

};

#endif //__GOBANGIMPL_H__
