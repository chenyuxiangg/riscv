#include "type.h"

#define MAX_TASK	10
#define TASK_STACK 	1024

typedef struct {
	reg_t ra;
	reg_t sp;
	reg_t gp;
	reg_t tp;
	reg_t t0;
	reg_t t1;
	reg_t t2;
	reg_t s0;
	reg_t s1;
	reg_t a0;
	reg_t a1;
	reg_t a2;
	reg_t a3;
	reg_t a4;
	reg_t a5;
	reg_t a6;
	reg_t a7;
	reg_t s2;
	reg_t s3;
	reg_t s4;
	reg_t s5;
	reg_t s6;
	reg_t s7;
	reg_t s8;
	reg_t s9;
	reg_t s10;
	reg_t s11;
	reg_t t3;
	reg_t t4;
	reg_t t5;
	reg_t t6;
} Context;
typedef Context* PContext;

typedef struct {
	Context ctx;
} Task;

typedef struct {
	uint32_t capcity;
	uint32_t size;
	uint32_t curindex;
	Task tasks[MAX_TASK];
} TaskSet;

extern TaskSet g_taskset;

void schedule_init(void);
void delay(uint32_t count);
void schedule(void);
void new_task(void* func);
void yeild(void);
