#ifndef COMM_H
#define COMM_H

#define READ_REG_BYTE(addr, offset, value) (value = *((unsigned char*)(addr+offset)))
#define WRITE_REG_BYTE(addr, offset, value) (*(unsigned char*)(addr+offset) = value)

#endif
