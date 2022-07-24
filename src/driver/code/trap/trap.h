#ifndef TRAP_H
#define TRAP_H
#include "type.h"

void trap_init(void);
void trap_handle(reg_t mepc, reg_t mcause);
#endif
