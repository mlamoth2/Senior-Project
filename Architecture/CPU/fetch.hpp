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
			At the end of the fetch operation, the PC points to the next instruction that will be read at the next cycle.
		*/

		void Fetch(MSP430_Opcode* opcode)
		{
			opcode->setAddress(programCounter);

			opcode->initialize();
			
			advanceProgramCounter(opcode->getLength());
		}

		void advanceProgramCounter(uint8 delta)
		{
			programCounter += delta;
		}

		void setProgramCounter(uint16 newProgramCounter)
		{
			programCounter = newProgramCounter;
		}

	private:

		uint16 programCounter;
	};
}