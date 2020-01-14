#pragma once

namespace Decoder
{
	class MSP430CPUDecoder
	{
	public:

		MSP430CPUDecoder();
		~MSP430CPUDecoder();

		MSP430_Opcode* decodeCurrentInstruction(uint16 programCounter);

	private:

	};
}