#include "cooperation.h"
#define STACK_SIZE 1024

uint8_t g_task_stack[STACK_SIZE];
Context g_task_ctx;

extern void switch_to(PContext ctx_ptr);

void write_mscratch(uint32_t val)
{
	asm volatile("csrw mscratch,%0" : : "r"(val));
}

void schedule_init(void)
{
	write_mscratch(0);
}

void delay(uint32_t count)
{
	count *= 50000;
	while(count--);
}

void schedule(void)
{
	PContext next = &g_task_ctx;
	switch_to(next);
	next = 0;
}

void new_task(void* func)
{
	g_task_ctx.sp = (reg_t)&g_task_stack[STACK_SIZE-1];
	g_task_ctx.ra = (reg_t)func;
}
