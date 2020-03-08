#pragma once

namespace Memory
{
	class MSP430MemoryLocation : Location::MSP430Location
	{
	public:

		void setContents(uint16 newContents)
		{
			contents = newContents;
		}

		uint16 getContents()
		{
			return contents;
		}
		
		void turnOffBits(uint16 bitMask)
		{
			contents &= ~bitMask;
		}

		void turnOnBits(uint16 bitMask)
		{
			contents |= bitMask;
		}
				
		virtual void* getLocation()
		{
			return reinterpret_cast<void*>(memoryAddress);
		}

		void setLocation(void* location)
		{
			memoryAddress = reinterpret_cast<unsigned int>(location);
		}

	private:

		unsigned int memoryAddress;
		uint16 contents;
	};
}