#pragma once

namespace Fetcher
{
	class MSP430Fetcher
	{
	public:

		MSP430Fetcher(uint16 programCounter);
		~MSP430Fetcher();
				
		uint16 getProgramCounter()
		{
			return programCounter;
		}

		/*
			Fetch Stage: The next instruction is fetched from the memory address that is currently stored in the program counter and stored into the instruction register. 
			At the end of the fetch operation, the PC points to the next instruction that will be read at the next cycle, if we haven't branched first.
		*/

		void Fetch(MSP430_Opcodes::MSP430_Opcode* opcode)
		{
			opcode->setAddress(getProgramCounter());
			
			opcode->initialize();
			
			advanceProgramCounter(opcode->getLength());
		}

		void advanceProgramCounter(int8 delta);

		void setProgramCounter(uint16 newProgramCounter);

	private:

		uint16 programCounter;
	};
}