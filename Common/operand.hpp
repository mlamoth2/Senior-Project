#pragma once

namespace MSP430_Operands
{
	typedef struct
	{
		template <class T>
		T sourceAddress;
		
		template <class T>
		T destinationAddress;

		union
		{
			uint8 immediate8;
			uint16 immediate16;
		};

		uint8 size;

		template <class T>
		void setSourceAddress(T sourceAddress)
		{
			this->sourceAddress = sourceAddress;
		}

		template <class T>
		T getSourceAddress()
		{
			return sourceAddress;
		}

		template <class T>
		void setDestinationAddress(T destinationAddress)
		{
			this->destinationAddress = destinationAddress;
		}

		template <class T>
		T getDestinationAddress()
		{
			return destinationAddress;
		}

		void setImmediate(uint16 immediate)
		{
			this->immediate16 = immediate;
		}

		uint16 getImmediate()
		{
			return immediate16;
		}

		uint8 getSize()
		{
			return size;
		}

		void setSize(uint8 size)
		{
			this->size = size;
		}

	}MSP430_Operand;
}