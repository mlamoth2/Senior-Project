#pragma once

namespace Decode
{
	class MSP430CPUDecode
	{
	public:

		MSP430CPUDecode();
		~MSP430CPUDecode();

		/*
			Decode Stage: During this stage, the encoded instruction present in the instruction register is interpreted by the decoder.
			Read the effective address: In the case of a memory instruction (direct or indirect), the execution phase will be during the next clock pulse. 
			If the instruction has an indirect address, the effective address is read from main memory, and any required data is fetched from main memory to be processed and then placed into data registers (clock pulse: T3). 
			If the instruction is direct, nothing is done during this clock pulse. If this is an I/O instruction or a register instruction, the operation is performed during the clock pulse.
		*/

		void decodeCurrentInstruction(MSP430_Opcodes::MSP430_Opcode* opcode);

	private:

	};

	extern MSP430CPUDecode decode;
}