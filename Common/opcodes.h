#pragma once

namespace MSP430_Opcodes
{
	#define SINGLE_OPERAND 0
	#define CONDITIONAL 1
	#define TWO_BYTE_OPERAND 2
	#define EMULATED 3

	// define bit fields for the struct

	typedef struct
	{
		char unused : 6;
		char opcode : 3;
		char size : 1;  // Byte or word operation: 0: word operation 1: byte operation
		char as : 2; // The addressing bits responsible for the addressing mode used for the source (src)
		char source : 4; // The source operand defined by As and S-reg
	}MSP40_Single_Operand_Arithmetic;

	typedef struct
	{
		char unused : 3;
		char condition : 3; 
		char offset : 10; // 10 bit signed offset -1024 to 1023
	}MSP430_Conditional;

	typedef struct
	{
		char opcode : 4;
		char source : 4; // The source operand defined by As and S-reg
		char ad : 1; // The addressing bits responsible for the addressing mode used for the destination (dst)
		char size : 1; // Byte or word operation: 0: word operation 1: byte operation
		char as : 2; // The addressing bits responsible for the addressing mode used for the source (src)
		char dst : 4; // The destination operand defined by Ad and D-reg
	}MSP430_Two_Operand_Arithmetic;

	typedef struct
	{
		int type : 2;
		uint16 address;

		// could used lambda?

		template <typename T> 
		T* getOpcodeInformation(uint16_t address)
		{
			return <reinterpret_cast><T*>(address);
		}


	}MSP430_Opcode;

	// Finish this later

	char* Mnemonics[] = 
	{
		// Single Operand Arithmetic

		{"RRC"},
		{"SWPB"},
		{"RRA"},
		{"SXT"},
		{"PUSH"},
		{"CALL"},
		{"RETI"}

		// Conditionals

	};

	enum Opcodes
	{
		//
		// Single Operand Arithmetic
		//

		// RRC: Rotate right carry through carry
		RRC = 0,

		// SWPB: Swap bytes
		SWPB,

		// RRA: Rotate right arithmetic
		RRA,

		// SXT: Sign extend byte to word
		SXT,

		// PUSH: Push value onto stack
		PUSH,

		// CALL: Subroutine call, push pc onto stack, then move source to pc
		CALL,

		// RETI: Return from interrupt, pop sr, then pop pc
		RETI,

		//
		// Conditionals
		//

		// JNZ/JNE: Jump if not equal or jump if not zero
		JNZ,

		// JEQ/JZ: Jump if equal or jump if zero
		JEQ,

		// JNC/JLO: Jump if not carry or jump if lower
		JNC,

		// JC/JHS: Jump if carry or jump if higher or same
		JC,

		// JN: Jump if negative
		JN,

		// JGE: Jump if greater than or equal(N == V)
		JGE,

		// JL: Jump if less than (N != V)
		JL,

		// JMP: Jump unconditionally
		jmp,

		//
		// Two Operand Arithmetic
		//

		// MOV: Move source to destination 
		MOV,

		// ADD: Add source to destination
		ADD,

		// ADDC: Add w/carry: dst += (src+C) 
		ADDC,

		// SUBC: Subtract w/ carry: dst -= (src+C)
		SUBC,

		// SUB: Subtract; dst -= src
		SUB,

		// CMP: Compare; (dst-src); discard result
		CMP,

		// DADD: Decimal (BCD) addition: dst += src
		DADD,

		// BIT: Test bits; (dst & src); discard result
		BIT,

		// BIC: Bit clear; dest &= ~src
		BIC,

		// BIS: "Bit set" - logical OR; dst |= src
		BIS,

		// XOR: Bitwise XOR; dst ^= src
		XOR,

		// AND: Bitwise AND; dst &= src
		AND

		/*
			Emulated instructions:
			
			These instructions are meant for the assembler, not the disassembler/debugger.
			If we want to recognize them in the disassembler/debugger, then
			we simply define certain MSP430 instruction patterns as idioms and replace the output as necessary
			while preserving the physical diassembly

		
			ADC.x dst ADDC.x #0,dst add carry to destination
			CLRC BIC #1,SR clear carry bit 0xc312
			CLRN BIC #4,SR clear negative bit 0xc222
			CLRZ BIC #2,SR clear zero bit 0xc322
			DADC.x dst DADD.x #0,dst decimal add carry to destination
			DEC.x dst SUB.x #1,dst decrement
			DECD.x dst SUB.x #2,dst double decrement
			DINT BIC #8,SR disable interrupts 0xc232
			EINT BIS #8,SR enable interrupts 0xd232
			INC.x dst ADD.x #1,dst increment
			INCD.x dst ADD.x #2,dst double increment
			INV.x dst XOR.x #−1,dst invert
			NOP MOV #0,R3 no operation 0x4303
			POP dst MOV @SP+,dst pop from stack
			RET MOV @SP+,PC return from subroutine 0x4130
			RLA.x dst ADD.x dst,dst rotate left arithmetic (shift left 1 bit)
			RLC.x dst ADDC.x dst,dst rotate left through carry
			SBC.x dst SUBC.x #0,dst subtract borrow (1−carry) from destination
			SETC BIS #1,SR set carry bit 0xd312
			SETN BIS #4,SR set negative bit 0xd222
			SETZ BIS #2,SR set zero bit 0xd322
			TST.x dst CMP.x #0,dst test destination
		
		*/

	};
};