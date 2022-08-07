#include "riscv.h"
#include "cooperation.h"

uint8_t g_task_stacks[MAX_TASK][TASK_STACK];
TaskSet g_taskset = {
	.capcity = MAX_TASK,
	.size 	= 0,
	.curindex = -1
};

extern void switch_to(PContext ctx_ptr);

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
	if (g_taskset.size <= 0) {
		return;
	}
	g_taskset.curindex = (g_taskset.curindex+1)%g_taskset.size;
	switch_to(&(g_taskset.tasks[g_taskset.curindex].ctx));
}

void new_task(void* func)
{
	if (g_taskset.size+1 >= g_taskset.capcity) {
		return;
	}
	g_taskset.tasks[g_taskset.size].ctx.sp = (reg_t)&g_task_stacks[g_taskset.size][TASK_STACK-1];
	g_taskset.tasks[g_taskset.size].ctx.pc = (reg_t)func;
	g_taskset.size++;
}

void yeild(void)
{
	schedule();
}
