#pragma once

namespace Registers
{
	class MSP430CPURegisters : Location::MSP430Location
	{
	public:

		MSP430CPURegisters();
		~MSP430CPURegisters();

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

		void turnOnBit(uint16 bit)
		{
			contents |= (1 << bit);
		}

		void turnOffBit(uint16 bit)
		{
			contents &= ~(1 << bit);
		}

		char getBit(uint16 bit)
		{
			return contents & (1 << bit);
		}
		
		virtual void* getLocation()
		{
			return reinterpret_cast<void*>(this);
		}

		void setLocation(void* location)
		{
		
		}

	private:

		uint16 contents;
	};

/*
	SCG (system clock generator), OSCOFF (oscillator off), and CPUOFF are used to control the various low-power modes.
	GIE is the global interrupt enable. Turning off this bit masks interrupts. (NOTE: it may be delayed by 1 cycle, so an interrupt may be taken after the instruction after GIE is cleared. Add a NOP or clear GIE one instruction earlier than your real "critical section".)

	N, Z, C and V are the usual processor status bits, set as a side effect to instruction execution. If r2 is specified as a destination, the explicitly written bits override the side effects. An instruction sets all 4 bits, or none of them. Logical instructions set C to the opposite of Z (C is set if the result is NOT zero), and clear V to 0.

	C is a "carry" bit as opposed to a "borrow" bit when subtracting. That is, subtract with carry of A-B computes A + ~B + Carry. (~ is the C "not" or "bitwise invert" operator.)

	Note that the basic move instruction does NOT set these bits (unless it's a move to r2).

	r3 is hardwired to 0. If specified as a source, its value is 0. If specified as a destination, the value is discarded.
*/

	extern MSP430CPURegisters cpuRegisters[MAX_REGISTERS];
}