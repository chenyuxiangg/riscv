#include "timer.h"
#include "riscv.h"

void timer_init(void)
{
	timer_load(TIMER_DEFAULT_INTERVAL);

	// enable mtie
	write_mie(read_mie() | MIE_MTIE);
	// enable global int
	write_mstatus(read_mstatus() | MSTATUS_MIE);
}
	
void timer_load(uint64_t interval)
{
	reg_t hartid = read_mhartid();
	MTIMERCMP(hartid) = MTIMER + interval;
}
