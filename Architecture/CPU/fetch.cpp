#include "..\..\Common\defines.hpp"
#include "..\..\Common\typedefs.hpp"
#include "..\..\Common\operand.hpp"
#include "..\..\Common\opcodes.hpp"

#include "fetch.hpp"
#include "location.hpp"
#include "registers.hpp"

using namespace MSP430_Opcodes;

using namespace Location;
using namespace Registers;

#include <cstring>

using namespace std;

namespace Fetch
{
	MSP430Fetch::MSP430Fetch(uint16 programCounter)
	{
		this->programCounter = programCounter; // initialize the fetcher
		cpuRegisters[PC].setContents(programCounter); // initialize the program counter
	}

	MSP430Fetch::~MSP430Fetch()
	{
		
	}

	void MSP430Fetch::advanceProgramCounter(int8 delta)
	{
		programCounter += delta;

		cpuRegisters[PC].setContents(programCounter);
	}

	void MSP430Fetch::setProgramCounter(uint16 newProgramCounter)
	{
		programCounter = newProgramCounter;

		cpuRegisters[PC].setContents(newProgramCounter);
	}

	MSP430Fetch fetch(0); // start at 0
}