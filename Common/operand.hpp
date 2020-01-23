#pragma once

namespace MSP430_Operands
{
	typedef struct
	{
		union
		{
			uint8 sourceAddress8;
			uint16 sourceAddress16;

			uint8 destinationAddress8;
			uint16 destinationAddress16;
		};

		union
		{
			uint8 immediate8;
			uint16 immediate16;
		};


	}MSP430_Operand;
}