#include "drv_uart.h"
#include "cooperation.h"
#include "trap.h"
#include "plic.h"
#include "timer.h"

void task_test0()
{
	uart_puts("task_test0 created!\n");
	while(1) {
		uart_puts("task0 is runging...\n");
		delay(5000);
	}
}

void task_test1()
{
	uart_puts("task_test1 created!\n");
	while (1) {
		uart_puts("task1 is running\n");
		delay(5000);
	}
}

void task_test2()
{
	uart_puts("task_test2 created!\n");
	while (1) {
		uart_puts("task2 is running\n");
		uart_puts("task2 is yeild....\n");
		yeild();
		delay(5000);
		uart_puts("task2 is rerun!\n");
	}
}

void span_main(void)
{
	uart_init();
	uart_puts("Hello, RISC-V\n");

	trap_init();
	plic_init();
	schedule_init();
	timer_init();
	new_task((void*)task_test0);
	new_task((void*)task_test1);
	new_task((void*)task_test2);
	schedule();
}
