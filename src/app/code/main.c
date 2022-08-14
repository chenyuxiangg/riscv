#include "drv_uart.h"
#include "cooperation.h"
#include "trap.h"
#include "plic.h"
#include "timer.h"

#define NEED_LOCK
#include "lock.h"

extern int printf(const char*, ...);
uint32_t g_test_critical_cnt = 0;

void task_test0()
{
	uart_puts("task_test0 created!\n");
	while(1) {
		delay(1000);
		SPINLOCK();
		++g_test_critical_cnt;
		printf("task0 : %d\n", g_test_critical_cnt);
		SPINUNLOCK();
	}
}

void task_test1()
{
	uart_puts("task_test1 created!\n");
	while (1) {
		SPINLOCK();
		++g_test_critical_cnt;
		printf("task1 : %d\n", g_test_critical_cnt);
		SPINUNLOCK();
		delay(15000);
	}
}

void task_test2()
{
	uart_puts("task_test2 created!\n");
	while (1) {
		uart_puts("task2 is running\n");
		SPINLOCK();
		++g_test_critical_cnt;
		printf("task2 : %d\n", g_test_critical_cnt);
		SPINUNLOCK();
		yeild();
		uart_puts("task2 is rerun!\n");
		delay(10000);
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
