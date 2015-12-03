#include "evaluation.h"
#include <cassert>
#include <cstring>
using namespace std;

static const uint8_t s_pos_value[checkerboard::BOARD_GRID][checkerboard::BOARD_GRID] =
{
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
    {0, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 0},
    {0, 1, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 2, 1, 0},
    {0, 1, 2, 3, 4, 4, 4, 4, 4, 4, 4, 3, 2, 1, 0},
    {0, 1, 2, 3, 4, 5, 5, 5, 5, 5, 4, 3, 2, 1, 0},
    {0, 1, 2, 3, 4, 5, 6, 6, 6, 5, 4, 3, 2, 1, 0},
    {0, 1, 2, 3, 4, 5, 6, 7, 6, 5, 4, 3, 2, 1, 0},
    {0, 1, 2, 3, 4, 5, 6, 6, 6, 5, 4, 3, 2, 1, 0},
    {0, 1, 2, 3, 4, 5, 5, 5, 5, 5, 4, 3, 2, 1, 0},
    {0, 1, 2, 3, 4, 4, 4, 4, 4, 4, 4, 3, 2, 1, 0},
    {0, 1, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 2, 1, 0},
    {0, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 0},
    {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};

enum
{
    TOBEANALSIS     = 0,  //已分析过的
    STWO            = 1,   //眠二
    STHREE          = 2,   //眠三
    SFOUR           = 3,   //冲四
    TWO             = 4,   //活二
    THREE           = 5,   //活三
    FOUR            = 6,   //活四
    FIVE            = 7,   //五连
    DFOUR           = 8,   //双四
    FOURT           = 9,   //四三
    DTHREE          = 10,   //三三
    NOTYPE          = 11,   //未定义
    ANALSISED       = 255,  //已分析过的
};


static uint32_t s_type_record[checkerboard::BOARD_GRID][checkerboard::BOARD_GRID][4];
static uint32_t s_type_count[2][20];
static uint8_t s_line_record[30];

static int analysis_line(uint8_t* line, uint8_t len, uint8_t piece_pos)
{
    uint8_t StoneType;
    uint8_t AnalyLine[30];
    int nAnalyPos;
    int LeftEdge, RightEdge;
    int LeftRange, RightRange;

    if (len < 5)
    {
        memset(s_line_record, ANALSISED, len);
        return 0;
    }

    nAnalyPos = piece_pos;
    memset(s_line_record, TOBEANALSIS, 30);
    memset(AnalyLine, 0x0F, 30);
    memcpy(&AnalyLine, line, len);

    len--;

    StoneType = AnalyLine[nAnalyPos];
    LeftEdge = nAnalyPos;
    RightEdge = nAnalyPos;

    while (LeftEdge > 0)
    {
        if (AnalyLine[LeftEdge - 1] != StoneType)
        {
            break;
        }
        LeftEdge--;
    }

    while (RightEdge < len)
    {
        if (AnalyLine[RightEdge + 1] != StoneType)
        {
            break;
        }
        RightEdge++;
    }

    LeftRange = LeftEdge;
    RightRange = RightEdge;

    while (LeftRange > 0)
    {
        if (AnalyLine[LeftRange - 1] != checkerboard::PIECE_NONE)
        {
            break;
        }
        LeftRange--;
    }

    while (RightRange < len)
    {
        if (AnalyLine[RightRange + 1] != checkerboard::PIECE_NONE)
        {
            break;
        }
        RightRange++;
    }

    if (RightRange - LeftRange < 4)
    {
        for (int k = LeftRange ; k <= RightRange; k++)
        {
            s_line_record[k] = ANALSISED;
        }
        return 0;
    }

    for (int k = LeftEdge; k <= RightEdge; k++)
    {
        s_line_record[k] = ANALSISED;
    }

    if (RightEdge - LeftEdge > 3)//五连
    {
        s_line_record[nAnalyPos] = FIVE;
        return FIVE;
    }


    if (RightEdge - LeftEdge == 3)//4连
    {
        bool Leftfour = false;
        if (LeftEdge > 0)
        {
            if (AnalyLine[LeftEdge - 1] == checkerboard::PIECE_NONE)
            {
                Leftfour = true;
            }
        }

        if (RightEdge < len)
        {
            if (AnalyLine[RightEdge + 1] == checkerboard::PIECE_NONE)
            {
                if (Leftfour == true)
                {
                    s_line_record[nAnalyPos] = FOUR;
                }
                else
                {
                    s_line_record[nAnalyPos] = SFOUR;
                }
            }
            else
            {
                if (Leftfour == true)
                {
                    s_line_record[nAnalyPos] = SFOUR;
                }
            }

        }
        else
        {
            if (Leftfour == true)
            {
                s_line_record[nAnalyPos] = SFOUR;
            }
        }

        return s_line_record[nAnalyPos];
    }



    if (RightEdge - LeftEdge == 2)//3连
    {
        bool LeftThree = false;
        if (LeftEdge > 0)
        {

            if (AnalyLine[LeftEdge - 1] == checkerboard::PIECE_NONE)
            {
                if (LeftEdge > 1 && AnalyLine[LeftEdge - 2] == AnalyLine[LeftEdge])
                {
                    s_line_record[LeftEdge] = SFOUR;
                    s_line_record[LeftEdge - 2] = ANALSISED;
                }
                else
                {
                    LeftThree = true;
                }
            }
            else
            {
                if (RightEdge == len || AnalyLine[RightEdge + 1] != checkerboard::PIECE_NONE)
                {
                    return false;
                }
            }
        }

        if (RightEdge < len)
        {
            if (AnalyLine[RightEdge + 1] == checkerboard::PIECE_NONE)
            {
                if (RightEdge < len - 1 && AnalyLine[RightEdge + 2] == AnalyLine[RightEdge])
                {
                    s_line_record[RightEdge] = SFOUR;
                    s_line_record[RightEdge + 2] = ANALSISED;

                }
                else
                {
                    if (LeftThree == true)
                    {
                        s_line_record[RightEdge] = THREE;
                    }
                    else
                    {
                        s_line_record[RightEdge] = STHREE;
                    }
                }
            }
            else
            {
                if (s_line_record[LeftEdge] == SFOUR)
                {
                    return s_line_record[LeftEdge];
                }
                if (LeftThree == true)
                {
                    s_line_record[nAnalyPos] = STHREE;
                }
            }

        }
        else
        {
            if (s_line_record[LeftEdge] == SFOUR)
            {
                return s_line_record[LeftEdge];
            }
            if (LeftThree == true)
            {
                s_line_record[nAnalyPos] = STHREE;
            }

        }
        return s_line_record[nAnalyPos];
    }

    if (RightEdge - LeftEdge == 1)//2连
    {
        bool Lefttwo = false;
        //bool Leftthree = false;
        if (LeftEdge > 2)
        {
            if (AnalyLine[LeftEdge - 1] == checkerboard::PIECE_NONE)
            {
                if (LeftEdge - 1 > 1 && AnalyLine[LeftEdge - 2] == AnalyLine[LeftEdge])
                {
                    if (AnalyLine[LeftEdge - 3] == AnalyLine[LeftEdge])
                    {
                        s_line_record[LeftEdge - 3] = ANALSISED;
                        s_line_record[LeftEdge - 2] = ANALSISED;
                        s_line_record[LeftEdge] = SFOUR;
                    }
                    else if (AnalyLine[LeftEdge - 3] == checkerboard::PIECE_NONE)
                    {
                        s_line_record[LeftEdge - 2] = ANALSISED;
                        s_line_record[LeftEdge] = STHREE;
                    }
                }
                else
                {
                    Lefttwo = true;
                }
            }
        }
        if (RightEdge < len)
        {
            if (AnalyLine[RightEdge + 1] == checkerboard::PIECE_NONE)
            {
                if (RightEdge + 1 < len - 1 && AnalyLine[RightEdge + 2] == AnalyLine[RightEdge])
                {
                    if (AnalyLine[RightEdge + 3] == AnalyLine[RightEdge])
                    {
                        s_line_record[RightEdge + 3] = ANALSISED;
                        s_line_record[RightEdge + 2] = ANALSISED;
                        s_line_record[RightEdge] = SFOUR;
                    }
                    else if (AnalyLine[RightEdge + 3] == checkerboard::PIECE_NONE)
                    {
                        s_line_record[RightEdge + 2] = ANALSISED;
                        if (Lefttwo == true)
                        {
                            s_line_record[RightEdge] = THREE;
                        }
                        else
                        {
                            s_line_record[RightEdge] = STHREE;
                        }
                    }

                }
                else
                {
                    if (s_line_record[LeftEdge] == SFOUR)
                    {
                        return s_line_record[LeftEdge];
                    }
                    if (s_line_record[LeftEdge] == STHREE)
                    {
                        s_line_record[LeftEdge] = THREE;
                        return s_line_record[LeftEdge];
                    }

                    if (Lefttwo == true)
                    {
                        s_line_record[nAnalyPos] = TWO;
                    }
                    else
                    {
                        s_line_record[nAnalyPos] = STWO;
                    }
                }
            }
            else
            {
                if (s_line_record[LeftEdge] == SFOUR)
                {
                    return s_line_record[LeftEdge];
                }
                if (Lefttwo == true)
                {
                    s_line_record[nAnalyPos] = STWO;
                }
            }

        }
        return s_line_record[nAnalyPos];
    }

    return 0;

}

static void analysis_horizon(checkerboard& board, uint8_t x, uint8_t y)
{
    uint8_t temp[checkerboard::BOARD_GRID];
    for (uint8_t i = 0; i < checkerboard::BOARD_GRID; i++)
    {
        temp[i] = board.getpiece(x, i);
    }
    analysis_line(temp, checkerboard::BOARD_GRID, y);

    for (uint8_t i = 0; i < checkerboard::BOARD_GRID; ++i)
    {
        if (s_line_record[i] != TOBEANALSIS)
        {
            s_type_record[x][i][0] = s_line_record[i];
        }
    }
}
static void analysis_vertical(checkerboard& board, uint8_t x, uint8_t y)
{
    uint8_t temp[checkerboard::BOARD_GRID];
    for (uint8_t i = 0; i < checkerboard::BOARD_GRID; i++)
    {
        temp[i] = board.getpiece(i, y);
    }
    analysis_line(temp, checkerboard::BOARD_GRID, x);

    for (uint8_t i = 0; i < checkerboard::BOARD_GRID; ++i)
    {
        if (s_line_record[i] != TOBEANALSIS)
        {
            s_type_record[i][y][1] = s_line_record[i];
        }
    }
}
static void analysis_left(checkerboard& board, uint8_t x, uint8_t y)
{
    uint8_t temp[checkerboard::BOARD_GRID];
    uint8_t xx, yy, k;
    if (x < y)
    {
        yy = 0;
        xx = y - x;
    }
    else
    {
        xx = 0;
        yy = x - y;
    }

    for (k = 0; k < checkerboard::BOARD_GRID; ++k)
    {
        if (xx + k >= checkerboard::BOARD_GRID || yy + k >= checkerboard::BOARD_GRID)
        {
            break;
        }
        temp[k] = board.getpiece(yy + k, xx + k);
    }
    analysis_line(temp, k, y - xx);

    for (uint8_t s = 0; s < k; ++s)
    {
        if (s_line_record[s] != TOBEANALSIS)
        {
            s_type_record[yy + s][xx + s][2] = s_line_record[s];
        }
    }
}
static void analysis_right(checkerboard& board, uint8_t x, uint8_t y)
{
    uint8_t temp[checkerboard::BOARD_GRID];
    int16_t xx, yy, k;
    if (checkerboard::BOARD_GRID - 1 - x < y)
    {
        yy = checkerboard::BOARD_GRID - 1;
        xx = y - (checkerboard::BOARD_GRID - 1) + x;
    }
    else
    {
        xx = 0;
        yy = x + y;
    }

    for (k = 0; k < checkerboard::BOARD_GRID; ++k)
    {
        if (xx + k >= checkerboard::BOARD_GRID || yy - k < 0)
        {
            break;
        }
        temp[k] = board.getpiece(yy - k, xx + k);
    }
    analysis_line(temp, k, y - xx);

    for (int16_t s = 0; s < k; ++s)
    {
        if (s_line_record[s] != TOBEANALSIS)
        {
            s_type_record[yy - s][xx + s][3] = s_line_record[s];
        }
    }
}

int16_t evaluate_checkerboard(checkerboard& board, uint8_t side)
{
    uint8_t x, y;
    memset(s_type_record, 0, sizeof(s_type_record));
    memset(s_type_count, 0, sizeof(s_type_count));
    for (x = 0; x < checkerboard::BOARD_GRID; x++)
    {
        for (y = 0; y < checkerboard::BOARD_GRID; y++)
        {
            if (board.haspiece(x, y))
            {
                if (s_type_record[x][y][0] == TOBEANALSIS)
                {
                    analysis_horizon(board, x, y);
                }
                if (s_type_record[x][y][1] == TOBEANALSIS)
                {
                    analysis_vertical(board, x, y);
                }
                if (s_type_record[x][y][2] == TOBEANALSIS)
                {
                    analysis_left(board, x, y);
                }
                if (s_type_record[x][y][3] == TOBEANALSIS)
                {
                    analysis_right(board, x, y);
                }
            }
        }
    }

    for (x = 0; x < checkerboard::BOARD_GRID; ++x)
    {
        for (y = 0; y < checkerboard::BOARD_GRID; ++y)
        {
            uint8_t piece_type = board.getpiece(x, y);
            if (piece_type != checkerboard::PIECE_NONE)
            {
                for (uint8_t k = 0; k < 4; ++k)
                {
                    uint8_t piece_index = (piece_type == checkerboard::PIECE_BLACK ? 0 : 1);
                    switch (s_type_record[x][y][k])
                    {
                    case FIVE:
                        s_type_count[piece_index][FIVE]++;
                        break;
                    case FOUR:
                        s_type_count[piece_index][FOUR]++;
                        break;
                    case SFOUR:
                        s_type_count[piece_index][SFOUR]++;
                        break;
                    case THREE:
                        s_type_count[piece_index][THREE]++;
                        break;
                    case STHREE:
                        s_type_count[piece_index][STHREE]++;
                        break;
                    case TWO:
                        s_type_count[piece_index][TWO]++;
                        break;
                    case STWO:
                        s_type_count[piece_index][STWO]++;
                        break;
                    default:
                        break;
                    }
                }
            }
        }
    }

    if (side == checkerboard::PIECE_BLACK)
    {
        if (s_type_count[0][FIVE])
        {
            return SCORE_INFINITE;
        }
        if (s_type_count[1][FIVE])
        {
            return -SCORE_INFINITE;
        }
    }
    else
    {
        if (s_type_count[1][FIVE])
        {
            return SCORE_INFINITE;
        }
        if (s_type_count[0][FIVE])
        {
            return -SCORE_INFINITE;
        }
    }


    int16_t black_value = 0;
    int16_t white_value = 0;

    if (side == checkerboard::PIECE_BLACK)
    {
        if (s_type_count[0][FOUR] > 0 || s_type_count[0][SFOUR] > 0) //黑胜
        {
            black_value += 0x1000;
        }
        else if (s_type_count[1][FOUR] > 0 || s_type_count[1][SFOUR] > 1)   //白胜
        {
            white_value += 0x1000;
        }

        if (s_type_count[0][THREE] > 0 || s_type_count[0][STHREE] > 1) //黑胜
        {
            black_value += 0x0800;
        }
        else if (s_type_count[1][THREE] > 1)
        {
            white_value += 0x0800;
        }
        else if (s_type_count[1][THREE] > 0)
        {
            white_value += 0x100;
        }
    }
    else //WHITE
    {
        if (s_type_count[1][FOUR] > 0 || s_type_count[1][SFOUR] > 0)
        {
            white_value += 0x1000;
        }
        else if (s_type_count[0][FOUR] > 0 || s_type_count[0][SFOUR] > 1)
        {
            black_value += 0x1000;
        }

        if (s_type_count[1][THREE] > 0 || s_type_count[1][STHREE] > 1)
        {
            white_value += 0x800;
        }
        else if (s_type_count[0][THREE] > 1)
        {
            black_value += 0x800;
        }
        else if (s_type_count[0][THREE] > 0)
        {
            black_value += 0x100;
        }
    }
    white_value += s_type_count[1][STHREE] * 0x0004;
    white_value += s_type_count[1][TWO] * 0x0004;
    white_value += s_type_count[1][STWO];
    black_value += s_type_count[0][STHREE] * 0x0004;
    black_value += s_type_count[0][TWO] * 0x0004;
    black_value += s_type_count[0][STWO];

    for (x = 0; x < checkerboard::BOARD_GRID; ++x)
    {
        for (y = 0; y < checkerboard::BOARD_GRID; ++y)
        {
            switch (board.getpiece(x, y))
            {
            case checkerboard::PIECE_BLACK:
                black_value += s_pos_value[x][y];
                break;
            case checkerboard::PIECE_WHITE:
                white_value += s_pos_value[x][y];
                break;
            default:
                break;
            }
        }
    }
    return side == checkerboard::PIECE_BLACK ? black_value - white_value : white_value - black_value;
}
