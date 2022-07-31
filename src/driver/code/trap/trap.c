#include "riscv.h"
#include "platform.h"
#include "trap.h"

extern void trap_vector(void);
extern reg_t plic_claim(void);
extern void plic_complete(reg_t);
extern void uart_recvback();
extern void uart_puts(const char*);
extern void timer_load(uint64_t);

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
	uart_puts("timer triger!\n");
	timer_load(TIMER_DEFAULT_INTERVAL);
}

void other_handle()
{
	uart_puts("other triger!\n");
	reg_t irq = plic_claim();
	plic_complete(irq);
}

void int_handle(reg_t mepc, reg_t mcause)
{
	(void)mepc;
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

void exception_handle(reg_t mepc, reg_t mcause)
{
	// Store/AMO access fault
	if((mcause&0x7fffffff) == 7) {
		uart_puts("Store or AMO access fault\n");
		mepc += 4;
		write_mepc(mepc);
	}
}

void trap_handle(reg_t mepc, reg_t mcause)
{
	if(mcause & 0x80000000) {
		int_handle(mepc, mcause);
	} else {
		exception_handle(mepc, mcause);
	}	
}
