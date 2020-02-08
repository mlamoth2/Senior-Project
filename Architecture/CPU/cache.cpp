#include "..\..\Common\defines.hpp"
#include "..\..\Common\typedefs.hpp"

#include "cache.hpp"

#include <math.h>

namespace Cache
{
	MSP430Cache::MSP430Cache(int blockSize, int cacheSize, int cacheAssociativity, int vcSize)
	{
		cacheData.blockSize = blockSize;
		cacheData.cacheSize = cacheSize;
		cacheData.cacheAssoc = cacheAssociativity;
		cacheData.vcSize = vcSize;

		if (cacheAssociativity < (cacheSize/blockSize))
		{
			cacheData.numWays = cacheAssociativity;
			cacheData.numSets = (cacheSize / (blockSize * cacheAssociativity));
		}
		else if (cacheAssociativity >= (cacheSize / blockSize))
		{
			cacheData.numWays = cacheAssociativity;
			cacheData.numSets = 1;
		}

		if (cacheAssociativity < (cacheSize / blockSize))
		{
			cacheData.offsetBits = log2 (blockSize);

			cacheData.indexBits = log2 (cacheSize / (blockSize * cacheAssociativity));	

			cacheData.tagBits = 32 - cacheData.offsetBits - cacheData.indexBits;
		}
		else if (cacheAssociativity >= (cacheSize / blockSize) )
		{
			cacheData.offsetBits = log2 (blockSize);
			cacheData.indexBits = 0;
			cacheData.tagBits = 32 - cacheData.offsetBits - cacheData.indexBits;
		}

		cacheData.vcOffsetBits = log2 (blockSize);

		cacheData.vcTagBits = 32 - cacheData.vcOffsetBits;

		cacheData.cache = new MSP430Block*[cacheData.numSets];

		for (int setIterator = 0; setIterator < cacheData.numSets; ++setIterator)
		{
			cacheData.cache[setIterator] = new MSP430Block[cacheData.numWays];
		}

		cacheData.LRU = new int*[cacheData.numSets];

		for (int setIterator = 0; setIterator < cacheData.numSets; ++setIterator)
		{
			cacheData.LRU[setIterator] = new int[cacheData.numWays];
		}
	
		initCache();
	
		initLRU();

		if (cacheData.vcSize != 0)
		{  	
			initVC();
			initvcLRU();
		}

		cacheData.accessCount = 0;
	}

	void MSP430Cache::initCache()
	{
		// this could potentially be optimized with a memset

		for (int setIterator = 0; setIterator < cacheData.numSets; ++setIterator)
		{
			for (int wayIterator = 0; wayIterator < cacheData.numWays; ++wayIterator)
			{
				cacheData.cache[wayIterator][setIterator].validBit = 0;
			}
		}
	}
	
	void MSP430Cache::initLRU()
	{
		int currentLRU = 0;

		for (int setIterator = 0; setIterator < cacheData.numSets; ++setIterator)
		{
			currentLRU = cacheData.numWays - 1;

			for (int wayIterator = 0; wayIterator < cacheData.numWays; ++wayIterator)
			{
				cacheData.LRU[setIterator][wayIterator] = currentLRU--;
			}
		}
	}

	void MSP430Cache::updateLRU(unsigned int index, int way)
	{
		int foundValue, way;

		for (int wayIterator = 0; wayIterator < cacheData.numWays; ++wayIterator)
		{
			if (cacheData.LRU[index][wayIterator] == way)
			{
				way = wayIterator;

				break;
			}
		}

		foundValue = cacheData.LRU[index][way];

		for(int wayIterator = way; wayIterator > 0; --wayIterator)
		{
			cacheData.LRU[index][wayIterator] = cacheData.LRU[index][wayIterator-1]; 
		}

		cacheData.LRU[index][0] = foundValue;
	}

	unsigned int MSP430Cache::getLRU(unsigned int index) const
	{
		return cacheData.LRU[index][cacheData.numWays - 1];
	}

