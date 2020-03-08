#pragma once

namespace Instructions
{
	// interface
	// this class represents all possible locations, registers, memory and such

	class MSP430Location
	{
	public:

		virtual unsigned short GetValue() = 0;
	};

	class MSP430CPUInstructions : public MSP430Location
	{
	public:

		MSP430CPUInstructions();
		~MSP430CPUInstructions();

		// Single operand

		// Conditional

		// Double operand


	private:

	};
}