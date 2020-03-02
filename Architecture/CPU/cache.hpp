#pragma once

namespace Cache
{
	typedef struct
	{
		int validBit;
		int dirtyBit;
		unsigned int tag;
		unsigned int index;     
	}MSP430Block;

	typedef struct
	{
		int blockSize;
		int cacheSize;
		int cacheAssoc;
		int vcSize;
	
		int numSets;
		int numWays;
		unsigned int offsetBits;
		unsigned int indexBits;
		unsigned int tagBits;
		unsigned int address;
		unsigned int index;
		unsigned int tag;

		unsigned int vcTagBits;
		unsigned int vcIndexBits;
		unsigned int vcOffsetBits;
		unsigned int vcTag;
		unsigned int vcIndex; 

		int accessCount;

		int** LRU; // least recently used

		int* vcLRU;

		MSP430Block** cache; // the actual cache

		MSP430Block* vcCache; // victim cache
	}MSP430CacheData;
			
	class MSP430Cache
	{
	public:

		MSP430Cache(int blockSize, int cacheSize, int cacheAssociativity, int vcSize);
		~MSP430Cache();

		int getCacheLevel()
		{
			return cacheLevel;
		}
		void setCacheLevel(int level)
		{
			cacheLevel = level;
		}

	private:	
					
		void initCache();
		void Request(unsigned int accessType, unsigned int address, unsigned int cacheLevel);
		void initLRU();
		void updateLRU(unsigned int index, int way);
		unsigned int getLRU(unsigned int index) const;

		void initVC();
		void initvcLRU();
		void updatevcLRU(int way);
		void writeVC(unsigned int address, int dirtyBit);
		unsigned int getvcLRU() const;
		int searchVC(unsigned int address);

		int cacheLevel;

		MSP430CacheData cacheData;
	}; 

	MSP430Cache Level1CacheCode(4, 1024, 4, 1024);
	MSP430Cache Level1CacheData(4, 1024, 4, 1024);

	MSP430Cache Level2CacheCode(4*4, 1024*4, 4, 1024*4);
	MSP430Cache Level2CacheData(4*4, 1024*4, 4, 1024*4);

	MSP430Cache Level3Cache(4*8, 1024*8, 4, 1024*8);
};