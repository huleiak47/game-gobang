#ifndef __CHECKERBOARD_H__
#define __CHECKERBOARD_H__

#include <stdint.h>
#include <cstring>
#include <cassert>
using namespace std;

struct position
{
    uint8_t x;
    uint8_t y;
};

#define check_positon(x, y) assert((x) < BOARD_GRID && (y) < BOARD_GRID)

class checkerboard
{
public:
    enum
    {
        BOARD_GRID = 15,
        PIECE_BLACK = 1,
        PIECE_WHITE = 0xff,
        PIECE_NONE = 0,
    };

    ~checkerboard(void) {}

    static checkerboard& getinstance(void)
    {
        return checkerboard::_checkerboard;
    }

    static bool posavailable(uint32_t x, uint32_t y)
    {
        return (bool)(x < BOARD_GRID && y < BOARD_GRID);
    }

    uint8_t getpiece(uint8_t x, uint8_t y)
    {
        check_positon(x, y);
        return _board[x][y];
    }

    uint8_t getpiece(position pos)
    {
        return getpiece(pos.x, pos.y);
    }

    void setpiece(uint8_t x, uint8_t y, uint8_t piece)
    {
        check_positon(x, y);
        assert(piece == PIECE_BLACK || piece == PIECE_NONE || piece == PIECE_WHITE);
        _board[x][y] = piece;
    }

    void setpiece(position pos, uint8_t piece)
    {
        setpiece(pos.x, pos.y, piece);
    }

    bool haspiece(uint8_t x, uint8_t y)
    {
        check_positon(x, y);
        return _board[x][y] != PIECE_NONE;
    }

    bool haspiece(position pos)
    {
        return haspiece(pos.x, pos.y);
    }

    void clear(uint8_t x, uint8_t y)
    {
        check_positon(x, y);
        _board[x][y] = PIECE_NONE;
    }

    void clear(position pos)
    {
        clear(pos.x, pos.y);
    }

    void clearall(void)
    {
        std::memset(_board, PIECE_NONE, sizeof(_board));
    }

private:
    checkerboard(void)
    {
        clearall();
    }

private:
    uint8_t _board[BOARD_GRID][BOARD_GRID];
    static checkerboard _checkerboard;
};

#endif
