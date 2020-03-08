#include "..\..\Common\typedefs.hpp"
#include "..\..\Common\operand.hpp"
#include "..\..\Common\opcodes.hpp"

#include "execute.hpp"
#include "decoder.hpp"
#include "..\..\Common\defines.hpp"
#include "..\..\Common\typedefs.hpp"
#include "..\..\Common\operand.hpp"
#include "..\..\Common\opcodes.hpp"

using namespace MSP430_Opcodes;
using namespace MSP430_Operands;

#include "location.hpp"
#include "memory.hpp"
#include "registers.hpp"

using namespace Location;
using namespace Memory;
using namespace Registers;

namespace Execute
{
	MSP430CPUExecute::MSP430CPUExecute()
	{

	}
	MSP430CPUExecute::~MSP430CPUExecute()
	{

	}
	
	void MSP430CPUExecute::executeSingleOperand(MSP430_Opcodes::MSP430_Opcode* opcode)
	{
		switch(opcode->getInstruction())
		{
			case RRC:
			{
			}
			break;

			case SWPB:
			{
			}
			break;

			case RRA:
			{
			}
			break;

			case SXT:
			{
			}
			break;

			case PUSH:
			{
			}
			break;

			case CALL:
			{
			}
			break;

			case RETI:
			{
			}
			break;
		}

	}

	void MSP430CPUExecute::executeDoubleOperand(MSP430_Opcodes::MSP430_Opcode* opcode)
	{
		switch(opcode->getInstruction())
		{
			case JNZ:
//			case JNE:
			{
			}
			break;

			case JEQ:
//			case JZ:
			{
			}
			break;

			case JNC:
//			case JLO:
			{
			}
			break;

			case JC:
//			case JHS:
			{
			}
			break;

			case JN:
			{
			}
			break;

			case JGE:
			{
			}
			break;

			case JL:
			{
			}
			break;

			case JMP:
			{
			}
			break;
		}
	}

	void MSP430CPUExecute::executeConditional(MSP430_Opcodes::MSP430_Opcode* opcode)
	{
		switch(opcode->getInstruction())
		{
			case MOV:
			{
			}
			break;

			case ADD:
			{
			}
			break;

			case ADDC:
			{
			}
			break;

			case SUBC:
			{
			}
			break;

			case SUB:
			{
			}
			break;

			case CMP:
			{
			}
			break;

			case DADD:
			{
			}
			break;

			case BIT:
			{
			}
			break;

			case BIC:
			{
			}
			break;

			case BIS:
			{
			}
			break;

			case XOR:
			{
			}
			break;

			case AND:
			{
			}
			break;
		}
	}

	void MSP430CPUExecute::executeInstruction(MSP430_Opcodes::MSP430_Opcode* opcode)
	{
		switch (opcode->getInstructionType())
		{
			case SINGLE_OPERAND:
			{
				executeSingleOperand(opcode);
			}
			break;

			case CONDITIONAL:
			{
				executeConditional(opcode);
			}
			break;

			case DOUBLE_OPERAND:
			{
				executeDoubleOperand(opcode);
			}
			break;

			default:
			{
				// throw exception
			}
			break;
		}

	}
}
