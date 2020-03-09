#include "..\..\Common\defines.hpp"
#include "..\..\Common\typedefs.hpp"
#include "..\..\Common\operand.hpp"
#include "..\..\Common\opcodes.hpp"

using namespace MSP430_Opcodes;
using namespace MSP430_Operands;

#include "decoder.hpp"
#include "execute.hpp"
#include "instructions.hpp"
#include "location.hpp"
#include "memory.hpp"
#include "registers.hpp"

using namespace Instructions;
using namespace Location;
using namespace Memory;
using namespace Registers;

// this code needs more reworking, MSP430 addressing modes can be quite complicated and difficult to decipher
// had to remove some code

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
		const MSP40_Single_Operand* singleOperand = opcode->getOpcodeInformation<MSP40_Single_Operand>();

		MSP430MemoryLocation destination;

		switch(singleOperand->as)
		{
			case 0: // Register direct mode
			{
				destination.setLocation(&cpuRegisters[singleOperand->dst]);
			}
			break;

			case 1: // Indexed mode
			{
				destination.setLocation(&(cpuRegisters[singleOperand->dst] + opcode->getImmediateDestination));
			}
			break;

			case 2: // Indirect register mode
			{
//				destination.setLocation(&cpuRegisters[singleOperand->dst].getContents());
			}
			break;

			case 3: // Auto increment
			{
				if(singleOperand->dst == PC)
				{

				}
			}
			break;
		}

		switch(opcode->getInstruction())
		{
			case RRC:
			{
				instructions.RRC(&destination);
			}
			break;

			case SWPB:
			{
				instructions.SWPB(&destination);
			}
			break;

			case RRA:
			{
				instructions.RRA(&destination);
			}
			break;

			case SXT:
			{
				instructions.SXT(&destination);
			}
			break;

			case PUSH:
			{
				instructions.PUSH(&destination);
			}
			break;

			case CALL:
			{
				instructions.CALL(&destination);
			}
			break;

			case RETI:
			{
				instructions.RETI(&destination);
			}
			break;
		}

	}

	void MSP430CPUExecute::executeConditional(MSP430_Opcodes::MSP430_Opcode* opcode)
	{
		const MSP430_Conditional* conditional = opcode->getOpcodeInformation<MSP430_Conditional>();

		int16 branch = conditional->offset;

		MSP430MemoryLocation branchLocation;

		branchLocation.setContents(branch);
				
		switch(opcode->getInstruction())
		{
			case JNZ:
//			case JNE:
			{
				instructions.JNE_JNZ(&branchLocation);
			}
			break;

			case JEQ:
//			case JZ:
			{
				instructions.JEQ_JZ(&branchLocation);
			}
			break;

			case JNC:
//			case JLO:
			{
				instructions.JNC_JLO(&branchLocation);
			}
			break;

			case JC:
//			case JHS:
			{
				instructions.JC_JHS(&branchLocation);
			}
			break;

			case JN:
			{
				instructions.JN(&branchLocation);
			}
			break;

			case JGE:
			{
				instructions.JGE(&branchLocation);
			}
			break;

			case JL:
			{
				instructions.JL(&branchLocation);
			}
			break;

			case JMP:
			{
				instructions.JMP(&branchLocation);
			}
			break;
		}
	}

	void MSP430CPUExecute::executeDoubleOperand(MSP430_Opcodes::MSP430_Opcode* opcode)
	{
		const MSP430_Double_Operand* doubleOperand = opcode->getOpcodeInformation<MSP430_Double_Operand>();

		MSP430MemoryLocation source;
		MSP430MemoryLocation destination;

		switch(doubleOperand->as)
		{
			case 0: // Register direct mode
			{
				source.setLocation(&cpuRegisters[doubleOperand->source]);		
			}
			break;

			case 1: // Indexed mode
			{
				source.setLocation(&(cpuRegisters[doubleOperand->source] + opcode->getImmediateSource));
			}
			break;

			case 2: // Indirect register mode
			{

			}
			break;

			case 3: // Auto increment
			{

			}
			break;
		}

		switch(doubleOperand->ad)
		{
			case 0:
			{
				destination.setLocation(&cpuRegisters[doubleOperand->dst]);
			}
			break;

			case 1:
			{
				destination.setLocation(&(cpuRegisters[doubleOperand->dst] + opcode->getImmediateDestination));
			}
			break;
		}

		switch(opcode->getInstruction())
		{
			case MOV:
			{
				instructions.MOV(&source, &destination);
			}
			break;

			case ADD:
			{
				instructions.ADD(&source, &destination);
			}
			break;

			case ADDC:
			{
				instructions.ADDC(&source, &destination);
			}
			break;

			case SUBC:
			{
				instructions.SUBC(&source, &destination);
			}
			break;

			case SUB:
			{
				instructions.SUB(&source, &destination);
			}
			break;

			case CMP:
			{
				instructions.CMP(&source, &destination);
			}
			break;

			case DADD:
			{
				instructions.DADD(&source, &destination);
			}
			break;

			case BIT:
			{
				instructions.BIT(&source, &destination);
			}
			break;

			case BIC:
			{
				instructions.BIC(&source, &destination);
			}
			break;

			case BIS:
			{
				instructions.BIS(&source, &destination);
			}
			break;

			case XOR:
			{
				instructions.XOR(&source, &destination);
			}
			break;

			case AND:
			{
				instructions.AND(&source, &destination);
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

	MSP430CPUExecute execute;
}
