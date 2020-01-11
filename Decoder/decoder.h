#pragma once

namespace Decoder
{
	class MSP430Decoder
	{
	public:

		MSP430Decoder(uint16 intialProgramCounter);
		~MSP430Decoder();

		uint16 getProgramCounter()
		{
			return programCounter;
		}

		void setProgramCounter(uint16 newProgramCounter)
		{
			programCounter = newProgramCounter;
		}

		void advanceProgramCounter()
		{
			programCounter += sizeof(uint16);
		}

		void reverseProgramCounter()
		{
			programCounter -= sizeof(uint16);
		}

		MSP430_Opcode* decodeCurrentInstruction();

	private:

		uint16 programCounter;
	};
}