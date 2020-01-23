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

		void setSourceAddress(uint16 sourceAddress)
		{
			this->sourceAddress16 = sourceAddress;
		}

		uint16 getSourceAddress()
		{
			return sourceAddress16;
		}

		void setDestinationAddress(uint16 destinationAddress)
		{
			this->destinationAddress16 = destinationAddress;
		}

		uint16 getDestinationAddress()
		{
			return destinationAddress16;
		}

		void setImmediate(uint16 immediate)
		{
			this->immediate16 = immediate;
		}

		uint16 getImmediate()
		{
			return immediate16;
		}
	}MSP430_Operand;
}