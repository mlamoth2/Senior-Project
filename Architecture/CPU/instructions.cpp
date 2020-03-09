#include "..\..\Common\defines.hpp"
#include "..\..\Common\typedefs.hpp"

#include "location.hpp"
#include "instructions.hpp"
#include "registers.hpp"

#define BitsCount( val ) ( sizeof( val ) * CHAR_BIT )
#define Shift( val, steps ) ( steps % BitsCount( val ) )
#define ROL( val, steps ) ( ( val << Shift( val, steps ) ) | ( val >> ( BitsCount( val ) - Shift( val, steps ) ) ) )
#define ROR( val, steps ) ( ( val >> Shift( val, steps ) ) | ( val << ( BitsCount( val ) - Shift( val, steps ) ) ) )

// todo: overflow detection is not complete
// carry seems directly related
// maybe implement our own binary subtraction and addition(?)
// or find another way?

namespace Instructions
{
	MSP430CPUInstructions::MSP430CPUInstructions()
	{
	}

	MSP430CPUInstructions::~MSP430CPUInstructions()
	{

	}

	// Single operand

	void MSP430CPUInstructions::RRC(Location::MSP430Location* dst)
	{

	}

	void MSP430CPUInstructions::SWPB(Location::MSP430Location* dst)
	{
	}

	void MSP430CPUInstructions::RRA(Location::MSP430Location* dst)
	{

	}

	void MSP430CPUInstructions::SXT(Location::MSP430Location* dst)
	{
	}

	// todo: fix push and call

	void MSP430CPUInstructions::PUSH(Location::MSP430Location* dst)
	{
		uint16 currentStackPointer = Registers::cpuRegisters[SP].getContents();

		if(currentStackPointer == 0) // how?
		{
			// throw exception
		}
		else
		{
			currentStackPointer -= sizeof(uint16);

			Registers::cpuRegisters[SP].setContents(currentStackPointer);
		}
	}
	
	void MSP430CPUInstructions::CALL(Location::MSP430Location* dst)
	{
		uint16 currentStackPointer = Registers::cpuRegisters[SP].getContents();

		if(currentStackPointer == 0) // how?
		{
			// throw exception
		}
		else
		{
			currentStackPointer -= sizeof(uint16); // push PC

			Registers::cpuRegisters[SP].setContents(currentStackPointer);
		}
	}

	void MSP430CPUInstructions::RETI(Location::MSP430Location* dst)
	{
	}

	// Conditional, needs more work

	void MSP430CPUInstructions::JNE_JNZ(Location::MSP430Location* branchLocation)
	{
		if(Registers::cpuRegisters[SR].getBit(ZERO_BIT) != 1)
		{
			uint16 currentProgramCounter = Registers::cpuRegisters[PC].getContents();

			Registers::cpuRegisters[PC].setLocation((void*)(currentProgramCounter + 2*branchLocation->getContents()));
		}
	}

	void MSP430CPUInstructions::JEQ_JZ(Location::MSP430Location* branchLocation)
	{
		if(Registers::cpuRegisters[SR].getBit(ZERO_BIT) == 1)
		{
			uint16 currentProgramCounter = Registers::cpuRegisters[PC].getContents();

			Registers::cpuRegisters[PC].setLocation((void*)(currentProgramCounter + 2*branchLocation->getContents()));
		}
	}

	void MSP430CPUInstructions::JNC_JLO(Location::MSP430Location* branchLocation)
	{
		if(Registers::cpuRegisters[SR].getBit(CARRY_BIT) != 1)
		{
			uint16 currentProgramCounter = Registers::cpuRegisters[PC].getContents();

			Registers::cpuRegisters[PC].setLocation((void*)(currentProgramCounter + 2*branchLocation->getContents()));
		}
	}

