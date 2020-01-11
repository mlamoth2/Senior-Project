#include "..\Common\typedefs.h"
#include "..\Common\opcodes.h"

using namespace MSP430_Opcodes; // this has to be above the include below, otherwise compile error

#include "decoder.h"

namespace Decoder
{
	MSP430Decoder::MSP430Decoder(uint16 intialProgramCounter)
	{
		// todo:
		// check if PC is 2 byte aligned and within executable region

		programCounter = intialProgramCounter;
	}

	MSP430Decoder::~MSP430Decoder()
	{
	}

	// todo: add some sort of garbage collection
	MSP430_Opcode* MSP430Decoder::decodeCurrentInstruction()
	{
		int type;

		MSP430_Opcode* opcode = nullptr;

		uint16* currentInstruction = (uint16*)programCounter;

		opcode = new MSP430_Opcode;

		type = *currentInstruction >> 13;

		opcode->address = programCounter;

		switch (type)
		{
			case 0: // single operand arithmetic 
			{
				opcode->type = SINGLE_OPERAND;
			}
			break;

			case 1: // conditional
			{
				opcode->type = CONDITIONAL;
			}
			break;

			default: // two operand arithmetic
			{
				opcode->type = TWO_BYTE_OPERAND;
			}
			break;
		}

		return opcode;
	}
}