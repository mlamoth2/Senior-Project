#include "..\..\Common\defines.hpp"
#include "..\..\Common\typedefs.hpp"

#include "location.hpp"
#include "instructions.hpp"
#include "registers.hpp"

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

	void MSP430CPUInstructions::PUSH(Location::MSP430Location* dst)
	{
	}
	
	void MSP430CPUInstructions::CALL(Location::MSP430Location* dst)
	{
	}

	void MSP430CPUInstructions::RETI(Location::MSP430Location* dst)
	{
	}

	// Conditional

	void MSP430CPUInstructions::JNE_JNZ(Location::MSP430Location* branchLocation)
	{
	}

	void MSP430CPUInstructions::JEQ_JZ(Location::MSP430Location* branchLocation)
	{
	}

	void MSP430CPUInstructions::JNC_JLO(Location::MSP430Location* branchLocation)
	{
	}

	void MSP430CPUInstructions::JC_JHS(Location::MSP430Location* branchLocation)
	{
	}

	void MSP430CPUInstructions::JN(Location::MSP430Location* branchLocation)
	{
	}
	
	void MSP430CPUInstructions::JGE(Location::MSP430Location* branchLocation)
	{
	}

	void MSP430CPUInstructions::JL(Location::MSP430Location* branchLocation)
	{
	}

	void MSP430CPUInstructions::JMP(Location::MSP430Location* branchLocation)
	{
	}

	// Double operand

	void MSP430CPUInstructions::MOV(Location::MSP430Location* src, Location::MSP430Location* dst)
	{
	}

	void MSP430CPUInstructions::ADD(Location::MSP430Location* src, Location::MSP430Location* dst)
	{
	}

	void MSP430CPUInstructions::ADDC(Location::MSP430Location* src, Location::MSP430Location* dst)
	{
	}

	void MSP430CPUInstructions::CMP(Location::MSP430Location* src, Location::MSP430Location* dst)
	{
	}
	
	void MSP430CPUInstructions::SUBC(Location::MSP430Location* src, Location::MSP430Location* dst)
	{
	}
	
	void MSP430CPUInstructions::SUB(Location::MSP430Location* src, Location::MSP430Location* dst)
	{
	}

	void MSP430CPUInstructions::DADD(Location::MSP430Location* src, Location::MSP430Location* dst)
	{
	}

	void MSP430CPUInstructions::BIT(Location::MSP430Location* src, Location::MSP430Location* dst)
	{
	}

	void MSP430CPUInstructions::BIC(Location::MSP430Location* src, Location::MSP430Location* dst)
	{
	}

	void MSP430CPUInstructions::BIS(Location::MSP430Location* src, Location::MSP430Location* dst)
	{
	}

	void MSP430CPUInstructions::XOR(Location::MSP430Location* src, Location::MSP430Location* dst)
	{
	}

	void MSP430CPUInstructions::AND(Location::MSP430Location* src, Location::MSP430Location* dst)
	{
	}
}