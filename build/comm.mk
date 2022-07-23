BUILD_PATH = /home/zyzs/code/risc-v_snap/build
CROSS_COMPILE = riscv64-unknown-elf-
INCLUDE = -I/home/zyzs/code/risc-v_snap/src/comm/include \
	  -I/home/zyzs/code/risc-v_snap/src/driver/code/cooper_task \
	  -I/home/zyzs/code/risc-v_snap/src/driver/code/uart/

FLAG = -nostdlib -fno-builtin -march=rv32ima -mabi=ilp32 -g -Wall -Werror $(INCLUDE) 
LD_FLAG = -T $(BUILD_PATH)/boot.ld 
GCC = $(CROSS_COMPILE)gcc
GDB = $(CROSS_COMPILE)gdb

QEMU = qemu-system-riscv32
QFLAG = -nographic -smp 1 -machine virt -bios none
ROOT_PATH = /home/zyzs/code/risc-v_snap
