#pragma once

namespace Fetcher
{
	class MSP430Fetch
	{
	public:

		MSP430Fetch(uint16 programCounter);
		~MSP430Fetch();

		void advanceProgramCounter()
		{
			this->programCounter += sizeof(uint16);
		}

		void retractProgramCounter()
		{
			this->programCounter -= sizeof(uint16);
		}

		void setProgramCounter(uint16 newProgramCounter)
		{
			programCounter = newProgramCounter;
		}

		uint16 getProgramCounter()
		{
			return programCounter;
		}

	private:

		uint16 programCounter;
	};
}