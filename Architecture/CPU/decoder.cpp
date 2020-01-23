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

	/*
		Decode Stage: During this stage, the encoded instruction present in the instruction register is interpreted by the decoder.
		Read the effective address: In the case of a memory instruction (direct or indirect), the execution phase will be during the next clock pulse. 
		If the instruction has an indirect address, the effective address is read from main memory, and any required data is fetched from main memory to be processed and then placed into data registers (clock pulse: T3). 
		If the instruction is direct, nothing is done during this clock pulse. If this is an I/O instruction or a register instruction, the operation is performed during the clock pulse.
	*/
	
	void MSP430CPUDecoder::decodeCurrentInstruction(MSP430_Opcode* opcode)
	{
		switch (opcode->getInstructionType())
		{
			case SINGLE_OPERAND_ARITHMETIC:
			{
				const MSP40_Single_Operand_Arithmetic* singleOperandArithmetic = opcode->getOpcodeInformation<MSP40_Single_Operand_Arithmetic>();
			
				
			}
			break;

			case CONDITIONAL:
			{
				const MSP430_Conditional* conditional = opcode->getOpcodeInformation<MSP430_Conditional>();
			
				
			}
			break;

			case TWO_OPERAND_ARITHMETIC:
			{
				const MSP430_Two_Operand_Arithmetic* twoOperandArithmetic = opcode->getOpcodeInformation<MSP430_Two_Operand_Arithmetic>();
			
				
			}
			break;
		}
	}
}