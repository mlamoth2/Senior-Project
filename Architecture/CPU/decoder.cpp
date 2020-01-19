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
		bool hasSourceAddress = false, hasDestinationAddress = false, hasSourceImmediate = false;

		uint8 length = 0;

		uint16* currentProgramCounter = (uint16*)programCounter;
		uint16* currentInstruction = currentProgramCounter;

		opcode->setAddress(programCounter);

		switch (*currentInstruction >> 13)
		{
			case 0: // single operand arithmetic 
			{
				++currentProgramCounter;

				opcode->setInstructionType(SINGLE_OPERAND_ARITHMETIC);

				const MSP40_Single_Operand_Arithmetic* singleOperandArithmetic = opcode->getOpcodeInformation<MSP40_Single_Operand_Arithmetic>();
			
				// written this way for verboseness

				if (singleOperandArithmetic->as == 1
					&& singleOperandArithmetic->source == 0) /* Symbolic Mode ADDR. X value stored in the
																word following the instruction word,
																where X = PC - ADDR*/
				{
					hasSourceAddress = true;
				}
				else if (singleOperandArithmetic->as == 1
					&& singleOperandArithmetic->source == 2) /* Absolute mode &ADDR. SR takes value 0,
																and works as ADDR(SR)
																ADDR follows instruction word*/
				{
					hasSourceAddress = true;
				}
				else if (singleOperandArithmetic->as == 3
					&& singleOperandArithmetic->source == 0) /* Immediate mode3 #N
																N follows the instruction word*/
				{
					hasSourceImmediate = true;
				}

				if (hasSourceAddress)
				{
					opcode->setSourceAddress(*currentProgramCounter);
				}
				else if (hasSourceImmediate)
				{
					opcode->setImmediate(*currentProgramCounter);
				}

				opcode->setOperationType(singleOperandArithmetic->size);
			}
			break;

			case 1: // conditional
			{
				++currentProgramCounter;

				opcode->setInstructionType(CONDITIONAL);

				const MSP430_Conditional* conditional = opcode->getOpcodeInformation<MSP430_Conditional>();

				// todo: compute branch address
			}
			break;

			default: // two operand arithmetic
			{
				++currentProgramCounter;

				opcode->setInstructionType(TWO_OPERAND_ARITHMETIC);

				const MSP430_Two_Operand_Arithmetic* twoOperandArithmetic = opcode->getOpcodeInformation<MSP430_Two_Operand_Arithmetic>();
			
				// written this way for verboseness

				if (twoOperandArithmetic->as == 1
					&& twoOperandArithmetic->source == 0) /* Symbolic Mode ADDR. X value stored in the
															 word following the instruction word,
															 where X = PC - ADDR*/
				{
					hasSourceAddress = true;
				}
				else if (twoOperandArithmetic->as == 1
					&& twoOperandArithmetic->source == 2) /* Absolute mode &ADDR. SR takes value 0,
															 and works as ADDR(SR)
															 ADDR follows instruction word*/
				{
					hasSourceAddress = true;
				}
				else if (twoOperandArithmetic->as == 3
					&& twoOperandArithmetic->source == 0) /* Immediate mode3 #N
															 N follows the instruction word*/
				{
					hasSourceImmediate = true;
				}

				if (hasSourceAddress)
				{
					opcode->setSourceAddress(*currentProgramCounter);
				}
				else if (hasSourceImmediate)
				{
					opcode->setImmediate(*currentProgramCounter);
				}

				if (twoOperandArithmetic->ad == 1
					&& twoOperandArithmetic->dst == 0) /*   Symbolic Mode ADDR. X value stored in the
															word following the instruction word,
															where X = PC - ADDR*/
				{
					++currentProgramCounter;

					hasDestinationAddress = true;
				}
				else if (twoOperandArithmetic->ad == 1
					&& twoOperandArithmetic->dst == 2) /*   Absolute mode &ADDR
															ADDR is last word*/
				{
					++currentProgramCounter;

					hasDestinationAddress = true;
				}

				if (hasDestinationAddress)
				{
					opcode->setDestinationAddress(*currentProgramCounter);
				}

				opcode->setOperationType(twoOperandArithmetic->size);
				
			}
			break;
		}

		length = (currentProgramCounter - currentInstruction);

		opcode->setLength() = length;

		return length;
	}
}