#pragma once

namespace Fetcher
{
	class MSP430Fetcher
	{
	public:

		MSP430Fetcher(uint16 programCounter);
		~MSP430Fetcher();

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

		void fetchCacheLine(uint8* cacheBuffer);

	private:

		uint16 programCounter;
		uint8 cacheLine[CACHE_LINE_SIZE];
	};
}