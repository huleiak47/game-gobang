/**
 * @file recorder.cpp
 * @brief 
 * @author hulei
 * @version 1.0
 * @date 2012-03-14
 */
#include "recorder.h"

static recorder s_recorder;

recorder& get_recorder(void)
{
    return s_recorder;
}
