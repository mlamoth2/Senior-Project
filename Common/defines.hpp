#pragma once

#define CACHE_LINE_SIZE 128

#define SINGLE_OPERAND 0
#define CONDITIONAL 1
#define DOUBLE_OPERAND 2
#define EMULATED 3

#define WORD_OPERATION 0
#define BYTE_OPERATION 1

#define REGISTER_PC 0
#define REGISTER_SP 1
#define REGISTER_SR 2
#define REGISTER_CONST 3

#define USE_L1 (1<<0)
#define USE_L2 (1<<1)
#define USE_L3 (1<<2)
#define USE_L2_AND_L3 USE_L2 | USE_L3

#define L1 0
#define L2 1
#define L3 2

#define CACHE_READ (1<<0)
#define CACHE_WRITE (1<<1)

#define MAX_REGISTERS 16

#define PC 0
#define SR 2
#define CG 3

enum
{
	R0 = 0,
	R1,
	R2,
	R3,
	R4,
	R5,
	R6,
	R7,
	R8,
	R9,
	R10,
	R11,
	R12,
	R13,
	R14,
	R15
};