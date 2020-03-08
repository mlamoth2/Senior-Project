#pragma once

namespace Execute
{
	class MSP430CPUExecute
	{
	public:

		MSP430CPUExecute();
		~MSP430CPUExecute();

		void executeInstruction(MSP430_Opcodes::MSP430_Opcode* opcode, uint16 instruction);

		void executeSingleOperand(MSP430_Opcodes::MSP430_Opcode* opcode, uint16 instruction);
		void executeDoubleOperand(MSP430_Opcodes::MSP430_Opcode* opcode, uint16 instruction);
		void executeConditional(MSP430_Opcodes::MSP430_Opcode* opcode, uint16 instruction);

	private:

	};
}