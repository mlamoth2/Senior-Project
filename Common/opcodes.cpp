#include "defines.hpp"
#include "typedefs.hpp"
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

	uint8 MSP430_Opcode::initialize()
	{
		uint8 currentLength = sizeof(uint16);

		uint16* currentInstruction = (uint16*)getAddress();
				
		switch (*currentInstruction >> 13)
		{
			case 0: // single operand arithmetic 
			{				
				setInstructionType(SINGLE_OPERAND_ARITHMETIC);

				const MSP40_Single_Operand_Arithmetic* singleOperandArithmetic = opcode->getOpcodeInformation<MSP40_Single_Operand_Arithmetic>();

				if (singleOperandArithmetic->as == 1
					&& singleOperandArithmetic->source == 0)
				{
					setFlagHasSourceAddress(true);
				}
				else if (singleOperandArithmetic->as == 1
					&& singleOperandArithmetic->source == 2)
				{
					setFlagHasSourceAddress(true);
				}

				else if (singleOperandArithmetic->as == 3
					&& singleOperandArithmetic->source == 0)
				{
					setFlagHasSourceImmediate(true);
				}

				if (getFlagHasSourceAddress() || getFlagHasSourceImmediate())
				{
					currentLength += sizeof(uint16);
				}

				setOperationType(twoOperandArithmetic->size);
			}
			break;

			case 1: // conditional
			{
				setInstructionType(CONDITIONAL);
			}
			break;

			default: // two operand arithmetic
			{
				setInstructionType(TWO_OPERAND_ARITHMETIC);

				const MSP430_Two_Operand_Arithmetic* twoOperandArithmetic = opcode->getOpcodeInformation<MSP430_Two_Operand_Arithmetic>();
			
				if (twoOperandArithmetic->as == 1
					&& twoOperandArithmetic->source == 0)
				{
					setFlagHasSourceAddress(true);
				}
				else if (twoOperandArithmetic->as == 1
					&& twoOperandArithmetic->source == 2)
				{
					setFlagHasSourceAddress(true);
				}
				else if (twoOperandArithmetic->as == 3
					&& twoOperandArithmetic->source == 0)
				{
					setFlagHasSourceImmediate(true);
				}

				if (getFlagHasSourceAddress() || getFlagHasSourceImmediate())
				{
					currentLength += sizeof(uint16);
				}

				if (getFlagHasSourceAddress())
				{
					opcode->setSourceAddress(*currentProgramCounter);
				}
				else if (getFlagHasSourceImmediate())
				{
					opcode->setImmediate(*currentProgramCounter);
				}

				if (twoOperandArithmetic->ad == 1
					&& twoOperandArithmetic->dst == 0)
				{
					++currentProgramCounter;

					setFlaghasDestinationAddress(true);
				}
				else if (twoOperandArithmetic->ad == 1
					&& twoOperandArithmetic->dst == 2)
				{
					++currentProgramCounter;

					setFlaghasDestinationAddress(true);
				}

				if (getFlagHasDestinationAddress())
				{
					currentLength += sizeof(uint16);
				}

				setOperationType(twoOperandArithmetic->size);
			}
			break;
		}

		setLength(currentLength);
	}
}