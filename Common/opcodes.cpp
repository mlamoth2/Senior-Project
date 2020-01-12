#include "opcodes.hpp"

namespace MSP430_Opcodes
{
	MnemonicsAndDescriptions instructionSetDescriptor[] = 
	{
		// Single Operand Arithmetic

		{"RRC", "", "Rotate right carry through carry"},
		{"SWPB", "", "Swap bytes"},
		{"RRA", "", "Rotate right arithmetic"},
		{"SXT", "", "Sign extend byte to word"},
		{"PUSH", "", "Push value onto stack"},
		{"CALL", "", "Subroutine call, push PC onto stack, then move source to PC"},
		{"RETI", "", "Return from interrupt, pop SR, then pop PC"},


		// Conditionals
		{"JNE", "JNZ", "Jump if not equal/zero"},
		{"JEQ", "JZ", "Jump if equal/zero"},
		{"JNC", "JL", "Jump if not carry/lower"},
		{"JC", "JHS", "Jump if carry/higher or same"},
		{"JN", "", "Jump if negative"},
		{"JGE", "", "Jump if greater than or equal"},
		{"JL", "", "Jump if less than"},
		{"JMP", "", "Jump unconditionally"},

		// Two Operand Arithmetic

		{"MOV", "", "Move source to destination"},
		{"ADD", "", "Add source to destination"},
		{"ADDC", "", "Add source and carry to destination"},
		{"SUBC", "", "Subtract source from destination (with carry))"},
		{"SUB", "", "Subtract source from destination"},
		{"CMP", "", "Compare; (dst-src); discard result"},
		{"DADD", "", "Decimal add source to destination (with carry)"},
		{"BIT", "", "Test bits of source AND destination"},
		{"BIC", "", "Bit clear; dest &= ~src"},
		{"BIS", "", "Bit set - logical OR"},
		{"XOR", "", "Exclusive or source with destination"},
		{"AND", "", "Logical AND source with destination"},
	};
}