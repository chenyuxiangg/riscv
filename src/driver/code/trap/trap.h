#ifndef TRAP_H
#define TRAP_H
#include "type.h"

void trap_init(void);
reg_t trap_handle(reg_t mepc, reg_t mcause);
#endif
