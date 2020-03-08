#include "..\..\Common\defines.hpp"
#include "..\..\Common\typedefs.hpp"
#include "..\..\Common\operand.hpp"
#include "..\..\Common\opcodes.hpp"

using namespace MSP430_Opcodes;

#include "fetch.hpp"
#include "registers.hpp"

using namespace Registers;

#include <cstring>

using namespace std;

namespace Fetcher
{
	MSP430Fetcher::MSP430Fetcher(uint16 programCounter)
	{
		this->programCounter = programCounter; // initialize the fetcher
		cpuRegisters[PC].setContents(programCounter); // initialize the program counter
	}

	MSP430Fetcher::~MSP430Fetcher()
	{
		
	}

	void MSP430Fetcher::advanceProgramCounter(int8 delta)
	{
		programCounter += delta;

		cpuRegisters[PC].setContents(programCounter);
	}

	void MSP430Fetcher::setProgramCounter(uint16 newProgramCounter)
	{
		programCounter = newProgramCounter;

		cpuRegisters[PC].setContents(newProgramCounter);
	}
}