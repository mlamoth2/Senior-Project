#pragma once

// interface
// this class represents all possible locations, registers, memory and such

namespace Location
{
	class MSP430Location
	{
	public:

		virtual void* getLocation() = 0;
		virtual void setLocation(void* location) = 0;

		virtual void setContents(uint16 value) = 0;
		virtual uint16 getContents() = 0;

		virtual void turnOffBits(uint16 bitMask) = 0;
		virtual void turnOnBits(uint16 bitMask) = 0;

	};
}