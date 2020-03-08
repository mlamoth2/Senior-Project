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

	}

	void MSP430CPUExecute::executeDoubleOperand(MSP430_Opcodes::MSP430_Opcode* opcode)
	{
	
	}

	void MSP430CPUExecute::executeConditional(MSP430_Opcodes::MSP430_Opcode* opcode)
	{
	
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
