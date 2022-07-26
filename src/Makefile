include ../build/comm.mk

SRC_C = ./app/code/main.c \
	./driver/code/uart/drv_uart.c \
	./driver/code/cooper_task/cooperation.c \
	./driver/code/trap/trap.c \
	./driver/code/plic/plic.c \
	./driver/code/timer/timer.c \
	./driver/code/lib/printf.c \
	./driver/code/lock/lock.c \

SRC_S = ./boot/code/boot.S \
	./driver/code/cooper_task/sche.S \

OBJS = $(SRC_S:.S=.o)
OBJS += $(SRC_C:.c=.o)

TARGET_DIR = $(ROOT_PATH)/output
TARGET_O_DIR = $(TARGET_DIR)/obj
TARGET_BIN_DIR = $(TARGET_DIR)/bin
TARGET_ASM_DIR = $(TARGET_DIR)/asm
BIN_FILE = span.elf

all:$(BIN_FILE)
	@test -d $(TARGET_DIR) && echo "$(TARGET_DIR) is existed." || mkdir -p $(TARGET_DIR)
	@test -d $(TARGET_O_DIR) && echo "$(TARGET_O_DIR) is existed." || mkdir -p $(TARGET_O_DIR)
	@test -d $(TARGET_BIN_DIR) && echo "$(TARGET_BIN_DIR) is existed." || mkdir -p $(TARGET_BIN_DIR)
	@test -d $(TARGET_ASM_DIR) && echo "$(TARGET_ASM_DIR) is existed." || mkdir -p $(TARGET_ASM_DIR)
	@find . -name "*.o" | xargs -I % sh -c "mv -v % $(TARGET_O_DIR)"
	@find . -iname "*.elf" | xargs -I % sh -c "mv -v % $(TARGET_BIN_DIR)"
	@test -e $(TARGET_BIN_DIR)/span.elf && $(OBJDUMP) -d $(TARGET_BIN_DIR)/span.elf > $(TARGET_ASM_DIR)/span.asm || echo "elf not find."

span.elf:$(OBJS)
	$(GCC) $(FLAG)$(LD_FLAG) -Ttext=0x80000000 -o span.elf $^

# it`s only need to compile,not to link,so specified -c
%.o:%.c
	$(GCC) $(FLAG) -c -o $@ $<

%.o:%.S
	$(GCC) $(FLAG) -c -o $@ $<

.PHONY:run
run:all
	@echo "Please press CTRL-A and X to exit QEMU"
	@echo "--------------------------------------"
	@$(QEMU) $(QFLAG) -kernel $(TARGET_BIN_DIR)/$(BIN_FILE)

.PHONY:clean
clean:
	rm -rf $(TARGET_DIR)
	@find . -iname "*.o" | xargs -I % sh -c "rm -v %"

.PHONY:debug
debug:all
	@$(QEMU) $(QFLAG) -s -S -kernel $(TARGET_BIN_DIR)/$(BIN_FILE) &
	@$(GDB) $(TARGET_BIN_DIR)/span.elf -q
