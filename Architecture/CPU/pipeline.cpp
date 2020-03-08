#include "..\..\Common\defines.hpp"
#include "..\..\Common\typedefs.hpp"
#include "..\..\Common\operand.hpp"
#include "..\..\Common\opcodes.hpp"

using namespace MSP430_Opcodes;
using namespace MSP430_Operands;

#include "decoder.hpp"
#include "fetch.hpp"
#include "execute.hpp"
#include "location.hpp"
#include "memory.hpp"
#include "registers.hpp"

using namespace Decode;
using namespace Execute;
using namespace Fetch;
using namespace Location;
using namespace Memory;

namespace Pipeline
{
	// todo: Think of out of order execution?
	// just order it fetch, decode, execute

	void runCPUPipeline()
	{
		MSP430_Opcodes::MSP430_Opcode currentOpcode;

		while (1) // just loop forever for now
		{
			Fetch::fetch.Fetch(&currentOpcode);

			Fetch::fetch.advanceProgramCounter(currentOpcode.getLength()); // could be overriden by execute
			Decode::decode.
		}
	}
}