	int MSP430Cache::searchVC(unsigned int address)
	{
		int returnValue = -1;

		cacheData.vcTag = address >> cacheData.vcOffsetBits;

		for(int sizeIterator = 0; sizeIterator < cacheData.vcSize; ++sizeIterator)
		{
			if((cacheData.vcCache[sizeIterator].tag == cacheData.vcTag) && (cacheData.vcCache[sizeIterator].validBit == 1))
			{
				returnValue = sizeIterator;

				break;
			}
		}

		return returnValue;
	}

	void MSP430Cache::initVC()
	{
		cacheData.vcCache = new MSP430Block[cacheData.vcSize];

		for (int victimCacheIterator = 0; victimCacheIterator < cacheData.vcSize; ++victimCacheIterator)
		{
			cacheData.vcCache[victimCacheIterator].validBit = 0;
		}
	}

	void MSP430Cache::initvcLRU()
	{
		cacheData.vcLRU = new int[cacheData.vcSize];

		int currentSize = cacheData.vcSize - 1;

		for (int sizeIterator = 0; sizeIterator < cacheData.vcSize; ++sizeIterator)
		{
			cacheData.vcLRU[sizeIterator] = currentSize--;
		}
	}

	void MSP430Cache::updatevcLRU(int way)
	{
		int dataEntry = 0;

		int foundEntry = 0;

		for (int sizeIterator = 0; sizeIterator < cacheData.vcSize; ++sizeIterator)
		{
			if (cacheData.vcLRU[sizeIterator] == way)
			{ 
				foundEntry = sizeIterator;

				break;
			}
		}

		dataEntry = cacheData.vcLRU[foundEntry];

		for (int lruIterator = foundEntry; lruIterator > 0; --lruIterator)
		{
			cacheData.vcLRU[lruIterator] = cacheData.vcLRU[lruIterator-1];
		}

		cacheData.vcLRU[0] = dataEntry;
	}

	unsigned int MSP430Cache::getvcLRU() const
	{
		return cacheData.vcLRU[cacheData.vcSize - 1];
	}

	void MSP430Cache::writeVC(unsigned int address, int dirtyBit)
	{
		bool vcInvalid = false;

		unsigned int vclruBlock, vcInvalid, vcEmpty;

		cacheData.vcTag = address >> cacheData.vcOffsetBits;

		// Check for invalid block

		for(int sizeIterator = 0; sizeIterator < cacheData.vcSize; ++sizeIterator)
		{
			if (cacheData.vcCache[sizeIterator].validBit == 0)
			{
				vcInvalid = false;  
				vcEmpty = sizeIterator;
				break;
			}
			else
			{
				vcInvalid = true;
			}
		}

		if (vcInvalid == false)
		{
			cacheData.vcCache[vcEmpty].tag = cacheData.vcTag;
			cacheData.vcCache[vcEmpty].validBit = 1;
			cacheData.vcCache[vcEmpty].dirtyBit = dirtyBit;
			cacheData.vcCache[vcEmpty].index = 0;

			updatevcLRU(vcEmpty);
		}
		else
		{
			vclruBlock = getvcLRU();

			if(cacheData.vcCache[vclruBlock].dirtyBit == 1)
			{
				unsigned int wbAddress;

				wbAddress = (cacheData.vcCache[vclruBlock].tag) << cacheData.vcOffsetBits;

				cacheData.vcCache[vclruBlock].tag = cacheData.vcTag;
				cacheData.vcCache[vclruBlock].validBit = 1;
				cacheData.vcCache[vclruBlock].index = 0;
				cacheData.vcCache[vclruBlock].dirtyBit = dirtyBit;

				updatevcLRU(vclruBlock);
			}
			else if(cacheData.vcCache[vclruBlock].dirtyBit == 0)
			{
				cacheData.vcCache[vclruBlock].tag = cacheData.vcTag;
				cacheData.vcCache[vclruBlock].validBit = 1;
				cacheData.vcCache[vclruBlock].index = 0;
				cacheData.vcCache[vclruBlock].dirtyBit = dirtyBit;

				updatevcLRU(vclruBlock);
			}

		}
	
	}
	void MSP430Cache::Request(const char *c, unsigned int address)  
	{
		
	}
}