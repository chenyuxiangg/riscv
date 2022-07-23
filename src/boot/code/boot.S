#include "platform.h"

.global _start

.equ STACK_SIZE, 1024

.section .text
_start:
	csrr 	t0, mhartid
	mv	t1, t0
	bnez	t0, cpu_sleep

	la 	sp, stacks + STACK_SIZE
	slli	t1, t1, 10
	add	sp, sp, t1

	la 	a0, enter_boot_msg
	jal	uart_puts
	j	span_main

stacks:
	.skip STACK_SIZE*MAX_CPUS

cpu_sleep:
	la	a0, sleep_msg
	jal	uart_puts
	wfi
	j .

.section .rodata
	enter_boot_msg: .string "RV-Snap boot start.\n"
	sleep_msg:	.string "I`ll sleep.\n"
.end
