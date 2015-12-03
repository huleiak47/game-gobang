/**
 * @file recorder.h
 * @brief recorder
 * @author hulei
 * @version 1.0
 * @date 2012-03-14
 */

#ifndef __RECORDER_H__
#define __RECORDER_H__
#include <stdint.h>
#include <stack>
using namespace std;
#include "checkerboard.h"

struct record
{
    position pos;
    uint8_t piece;

    record(uint8_t r, uint8_t c, uint8_t p): piece(p) 
    {
        pos.x = r;
        pos.y = c;
    }

    record(position _pos, uint8_t p): pos(_pos), piece(p) {}
};

typedef stack<record> recorder;

recorder& get_recorder(void);

#endif /* __RECORDER_H__ */
