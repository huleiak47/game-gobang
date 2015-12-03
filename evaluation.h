/**
 * @file evaluation.h
 * @brief 五子棋估值接口
 * @author hulei
 * @version 1.0
 * @date 2012-03-24
 *
 * Copyright (C) 2012 Hu Lei. All rights reserved.
 */

#ifndef __EVALUATION_H__
#define __EVALUATION_H__

#include <stdint.h>

#include "checkerboard.h"

enum
{
    SCORE_INFINITE = 0x7fff,
};

int16_t evaluate_checkerboard(checkerboard & board, uint8_t side);

#endif //__EVALUATION_H__

