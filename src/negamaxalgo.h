/**
 * @file negamaxalgo.h
 * @brief
 * @author hulei
 * @version 1.0
 * @date 2012-03-24
 *
 * Copyright (C) 2012 Hu Lei. All rights reserved.
 */

#ifndef __NEGAMAXALGO_H__
#define __NEGAMAXALGO_H__

#include "checkerboard.h"
#include "gobangai.h"

class negamaxalgo : public gobangai
{
public:
    negamaxalgo(void);
    virtual ~negamaxalgo(void);

    virtual void set_depth(uint8_t depth);
    virtual int8_t get_result(checkerboard& board, uint8_t side);
    virtual position next_step(checkerboard& board);

private:
    uint8_t _depth;
};


#endif //__NEGAMAXALGO_H__

