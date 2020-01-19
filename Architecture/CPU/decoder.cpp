#include "..\..\Common\defines.hpp"
#include "..\..\Common\typedefs.hpp"
#include "..\..\Common\opcodes.hpp"

using namespace MSP430_Opcodes; // this has to be above the include below, otherwise compile error

#include "decoder.hpp"

namespace Decoder
{
	MSP430CPUDecoder::MSP430CPUDecoder()
	{
	}

	MSP430CPUDecoder::~MSP430CPUDecoder()
	{
	}



	uint8 MSP430CPUDecoder::decodeCurrentInstruction(uint16 programCounter, MSP430_Opcode* opcode)
	{
		bool hasImmediateSource = false, hasImmediateDestination = false;

		uint8 length = 0;

		uint16* currentProgramCounter = (uint16*)programCounter;
		uint16* currentInstruction = currentProgramCounter;

		opcode->address = programCounter;

		switch (*currentInstruction >> 13)
		{
			case 0: // single operand arithmetic 
			{
				++currentProgramCounter;

				opcode->instructionType = SINGLE_OPERAND_ARITHMETIC;

				const MSP40_Single_Operand_Arithmetic* singleOperandArithmetic = opcode->getOpcodeInformation<MSP40_Single_Operand_Arithmetic>();
			
				// written this way for verboseness

				if (singleOperandArithmetic->as == 1
					&& singleOperandArithmetic->source == 0) /* Symbolic Mode ADDR. X value stored in the
																word following the instruction word,
																where X = PC - ADDR*/
				{
					hasImmediateSource = true;
				}
				else if (singleOperandArithmetic->as == 1
					&& singleOperandArithmetic->source == 2) /* Absolute mode &ADDR. SR takes value 0,
																and works as ADDR(SR)
																ADDR follows instruction word*/
				{
					hasImmediateSource = true;
				}
				else if (singleOperandArithmetic->as == 3
					&& singleOperandArithmetic->source == 0) /* Immediate mode3 #N
																N follows the instruction word*/
				{
					hasImmediateSource = true;
				}

				if (hasImmediateSource)
				{
					opcode->sourceAddress = *currentProgramCounter;
				}

				opcode->operationType = singleOperandArithmetic->size;
			}
			break;

			case 1: // conditional
			{
				++currentProgramCounter;

				opcode->instructionType = CONDITIONAL;

				const MSP430_Conditional* conditional = opcode->getOpcodeInformation<MSP430_Conditional>();

				// todo: compute branch address
			}
			break;

			default: // two operand arithmetic
			{
				++currentProgramCounter;

				opcode->instructionType = TWO_OPERAND_ARITHMETIC;

				const MSP430_Two_Operand_Arithmetic* twoOperandArithmetic = opcode->getOpcodeInformation<MSP430_Two_Operand_Arithmetic>();
			
				// written this way for verboseness

				if (twoOperandArithmetic->as == 1
					&& twoOperandArithmetic->source == 0) /* Symbolic Mode ADDR. X value stored in the
															 word following the instruction word,
															 where X = PC - ADDR*/
				{
					hasImmediateSource = true;
				}
				else if (twoOperandArithmetic->as == 1
					&& twoOperandArithmetic->source == 2) /* Absolute mode &ADDR. SR takes value 0,
															 and works as ADDR(SR)
															 ADDR follows instruction word*/
				{
					hasImmediateSource = true;
				}
				else if (twoOperandArithmetic->as == 3
					&& twoOperandArithmetic->source == 0) /* Immediate mode3 #N
															 N follows the instruction word*/
				{
					hasImmediateSource = true;
				}

				if (hasImmediateSource)
				{
					opcode->sourceAddress = *currentProgramCounter;
				}

				if (twoOperandArithmetic->ad == 1
					&& twoOperandArithmetic->dst == 0) /*   Symbolic Mode ADDR. X value stored in the
															word following the instruction word,
															where X = PC - ADDR*/
				{
					++currentProgramCounter;

					hasImmediateDestination = true;
				}
				else if (twoOperandArithmetic->ad == 1
					&& twoOperandArithmetic->dst == 2) /*   Absolute mode &ADDR
															ADDR is last word*/
				{
					++currentProgramCounter;

					hasImmediateDestination = true;
				}

				if (hasImmediateDestination)
				{
					opcode->destinationAddress = *currentProgramCounter;
				}

				opcode->operationType = twoOperandArithmetic->size;
				
			}
			break;
		}

		length = (currentProgramCounter - currentInstruction);

		opcode->length = length;

		return length;
	}
}