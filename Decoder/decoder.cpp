#include "..\Common\typedefs.hpp"
#include "..\Common\opcodes.hpp"

using namespace MSP430_Opcodes; // this has to be above the include below, otherwise compile error

#include "decoder.hpp"

namespace Decoder
{
	MSP430Decoder::MSP430Decoder()
	{
	}

	MSP430Decoder::~MSP430Decoder()
	{
	}

	// todo: add some sort of garbage collection
	MSP430_Opcode* MSP430Decoder::decodeCurrentInstruction(uint16 programCounter)
	{
		MSP430_Opcode* opcode = nullptr;

		uint16* currentInstruction = (uint16*)programCounter;

		opcode = new MSP430_Opcode;

		opcode->address = programCounter;

		switch (*currentInstruction >> 13)
		{
			case 0: // single operand arithmetic 
			{
				opcode->type = SINGLE_OPERAND_ARITHMETIC;
			}
			break;

			case 1: // conditional
			{
				opcode->type = CONDITIONAL;
			}
			break;

			default: // two operand arithmetic
			{
				opcode->type = TWO_OPERAND_ARITHMETIC;
			}
			break;
		}

		return opcode;
	}
}