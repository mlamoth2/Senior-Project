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

		void AdvanceProgramCounter()
		{
			programCounter += sizeof(uint16);
		}

		void setProgramCounter(uint16 newProgramCounter)
		{
			programCounter = newProgramCounter;
		}

	private:

		uint16 programCounter;
	};
}