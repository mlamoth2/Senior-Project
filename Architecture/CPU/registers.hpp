#pragma once

namespace Registers
{
	class MSP430CPURegisters
	{
	public:

		MSP430CPURegisters();
		~MSP430CPURegisters();

		// This routine allows us to seemlessly cast between int8 and int16
		template <typename T> 
		T getContents()
		{
			return reinterpret_cast<T>(contents);
		}

		void setContents(int16 newContents)
		{
			contents = newContents;
		}

		void turnOffBits(uint16 bitMask)
		{
			contents &= ~bitMask;
		}

		void turnOnBits(uint16 bitMask)
		{
			contents |= bitMask;
		}
	private:

		int16 contents;
	};
}