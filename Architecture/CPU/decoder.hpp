#pragma once

namespace Decoder
{
	class MSP430Decoder
	{
	public:

		MSP430Decoder();
		~MSP430Decoder();

		MSP430_Opcode* decodeCurrentInstruction(uint16 programCounter);

	private:

	};
}