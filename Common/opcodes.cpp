#include "defines.hpp"
#include "typedefs.hpp"
#include "operands.hpp"
#include "opcodes.hpp"

using namespace MSP430_Operands;

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
		unsigned int* currentInstruction = (unsigned int*)getAddress();
		unsigned int* start = (unsigned int*)getAddress();

		uint8 length = sizeof(uint16);
				
		switch (*currentInstruction >> 13)
		{
			case 0: // single operand arithmetic 
			{				
				setInstructionType(SINGLE_OPERAND_ARITHMETIC);

				const MSP40_Single_Operand_Arithmetic* singleOperandArithmetic = opcode->getOpcodeInformation<MSP40_Single_Operand_Arithmetic>();

				if(singleOperandArithmetic->as == 3)
				{
					if(singleOperandArithmetic->dst == PC)
					{
						length += sizeof(uint16);

						setFlagHasSourceImmediate(true);
					}
				}
				
				setOperationType(singleOperandArithmetic->size);
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
			
				if(twoOperandArithmetic->as == 1)
				{
					if(twoOperandArithmetic->as == 1)
					{
						if(twoOperandArithmetic->source == SR)  // # absolute
						{
							length += sizeof(uint16);

							setFlagHasSourceImmediate(true);
						}
						else // # relative
						{
							length += sizeof(uint16);

							setFlagHasSourceImmediate(true);
						}
					}
				}
				else if(twoOperandArithmetic->as == 3)
				{
					if(twoOperandArithmetic->source == PC)
					{
						length += sizeof(uint16);

						setFlagHasSourceImmediate(true);
					}
				}

				if(twoOperandArithmetic->ad == 1)
				{
					if(twoOperandArithmetic->dst == SR) // # absolute
					{
						length += sizeof(uint16);

						setFlagHasDestinationAddress(true);
					}
					else // # relative
					{
						length += sizeof(uint16);

						setFlagHasDestinationAddress(true);
					}
				}
				

				setOperationType(twoOperandArithmetic->size);
			}
			break;
		}

		setLength(currentProgramCounter - start);
	}
}