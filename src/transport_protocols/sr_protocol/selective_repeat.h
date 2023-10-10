#ifndef SELECTIVE_REPEAT_H
#define SELECTIVE_REPEAT_H

#include "../rdt_strategy.h"
#include "../../utils/port_handler.h"

class selective_repeat : public rdt_strategy
{
private:
    /* data */
public:
    selective_repeat(port_handler *p);
    ~selective_repeat();

    virtual void implement() = 0;
};

#endif