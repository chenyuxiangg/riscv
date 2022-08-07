#include "riscv.h"
#include "platform.h"
#include "trap.h"

extern void trap_vector(void);
extern reg_t plic_claim(void);
extern void plic_complete(reg_t);
extern void uart_recvback();
extern void uart_puts(const char*);
extern void timer_load(uint64_t);
extern void schedule(void);

void trap_init(void)
{
	write_mtvec((reg_t)trap_vector);
}

void external_handle()
{
	reg_t irq = plic_claim();
	if(irq == UART0_IRQ) {
		uart_recvback();
	}

	if(irq) {
		plic_complete(irq);
	}
}

void timer_handle()
{
	timer_load(TIMER_DEFAULT_INTERVAL);
	schedule();
}

void other_handle()
{
	uart_puts("other_handle\n");
	reg_t irq = plic_claim();
	plic_complete(irq);
}

void int_handle(reg_t mcause)
{
	uint8_t cause_code = mcause & 0xfff;
	switch(cause_code) {
		case 7:
			timer_handle();
			break;
		case 11:
			external_handle();
			break;
		default:
			other_handle();
			break;
	}
}

void exception_handle(reg_t mcause)
{
	reg_t code = mcause&0xffff;
	// Store/AMO access fault
	switch (code) {
		case 2:
			uart_puts("Illegal instruction\n");
			break;
		case 7:
			uart_puts("Store or AMO access fault\n");
			break;
		default:
			uart_puts("Other exception\n");
			break;
	}
}

reg_t trap_handle(reg_t mepc, reg_t mcause)
{
	reg_t return_pc = mepc;
	if(mcause & 0x80000000) {
		int_handle(mcause);
	} else {
		exception_handle(mcause);
	}
	return return_pc;	
}
