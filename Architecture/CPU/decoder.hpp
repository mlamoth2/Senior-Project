#pragma once

namespace Decoder
{
	class MSP430CPUDecoder
	{
	public:

		MSP430CPUDecoder();
		~MSP430CPUDecoder();

		uint8 decodeCurrentInstruction(uint16 programCounter, MSP430_Opcode* opcode);

	private:

	};
}