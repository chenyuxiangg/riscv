#ifndef TIMER_H
#define TIMER_H
#include "type.h"
#include "clint.h"

void timer_init(void);
void timer_load(uint64_t interval);

#endif
