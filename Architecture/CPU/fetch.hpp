#pragma once

namespace Fetcher
{
	class MSP430Fetcher
	{
	public:

		MSP430Fetcher(uint16 programCounter);
		~MSP430Fetcher();
		
		bool consumeCacheLine(uint8 consumed)
		{
			bool didConsumeCacheLine = true;

			if ((cacheLineLeft - consumed) < 0)
			{
				// fetch another cacheline

				fetchCacheLine((uint8*)programCounter);

				didConsumeCacheLine = false;
			}
			else
			{
				cacheLineLeft -= consumed;
			}

			return didConsumeCacheLine;
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
		int16 cacheLineLeft;
	};
}