	void MSP430CPUInstructions::JC_JHS(Location::MSP430Location* branchLocation)
	{
		if(Registers::cpuRegisters[SR].getBit(CARRY_BIT) == 1)
		{
			uint16 currentProgramCounter = Registers::cpuRegisters[PC].getContents();

			Registers::cpuRegisters[PC].setLocation((void*)(currentProgramCounter + 2*branchLocation->getContents()));
		}
	}

	void MSP430CPUInstructions::JN(Location::MSP430Location* branchLocation)
	{
		if(Registers::cpuRegisters[SR].getBit(NEGATIVE_BIT) != 1)
		{
			uint16 currentProgramCounter = Registers::cpuRegisters[PC].getContents();

			Registers::cpuRegisters[PC].setLocation((void*)(currentProgramCounter + 2*branchLocation->getContents()));
		}
	}
	
	void MSP430CPUInstructions::JGE(Location::MSP430Location* branchLocation)
	{
		if(Registers::cpuRegisters[SR].getBit(NEGATIVE_BIT) == Registers::cpuRegisters[SR].getBit(OVERFLOW_BIT))
		{
			uint16 currentProgramCounter = Registers::cpuRegisters[PC].getContents();

			Registers::cpuRegisters[PC].setLocation((void*)(currentProgramCounter + 2*branchLocation->getContents()));
		}
	}

	void MSP430CPUInstructions::JL(Location::MSP430Location* branchLocation)
	{
		if(Registers::cpuRegisters[SR].getBit(NEGATIVE_BIT) != Registers::cpuRegisters[SR].getBit(OVERFLOW_BIT))
		{
			uint16 currentProgramCounter = Registers::cpuRegisters[PC].getContents();

			Registers::cpuRegisters[PC].setLocation((void*)(currentProgramCounter + 2*branchLocation->getContents()));
		}
	}

	void MSP430CPUInstructions::JMP(Location::MSP430Location* branchLocation)
	{
		uint16 currentProgramCounter = Registers::cpuRegisters[PC].getContents();

		Registers::cpuRegisters[PC].setLocation((void*)(currentProgramCounter + 2*branchLocation->getContents()));
	}

	// Double operand

	void MSP430CPUInstructions::MOV(Location::MSP430Location* src, Location::MSP430Location* dst)
	{
		dst->setContents(src->getContents());
	}

	void MSP430CPUInstructions::ADD(Location::MSP430Location* src, Location::MSP430Location* dst)
	{
		bool expect_positive = false;
		bool expect_negative = false;
		bool overflow = false;
		bool carry = false;
		bool source_negative = false;
		bool destination_negative = false;

		int16 source = 0, destination = 0;

		int result = 0;

		source = src->getContents();
		destination = dst->getContents();

		if(source < 0)
		{
			source_negative = true;
		}
		if(destination < 0)
		{
			destination_negative = true;
		}

		result = source + destination;

		if(source > 0 && destination > 0)
		{
			expect_positive = true;
		}

		if(source < 0 && destination < 0)
		{
			expect_negative = true;
		}
				
		if(result < 0 && expect_positive == true
		   || result > 0 && expect_negative == true)
		{
			overflow = true;
		}

		if(source_negative != destination_negative)
		{
			overflow = true;
		}

		if(overflow == true)
		{
			Registers::cpuRegisters[SR].turnOnBit(OVERFLOW_BIT);
			Registers::cpuRegisters[SR].turnOnBit(CARRY_BIT); // eek
		}

		if(result == 0)
		{
			Registers::cpuRegisters[SR].turnOnBit(ZERO_BIT);
		}

		if(result < 0)
		{
			Registers::cpuRegisters[SR].turnOnBit(NEGATIVE_BIT);
		}

		dst->setContents(src->getContents() + dst->getContents());
	}

	void MSP430CPUInstructions::ADDC(Location::MSP430Location* src, Location::MSP430Location* dst)
	{
	}

