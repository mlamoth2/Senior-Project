﻿#include "..\..\Common\defines.hpp"
#include "..\..\Common\typedefs.hpp"
#include "..\..\Common\operand.hpp"
#include "..\..\Common\opcodes.hpp"

using namespace MSP430_Opcodes;
using namespace MSP430_Operands;

#include "cache.hpp"
#include "decoder.hpp"
#include "location.hpp"
#include "registers.hpp"

using namespace Cache;
using namespace Location;
using namespace Registers;

/*
http://www.ece.utep.edu/courses/web3376/Links_files/MSP430%20Quick%20Reference.pdf

As Ad d/s Register Syntax Description
00 0 ds n ≠ 3 Rn Register direct. The operand is the contents of Rn. Ad=0
01 1 ds n ≠ 0, 2, 3 x(Rn) Indexed. The operand is in memory at address Rn+x.
10 - s n ≠ 0, 2, 3 @Rn Register indirect. The operand is in memory at the address held in Rn.
11 - s n ≠ 0, 2, 3 @Rn+ Indirect auto-increment. As above, then the register is incremented by 1 or 2.
Addressing modes using R0 (PC)
01 1 ds 0 (PC) LABEL Symbolic. x(PC) The operand is in memory at address PC+x.
11 - s 0 (PC) #x Immediate. @PC+ The operand is the next word in the instruction stream.
Addressing modes using R2 (SR) and R3 (CG), special-case decoding
01 1 ds 2 (SR) &LABEL Absolute. The operand is in memory at address x.
10 - s 2 (SR) #4 Constant. The operand is the constant 4.
11 - s 2 (SR) #8 Constant. The operand is the constant 8.
00 - s 3 (CG) #0 Constant. The operand is the constant 0.
01 - s 3 (CG) #1 Constant. The operand is the constant 1. There is no index word.
10 - s 3 (CG) #2 Constant. The operand is the constant 2.
11 - s 3 (CG) #−1 Constant. The operand is the constant −1.

https://cnx.org/contents/6YtMW_PQ@3.1:__auotnt@1/Addressing-modes

http://mspgcc.sourceforge.net/manual/x147.html
*/

namespace Decode
{
	MSP430CPUDecode::MSP430CPUDecode()
	{
	}

	MSP430CPUDecode::~MSP430CPUDecode()
	{
	}

	/*
		Decode Stage: During this stage, the encoded instruction present in the instruction register is interpreted by the Decode.
		Read the effective address: In the case of a memory instruction (direct or indirect), the execution phase will be during the next clock pulse. 
		If the instruction has an indirect address, the effective address is read from main memory, and any required data is fetched from main memory to be processed and then placed into data registers (clock pulse: T3). 
		If the instruction is direct, nothing is done during this clock pulse. If this is an I/O instruction or a register instruction, the operation is performed during the clock pulse.
	*/
	
	void MSP430CPUDecode::decodeCurrentInstruction(MSP430_Opcode* opcode)
	{
		switch (opcode->getInstructionType())
		{
			// todo: once L2 and L3 are done, we can query to see if the address was cached, so
			// it behaves more like a traditional cpu Decode

			case SINGLE_OPERAND:
			{
				const MSP40_Single_Operand* singleOperand = opcode->getOpcodeInformation<MSP40_Single_Operand>();
			
				switch(singleOperand->as)
				{
					case 0: // Register direct mode
					{
						// no cache needed, just register
					}
					break;

					case 1: // Indexed mode
					{

					}
					break;

					case 2: // Indirect register mode
					{

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

				
			}
			break;

			case CONDITIONAL:
			{
				const MSP430_Conditional* conditional = opcode->getOpcodeInformation<MSP430_Conditional>();
			
				// conditionals don't require any special addressing
			}
			break;

			case DOUBLE_OPERAND:
			{
				const MSP430_Double_Operand* doubleOperand = opcode->getOpcodeInformation<MSP430_Double_Operand>();
			
				switch(doubleOperand->as)
				{
					case 0: // Register direct mode
					{
						
					}
					break;

					case 1: // Indexed mode
					{
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

					}
					break;

					case 1:
					{
				
					}
					break;
				}
			}
			break;
		}
	}

	MSP430CPUDecode decode;
}