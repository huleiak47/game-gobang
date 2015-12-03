/**
 * @file gobangai.h
 * @brief interface of AI
 * @author hulei
 * @version 1.0
 * @date 2012-03-14
 */

#ifndef __GOBANGAI_H__
#     define __GOBANGAI_H__
#include <stdint.h>
using namespace std;
#include "checkerboard.h"

//AI is always at the white side
class gobangai
{
public:
    enum
    {
        WHITE_WIN = -1,
        BLACK_WIN = 1,
        PEACE = 0,
        UNFINISHED = 2,
    };
    virtual ~gobangai(){}
    virtual void set_depth(uint8_t depth) = 0;
    virtual int8_t get_result(checkerboard& board, uint8_t side) = 0;
    virtual position next_step(checkerboard& board) = 0;

};
#endif /* __GOBANGAI_H__ */
