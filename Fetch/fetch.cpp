#include "..\Common\typedefs.hpp"
#include "..\Common\opcodes.hpp"

#include "fetch.hpp"

namespace Fetcher
{

		MSP430Fetch::MSP430Fetch(uint16 programCounter)
		{
			this->programCounter = programCounter;
		}

		MSP430Fetch::~MSP430Fetch()
		{
		
		}
}