	void MSP430CPUInstructions::CMP(Location::MSP430Location* src, Location::MSP430Location* dst)
	{
		bool expect_positive = false;
		bool expect_negative = false;
		bool overflow = false;
		bool carry = false;
		bool source_negative = false;
		bool destination_negative = false;

		int16 source = 0, destination = 0;

		int result = 0;

		source = src->getContents();
		destination = dst->getContents();

		if(source < 0)
		{
			source_negative = true;
		}
		if(destination < 0)
		{
			destination_negative = true;
		}

		result = destination - source;

		if(source > 0 && destination > 0)
		{
			expect_positive = true;
		}

		if(source < 0 && destination < 0)
		{
			expect_negative = true;
		}
				
		if(result < 0 && expect_positive == true
		   || result > 0 && expect_negative == true)
		{
			overflow = true;
		}

		if(source_negative != destination_negative)
		{
			overflow = true;
		}

		if(overflow == true)
		{
			Registers::cpuRegisters[SR].turnOnBit(OVERFLOW_BIT);
			Registers::cpuRegisters[SR].turnOnBit(CARRY_BIT);
		}

		if(result == 0)
		{
			Registers::cpuRegisters[SR].turnOnBit(ZERO_BIT); // equal
		}

		if(result < 0)
		{
			Registers::cpuRegisters[SR].turnOnBit(NEGATIVE_BIT);
		}
	}
	
	void MSP430CPUInstructions::SUBC(Location::MSP430Location* src, Location::MSP430Location* dst)
	{
	}
	
	void MSP430CPUInstructions::SUB(Location::MSP430Location* src, Location::MSP430Location* dst)
	{
		bool expect_positive = false;
		bool expect_negative = false;
		bool overflow = false;
		bool carry = false;
		bool source_negative = false;
		bool destination_negative = false;

		int16 source = 0, destination = 0;

		int result = 0;

		source = src->getContents();
		destination = dst->getContents();
				
		if(source < 0)
		{
			source_negative = true;
		}
		if(destination < 0)
		{
			destination_negative = true;
		}

		result = destination - source;

		if(source > 0 && destination > 0)
		{
			expect_positive = true;
		}

		if(source < 0 && destination < 0)
		{
			expect_negative = true;
		}
				
		if(result < 0 && expect_positive == true
		   || result > 0 && expect_negative == true)
		{
			overflow = true;
		}

		if(source_negative != destination_negative)
		{
			overflow = true;
		}

		if(overflow == true)
		{
			Registers::cpuRegisters[SR].turnOnBit(OVERFLOW_BIT);
			Registers::cpuRegisters[SR].turnOnBit(CARRY_BIT);
		}

		if(result == 0)
		{
			Registers::cpuRegisters[SR].turnOnBit(ZERO_BIT);
		}

		if(result < 0)
		{
			Registers::cpuRegisters[SR].turnOnBit(NEGATIVE_BIT);
		}

		dst->setContents(dst->getContents() - src->getContents());
	}

	void MSP430CPUInstructions::DADD(Location::MSP430Location* src, Location::MSP430Location* dst)
	{
	}

	void MSP430CPUInstructions::BIT(Location::MSP430Location* src, Location::MSP430Location* dst)
	{
	}

	void MSP430CPUInstructions::BIC(Location::MSP430Location* src, Location::MSP430Location* dst)
	{
		dst->setContents(src->getContents() & ~dst->getContents());
	}

	void MSP430CPUInstructions::BIS(Location::MSP430Location* src, Location::MSP430Location* dst)
	{
		dst->setContents(src->getContents() | dst->getContents());
	}

	void MSP430CPUInstructions::XOR(Location::MSP430Location* src, Location::MSP430Location* dst)
	{
		dst->setContents(src->getContents() ^ dst->getContents());
	}

	void MSP430CPUInstructions::AND(Location::MSP430Location* src, Location::MSP430Location* dst)
	{
		dst->setContents(src->getContents() & dst->getContents());
	}
}