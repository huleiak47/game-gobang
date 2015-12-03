#include "negamaxalgo.h"
#include "evaluation.h"
#include "checkerboard.h"


negamaxalgo::negamaxalgo(void): _depth(2)
{
}

negamaxalgo::~negamaxalgo(void)
{
}

void negamaxalgo::set_depth(uint8_t depth)
{
    if (depth > 0)
    {
        _depth = depth;
    }
}

struct search_result
{
    int16_t value;
    position pos;
};

search_result nega_search(checkerboard& board, uint8_t depth, uint8_t side)
{
    search_result ret;
    search_result best;
    best.value = -(SCORE_INFINITE) - 1;
    best.pos.x = 0xff;
    best.pos.y = 0xff;

    if (depth == 0)
    {
        best.value = evaluate_checkerboard(board, side);
    }
    else
    {
        for (uint8_t x = 0; x < checkerboard::BOARD_GRID; ++x)
        {
            for (uint8_t y = 0; y < checkerboard::BOARD_GRID; ++y)
            {
                if (!board.haspiece(x, y))
                {
                    board.setpiece(x, y, side);
                    ret = nega_search(board, depth - 1, side == checkerboard::PIECE_BLACK ? checkerboard::PIECE_WHITE : checkerboard::PIECE_BLACK);
                    ret.value = -ret.value;
                    board.clear(x, y);
                    if (ret.value >= SCORE_INFINITE)
                    {
                        ret.pos.x = x;
                        ret.pos.y = y;
                        return ret;
                    }
                    else if (ret.value > best.value)
                    {
                        best.value = ret.value;
                        best.pos.x = x;
                        best.pos.y = y;
                    }
                }
            }
        }
        if (best.pos.x == 0xff)
        {
            best.value = 0;
        }
    }
    return best;
}


int8_t negamaxalgo::get_result(checkerboard& board, uint8_t side)
{
    for (uint8_t x = 0; x < checkerboard::BOARD_GRID; ++x)
    {
        for (uint8_t y = 0; y < checkerboard::BOARD_GRID; ++y)
        {
            if (board.getpiece(x, y) == checkerboard::PIECE_NONE)
            {
                int16_t score = evaluate_checkerboard(board, side);
                if (score >= SCORE_INFINITE)
                {
                    return side == checkerboard::PIECE_BLACK ? gobangai::BLACK_WIN : gobangai::WHITE_WIN;
                }
                else if (score <= -SCORE_INFINITE)
                {
                    return side == checkerboard::PIECE_BLACK ? gobangai::WHITE_WIN : gobangai::BLACK_WIN;
                }
                else
                {
                    return gobangai::UNFINISHED;
                }
            }
        }
    }
    return gobangai::PEACE;
}

position negamaxalgo::next_step(checkerboard& board)
{
    search_result ret = nega_search(board, this->_depth, checkerboard::PIECE_WHITE);
    assert(checkerboard::posavailable(ret.pos.x, ret.pos.y));
    return ret.pos;
}

