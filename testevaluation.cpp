#include <iostream>
#include "evaluation.h"
#include "checkerboard.h"

//#include "testdata.h"

uint8_t g_board[15][15] = 
{
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 1, 0xff, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 1, 0xff, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 1, 0xff, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0xff, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
};

void init_checkerboard(checkerboard& board)
{
    for (int x = 0; x < 15; ++x)
    {
        for (int y = 0; y < 15; ++y)
        {
            board.setpiece(x, y, g_board[x][y]);
        }
    }
}

int main(int argc, char** argv)
{
    checkerboard& board = checkerboard::getinstance();
    init_checkerboard(board);
    cout << "black side: " << evaluate_checkerboard(board, checkerboard::PIECE_BLACK) << endl;
    cout << "white side: " << evaluate_checkerboard(board, checkerboard::PIECE_WHITE) << endl;
    return 0;
}
