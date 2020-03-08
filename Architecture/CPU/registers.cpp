#include "..\..\Common\defines.hpp"
#include "..\..\Common\typedefs.hpp"

#include "location.hpp"
#include "registers.hpp"

using namespace Location;

namespace Registers
{
	MSP430CPURegisters::MSP430CPURegisters()
	{
	}

	MSP430CPURegisters::~MSP430CPURegisters()
	{
	}

	MSP430CPURegisters cpuRegisters[MAX_REGISTERS];
}