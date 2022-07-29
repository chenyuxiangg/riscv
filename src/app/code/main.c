#include "drv_uart.h"
#include "cooperation.h"
#include "trap.h"
#include "plic.h"
#include "timer.h"

void task_test()
{
	uart_puts("task_test created!\n");
	uart_puts("I am task0\n");
	while(1) {
		uart_puts("task0 is runging...\n");
		delay(5000);
		yeild();
	}
}

void span_main(void)
{
	uart_init();
	schedule_init();
	trap_init();
	plic_init();
	timer_init();
	uart_puts("Hello, RISC-V\n");
	new_task((void*)task_test);
	schedule();
}
