#pragma once

namespace MSP430_Opcodes
{

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
		short offset : 10; // 10 bit signed offset -1024 to 1023
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
		char instructionType : 2; // single operand, conditional, two operand

		char operationType : 1; // word = 0, byte = 1

		uint16 address;
		uint8 length;
		

		union
		{
			uint8 sourceAddress;
			uint16 sourceAddress;

			uint8 destinationAddress;
			uint16 destinationAddress;
		};

		union
		{
			uint8 immediate;
			uint16 immediate;
		};

		// could used lambda?

		template <typename T> 
		T* getOpcodeInformation()
		{
			return reinterpret_cast<T*>(address);
		}

		void setAddress(uint16 address)
		{
			this->address = address;
		}

		uint16 getAddress()
		{
			return address;
		}

		void setLength(uint16 length)
		{
			this->length = length;
		}

		uint16 getLength()
		{
			return length;
		}

		void setInstructionType(char instructionType)
		{
			this->instructionType = instructionType;
		}

		char getInstructionType()
		{
			return instructionType;
		}

		void setOperationType(char operationType)
		{
			this->operationType = operationType;
		}

		char getOperationType()
		{
			return operationType;
		}

		void setSourceAddress(uint16 sourceAddress)
		{
			this->sourceAddress = sourceAddress;
		}

		uint16 getSourceAddress()
		{
			return sourceAddress;
		}

		void setDestinationAddress(uint16 destinationAddress)
		{
			this->destinationAddress = destinationAddress;
		}

		uint16 getdestinationAddress()
		{
			return destinationAddress;
		}

		void setImmediate(uint16 immediate)
		{
			this->immediate = immediate;
		}

		uint16 getImmediate()
		{
			return immediate;
		}

	}MSP430_Opcode;

	typedef struct
	{
		const char* mnemonic;
		const char* altMnemonic;
		const char* description;
	}MnemonicsAndDescriptions;
		
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

		// CALL: Subroutine call, push PC onto stack, then move source to PC
		CALL,

		// RETI: Return from interrupt, pop SR, then pop PC
		RETI,

		//
		// Conditionals
		//

		// JNZ/JNE: Jump if not equal/zero
		JNZ,
		JNE = 7,

		// JEQ/JZ: Jump if equal/zero
		JEQ,
		JZ = 8,

		// JNC/JLO: Jump if not carry/lower
		JNC,
		JLO = 9,

		// JC/JHS: Jump if carry/higher or same
		JC,
		JHS = 10,

		// JN: Jump if negative
		JN,

		// JGE: Jump if greater than or equal
		JGE,

		// JL: Jump if less than
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

		// ADDC: Add source and carry to destination
		ADDC,

		// SUBC: Subtract source from destination (with carry)
		SUBC,

		// SUB: Subtract source from destination; dst -= src
		SUB,

		// CMP: Compare; (dst-src); discard result
		CMP,

		// DADD: Decimal add source to destination (with carry)
		DADD,

		// BIT: Test bits; (dst & src); discard result
		BIT,

		// BIC: Bit clear; dest &= ~src
		BIC,

		// BIS: Bit set - logical OR
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
		// ADC: Add carry to destination
		ADC = 27, // arbitrary(?)

		// BR: 	Branch to destination
		BR,

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
};