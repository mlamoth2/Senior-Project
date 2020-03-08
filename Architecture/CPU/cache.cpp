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
		int foundValue;

		for (int wayIterator = 0; wayIterator < cacheData.numWays; ++wayIterator)
		{
			if (cacheData.LRU[index][wayIterator] == way)
			{
				way = wayIterator;

				break;
			}
		}

		foundValue = cacheData.LRU[index][way];

		for (int wayIterator = way; wayIterator > 0; --wayIterator)
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

		for (int sizeIterator = 0; sizeIterator < cacheData.vcSize; ++sizeIterator)
		{
			if ((cacheData.vcCache[sizeIterator].tag == cacheData.vcTag) && (cacheData.vcCache[sizeIterator].validBit == 1))
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

		unsigned int vclruBlock, vcEmpty;

		cacheData.vcTag = address >> cacheData.vcOffsetBits;

		for (int sizeIterator = 0; sizeIterator < cacheData.vcSize; ++sizeIterator)
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

			if (cacheData.vcCache[vclruBlock].dirtyBit == 1)
			{
				unsigned int wbAddress;

				wbAddress = (cacheData.vcCache[vclruBlock].tag) << cacheData.vcOffsetBits;

				cacheData.vcCache[vclruBlock].tag = cacheData.vcTag;
				cacheData.vcCache[vclruBlock].validBit = 1;
				cacheData.vcCache[vclruBlock].index = 0;
				cacheData.vcCache[vclruBlock].dirtyBit = dirtyBit;

				updatevcLRU(vclruBlock);
			}
			else if (cacheData.vcCache[vclruBlock].dirtyBit == 0)
			{
				cacheData.vcCache[vclruBlock].tag = cacheData.vcTag;
				cacheData.vcCache[vclruBlock].validBit = 1;
				cacheData.vcCache[vclruBlock].index = 0;
				cacheData.vcCache[vclruBlock].dirtyBit = dirtyBit;

				updatevcLRU(vclruBlock);
			}
		}
	}
	void MSP430Cache::Request(unsigned int accessType, unsigned int address, unsigned int cacheLevel)   // modify return address, recursively search cache levels
	{
		unsigned int mask = 4294967295;
		unsigned int a; 	
	
		int foundWay;
		bool invalidBlock = false;
		bool hit = false;
		unsigned int lruBlock;

		int vcFound;
		unsigned int swapTemp;
		unsigned int swapAddressL1;
		int swapL1dirtyBit;
		int vcHitWay;
		unsigned int evictAddress;

		cacheData.accessCount++;

		if (accessType & CACHE_READ)
		{
			a = address >> cacheData.offsetBits;
			mask = 4294967295;
			mask = mask >> (cacheData.tagBits + cacheData.offsetBits);

			if (cacheData.cacheAssoc < (cacheData.cacheSize/cacheData.blockSize))
			{
				cacheData.index = (address >> cacheData.offsetBits) & mask;
			}
			else if (cacheData.cacheAssoc >= (cacheData.cacheSize/cacheData.blockSize))
			{
				cacheData.index = 0;
			}

			cacheData.tag = (address >> cacheData.offsetBits) >> cacheData.indexBits;

			for (int wayIterator = 0; wayIterator < cacheData.numWays; ++wayIterator)
			{
				if ((cacheData.cache[cacheData.index][wayIterator].validBit == 1) &&
					(cacheData.cache[cacheData.index][wayIterator].tag == cacheData.tag))   
				{
					hit = true; 
					foundWay = wayIterator;	
					break;
				}
				else
				{
					hit = false;
				}
			}
			if (hit == true)    
			{	
				updateLRU(cacheData.index, foundWay);
			}
			else
			{
				for (int wayIterator = 0; wayIterator < cacheData.numWays; ++wayIterator)
				{
					if ((cacheData.cache[cacheData.index][wayIterator].validBit == 0))
					{
						invalidBlock = true;
						foundWay = wayIterator;
						break;
					}
					else
					{
						invalidBlock = false;
					}	
				}
				if (invalidBlock == true)
				{
//					Request(CACHE_READ, address, L2);
//					read in from L2
				
					cacheData.cache[cacheData.index][foundWay].tag = cacheData.tag;
					cacheData.cache[cacheData.index][foundWay].validBit = 1;
					cacheData.cache[cacheData.index][foundWay].dirtyBit = 0;
					cacheData.cache[cacheData.index][foundWay].index = cacheData.index;

					updateLRU(cacheData.index, foundWay);
				} 
				else
				{
					lruBlock = getLRU(cacheData.index);

					if (cacheData.vcSize != 0)
					{		
						vcHitWay = searchVC(address);

						if (vcHitWay != -1)
						{
							swapAddressL1 = (cacheData.cache[cacheData.index][lruBlock].tag << (cacheData.indexBits + cacheData.offsetBits)) + (cacheData.cache[cacheData.index][lruBlock].index << cacheData.offsetBits);

							swapTemp = swapAddressL1;
							swapL1dirtyBit = cacheData.cache[cacheData.index][lruBlock].dirtyBit;

							cacheData.cache[cacheData.index][lruBlock].dirtyBit = cacheData.vcCache[vcHitWay].dirtyBit;
							cacheData.cache[cacheData.index][lruBlock].tag = ((cacheData.vcCache[vcHitWay].tag) << cacheData.vcOffsetBits) >> (cacheData.offsetBits + cacheData.indexBits);
							cacheData.cache[cacheData.index][lruBlock].validBit = 1;
							cacheData.cache[cacheData.index][lruBlock].index = cacheData.index;

							cacheData.vcCache[vcHitWay].tag = swapAddressL1 >> (cacheData.vcOffsetBits);
							cacheData.vcCache[vcHitWay].dirtyBit = swapL1dirtyBit;
							cacheData.vcCache[vcHitWay].validBit = 1;
							cacheData.vcCache[vcHitWay].index = 0;

							updateLRU(cacheData.index, lruBlock);
							updatevcLRU(vcHitWay);
						}
						else if (vcHitWay == -1)
						{
							evictAddress = (cacheData.cache[cacheData.index][lruBlock].tag << (cacheData.indexBits + cacheData.offsetBits)) + (cacheData.cache[cacheData.index][lruBlock].index << cacheData.offsetBits); 

							writeVC(evictAddress, cacheData.cache[cacheData.index][lruBlock].dirtyBit);

//							Request(CACHE_READ, address, L2);
			
							cacheData.cache[cacheData.index][lruBlock].tag = cacheData.tag;
							cacheData.cache[cacheData.index][lruBlock].validBit = 1; 
							cacheData.cache[cacheData.index][lruBlock].dirtyBit = 0;
							cacheData.cache[cacheData.index][lruBlock].index = cacheData.index;
	
							updateLRU(cacheData.index, lruBlock);
						}
					}	
					else if( cacheData.vcSize == 0 )				
					{
						if ((cacheData.cache[cacheData.index][lruBlock].dirtyBit == 1))
						{
							int wbAddress;
							wbAddress = (cacheData.cache[cacheData.index][lruBlock].tag << (cacheData.offsetBits + cacheData.indexBits)) + (cacheData.cache[cacheData.index][lruBlock].index << cacheData.offsetBits); 
			                   
//							Request(CACHE_WRITE, wbAddress, L2);
							
//			 				Request(CACHE_READ, address, L2);					

							cacheData.cache[cacheData.index][lruBlock].tag = cacheData.tag;
							cacheData.cache[cacheData.index][lruBlock].validBit = 1; 
							cacheData.cache[cacheData.index][lruBlock].dirtyBit = 0;
							cacheData.cache[cacheData.index][lruBlock].index = cacheData.index;
	
							updateLRU(cacheData.index, lruBlock);
						}
						else if ((cacheData.cache[cacheData.index][lruBlock].dirtyBit == 0)) 
						{
//							Request(CACHE_READ, address, L2);

							cacheData.cache[cacheData.index][lruBlock].tag = cacheData.tag;
							cacheData.cache[cacheData.index][lruBlock].validBit = 1; 
							cacheData.cache[cacheData.index][lruBlock].dirtyBit = 0;
							cacheData.cache[cacheData.index][lruBlock].index = cacheData.index;

							updateLRU(cacheData.index, lruBlock);
						}
					}
				}
			}	
		}
		else if (accessType & CACHE_WRITE)
		{
			mask = 4294967295;
			mask = mask >> (cacheData.tagBits + cacheData.offsetBits);

			if (cacheData.cacheAssoc < (cacheData.cacheSize/cacheData.blockSize))
			{
				cacheData.index = (address >> cacheData.offsetBits) & mask;
			}
			else if (cacheData.cacheAssoc >= (cacheData.cacheSize/cacheData.blockSize))
			{
				cacheData.index = 0;
			}

			cacheData.tag = (address >> cacheData.offsetBits) >> cacheData.indexBits;		
		
			for (int waysIterator = 0; waysIterator < cacheData.numWays; ++waysIterator)
			{
				if ((cacheData.cache[cacheData.index][waysIterator].validBit == 1) && (cacheData.cache[cacheData.index][waysIterator].tag == cacheData.tag))   //Condition for Hit
				{	
					hit = true;
					foundWay = waysIterator;
					break;
				}	
				else
				{
					hit = false;
				}
			}
			if (hit == true)
			{
				cacheData.cache[cacheData.index][foundWay].tag = cacheData.tag;
				cacheData.cache[cacheData.index][foundWay].validBit = 1; 
				cacheData.cache[cacheData.index][foundWay].dirtyBit = 1;
				cacheData.cache[cacheData.index][foundWay].index = cacheData.index;

				updateLRU(cacheData.index, foundWay);
			}
			else 
			{
				for (int waysIterator = 0; waysIterator < cacheData.numWays; ++waysIterator)
				{
					if((cacheData.cache[cacheData.index][waysIterator].validBit == 0))
					{	
						invalidBlock = true;
						foundWay = waysIterator;
						break;
					}
					else
					{
						invalidBlock = false;
					}
				}		
				if (invalidBlock == true)
				{
//					Request(CACHE_READ, address, L2);	
	
					cacheData.cache[cacheData.index][foundWay].tag = cacheData.tag;
					cacheData.cache[cacheData.index][foundWay].validBit = 1;		
					cacheData.cache[cacheData.index][foundWay].dirtyBit = 1;
					cacheData.cache[cacheData.index][foundWay].index = cacheData.index;	

					updateLRU(cacheData.index, foundWay);
				} 
				else
				{
					lruBlock = getLRU(cacheData.index);

					if (cacheData.vcSize != 0)
					{
						vcHitWay = searchVC(address);

						if (vcHitWay != -1)  
						{
							swapAddressL1 = (cacheData.cache[cacheData.index][lruBlock].tag << (cacheData.indexBits + cacheData.offsetBits)) + (cacheData.cache[cacheData.index][lruBlock].index << (cacheData.offsetBits));

							swapTemp = swapAddressL1;
							swapL1dirtyBit = cacheData.cache[cacheData.index][lruBlock].dirtyBit;

							cacheData.cache[cacheData.index][lruBlock].dirtyBit = 1;
							cacheData.cache[cacheData.index][lruBlock].tag = cacheData.tag;
							cacheData.cache[cacheData.index][lruBlock].validBit = 1;
							cacheData.cache[cacheData.index][lruBlock].index = cacheData.index;

							cacheData.vcCache[vcHitWay].tag = swapAddressL1 >> (cacheData.vcOffsetBits);
							cacheData.vcCache[vcHitWay].dirtyBit = swapL1dirtyBit;
							cacheData.vcCache[vcHitWay].validBit = 1;
							cacheData.vcCache[vcHitWay].index = 0;

							updateLRU(cacheData.index, lruBlock);
							updatevcLRU(vcHitWay);
						}
						else
						{
				
							evictAddress = (cacheData.cache[cacheData.index][lruBlock].tag << (cacheData.indexBits + cacheData.offsetBits)) + (cacheData.cache[cacheData.index][lruBlock].index << (cacheData.offsetBits));
							writeVC(evictAddress, cacheData.cache[cacheData.index][lruBlock].dirtyBit);

//							Request(CACHE_READ, address, L2);
			
							cacheData.cache[cacheData.index][lruBlock].tag = cacheData.tag;
							cacheData.cache[cacheData.index][lruBlock].validBit = 1; 
							cacheData.cache[cacheData.index][lruBlock].dirtyBit = 1;
							cacheData.cache[cacheData.index][lruBlock].index = cacheData.index;
	
							updateLRU(cacheData.index, lruBlock);

						}
					}	
					else if (cacheData.vcSize == 0)
					{
						if ((cacheData.cache[cacheData.index][lruBlock].dirtyBit == 1))
						{
							int wbAddress;
							wbAddress = (cacheData.cache[cacheData.index][lruBlock].tag << (cacheData.offsetBits + cacheData.indexBits)) + (cacheData.cache[cacheData.index][lruBlock].index << cacheData.offsetBits); 

//							Request(CACHE_WRITE, wbAddress, L2);	

//							Request(CACHE_READ, address, L2);
			
							cacheData.cache[cacheData.index][lruBlock].tag = cacheData.tag;
							cacheData.cache[cacheData.index][lruBlock].validBit = 1; 
							cacheData.cache[cacheData.index][lruBlock].dirtyBit = 1;
							cacheData.cache[cacheData.index][lruBlock].index = cacheData.index;

							updateLRU(cacheData.index, lruBlock);
						}
						else if ((cacheData.cache[cacheData.index][lruBlock].dirtyBit == 0)) 
						{

//							Request(CACHE_READ, address, L2);

							cacheData.cache[cacheData.index][lruBlock].tag = cacheData.tag;
							cacheData.cache[cacheData.index][lruBlock].validBit = 1; 
							cacheData.cache[cacheData.index][lruBlock].dirtyBit = 1;
							cacheData.cache[cacheData.index][lruBlock].index = cacheData.index;

							updateLRU(cacheData.index, lruBlock);
						}
					}
				}
			}
		}
	}
}