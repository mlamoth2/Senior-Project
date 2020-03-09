#pragma once

// I don't like how this had to be written, possibly restructure this slightly

namespace Memory
{
	class MSP430MemoryLocation : public Location::MSP430Location
	{
	public:

		void setContents(uint16 newContents)
		{
			contents = newContents;

			uint16* location = reinterpret_cast<uint16*>(getLocation());

			*location = newContents;
		}

		uint16 getContents()
		{
			uint16* location = reinterpret_cast<uint16*>(getLocation());

			contents = *location;

			return contents;
		}
		
		void turnOffBits(uint16 bitMask)
		{
			uint16* location = reinterpret_cast<uint16*>(getLocation());

			contents &= ~bitMask;

			*location = contents;
		}

		void turnOnBits(uint16 bitMask)
		{
			uint16* location = reinterpret_cast<uint16*>(getLocation());

			contents |= bitMask;

			*location = contents;
		}

		void turnOnBit(uint16 bit)
		{
			uint16* location = reinterpret_cast<uint16*>(getLocation());

			contents |= (1 << bit);

			*location = contents;
		}

		void turnOffBit(uint16 bit)
		{
			uint16* location = reinterpret_cast<uint16*>(getLocation());

			contents &= ~(1 << bit);

			*location = contents;
		}

		char getBit(uint16 bit)
		{			
			contents = *(uint16*)getLocation();

			return contents & (1 << bit);
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