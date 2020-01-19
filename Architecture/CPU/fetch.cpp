#include "..\..\Common\defines.hpp"
#include "..\..\Common\typedefs.hpp"
#include "..\..\Common\opcodes.hpp"

#include "fetch.hpp"

#include <cstring>

using namespace std;

namespace Fetcher
{
	MSP430Fetcher::MSP430Fetcher(uint16 programCounter)
	{
		this->programCounter = programCounter;
	}

	MSP430Fetcher::~MSP430Fetcher()
	{
		
	}
}