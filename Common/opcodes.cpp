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
			case 0: // single operand 
			{				
				unsigned int instruction = *currentInstruction;

				unsigned int bitmask = (1<<9) | (1<<8) | (1<<7);

				instruction &= bitmask;

				instruction >>= 7;

				setInstruction(instruction);

				setInstructionType(SINGLE_OPERAND_ARITHMETIC);

				const MSP40_Single_Operand* singleOperand = opcode->getOpcodeInformation<MSP40_Single_Operand>();

				if(singleOperand->as == 3)
				{
					if(singleOperand->dst == PC)
					{
						length += sizeof(uint16);

						setFlagHasSourceImmediate(true);
					}
				}
				
				setOperationType(singleOperand->size);
			}
			break;

			case 1: // conditional
			{
				unsigned int instruction = *currentInstruction;

				unsigned int bitmask = (1<<13) | (1<<12) | (1<<11) | (1<<10);

				instruction &= bitmask;

				instruction >>= 10;

				instruction -= 1;

				setInstruction(instruction);

				setInstructionType(CONDITIONAL);
			}
			break;

			default: // two operand arithmetic
			{
				unsigned int bitmask = (1<<15) | (1<<14) | (1<<13) | (1<<12);

				instruction &= bitmask;

				instruction >>= 12;

				instruction += 11;

				setInstruction(instruction);

				setInstructionType(TWO_OPERAND_ARITHMETIC);

				const MSP430_Double_Operand* doubleOperand = opcode->getOpcodeInformation<MSP430_Double_Operand>();
			
				if(doubleOperand->as == 1)
				{
					if(doubleOperand->source == SR)  // # absolute
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
				else if(doubleOperand->as == 3) // # immediate
				{
					if(doubleOperand->source == PC)
					{
						length += sizeof(uint16);

						setFlagHasSourceImmediate(true);
					}
				}

				if(doubleOperand->ad == 1)
				{
					if(doubleOperand->dst == SR) // # absolute
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
				

				setOperationType(doubleOperand->size);
			}
			break;
		}

		setLength(currentProgramCounter - start);
	}
}