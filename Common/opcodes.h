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
			return reinterpret_cast<T*>(address);
		}


	}MSP430_Opcode;

	const char* Mnemonics[] = 
	{
		// Single Operand Arithmetic

		{"RRC"},
		{"SWPB"},
		{"RRA"},
		{"SXT"},
		{"PUSH"},
		{"CALL"},
		{"RETI"},


		// Conditionals
		{"JNE"},
		{"JEQ"},
		{"JNC"},
		{"JC"},
		{"JN"},
		{"JGE"},
		{"JL"},
		{"JMP"},

		// Two Operand Arithmetic

		{"MOV"},
		{"ADD"},
		{"ADDC"},
		{"SUBC"},
		{"SUB"},
		{"CMP"},
		{"DADD"},
		{"BIT"},
		{"BIC"},
		{"BIS"},
		{"XOR"},
		{"AND"},
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
		JMP,

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

		

	};

	/*
		Emulated instructions:
			
		These instructions are meant for the assembler, not the disassembler/debugger.
		If we want to recognize them in the disassembler/debugger, then
		we simply define certain MSP430 instruction patterns as idioms and replace the output as necessary
		while preserving the physical diassembly
	*/

	enum OpcodesEmulated
	{
		ADC = 27, // arbitrary(?)

		CLRC,

		CLRN,

		CLRZ,

		DADC,

		DEC,

		DECD,

		DINT,

		EINT,

		INC,

		INCD,

		INV,

		NOP,

		POP,

		RET,

		RLA,

		RLC,

		SBC,

		SETC,

		SETN,

		SETZ,

		TST
	};

	const char* MnemonicsEmulated[] = 
	{
		{""},
	};
};