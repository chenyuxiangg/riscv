#include "lock.h"
#include "riscv.h"

void spin_lock()
{
	write_mstatus(read_mstatus() & (~MSTATUS_MIE));
}

void spin_unlock()
{
	write_mstatus(read_mstatus() |  MSTATUS_MIE);
}
