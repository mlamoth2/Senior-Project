#pragma once

namespace Instructions
{
	class MSP430CPUInstructions : Location::MSP430Location
	{
	public:

		MSP430CPUInstructions();
		~MSP430CPUInstructions();

		// Single operand

		void RRA(Location::MSP430Location* dst);
		void RRC(Location::MSP430Location* dst);
		void SWPB(Location::MSP430Location* dst);
		void SXT(Location::MSP430Location* dst);
		void PUSH(Location::MSP430Location* dst);
		void CALL(Location::MSP430Location* dst);
		void RETI(Location::MSP430Location* dst);

		// Conditional

		void JEQ(Location::MSP430Location* branchLocation);
		void JZ(Location::MSP430Location* branchLocation);
		void JNE(Location::MSP430Location* branchLocation);
		void JNZ(Location::MSP430Location* branchLocation);
		void JC(Location::MSP430Location* branchLocation);
		void JNC(Location::MSP430Location* branchLocation);
		void JN(Location::MSP430Location* branchLocation);
		void JGE(Location::MSP430Location* branchLocation);
		void JL(Location::MSP430Location* branchLocation);
		void JMP(Location::MSP430Location* branchLocation);

		// Double operand

		void ADD(Location::MSP430Location* src, Location::MSP430Location* dst);
		void ADDC(Location::MSP430Location* src, Location::MSP430Location* dst);
		void DADD(Location::MSP430Location* src, Location::MSP430Location* dst);
		void SUB(Location::MSP430Location* src, Location::MSP430Location* dst);
		void SUBC(Location::MSP430Location* src, Location::MSP430Location* dst);
		void AND(Location::MSP430Location* src, Location::MSP430Location* dst);
		void BIS(Location::MSP430Location* src, Location::MSP430Location* dst);
		void BIT(Location::MSP430Location* src, Location::MSP430Location* dst);
		void XOR(Location::MSP430Location* src, Location::MSP430Location* dst);
		void CMP(Location::MSP430Location* src, Location::MSP430Location* dst);
		void MOV(Location::MSP430Location* src, Location::MSP430Location* dst);


	private:

	};
}