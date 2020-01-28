#pragma once

namespace Cache
{
	typedef struct
	{
		int16 validBit;
		int16 dirtyBit;
		uint16 tag;
		uint16 index;     
	}MSP430Block;

	typedef struct
	{
		int16 blockSize;
		int16 cacheSize;
		int16 cacheAssoc;
		int16 vcSize;
	
		int16 numSets;
		int16 numWays;
		uint16 offsetBits;
		uint16 indexBits;
		uint16 tagBits;
		uint16 address;
		uint16 index;
		uint16 tag;

		uint16 vcTagBits;
		uint16 vcIndexBits;
		uint16 vcOffsetBits;
		uint16 vcTag;
		uint16 vcIndex; 

		int16 accessCount;

		int16** LRU; // least recently used

		int16* vcLRU;

		MSP430Block** cache; // the actual cache

		MSP430Block* vcCache; // victim cache
	}MSP430CacheData;
			
	class MSP430Cache
	{
	public:

		MSP430Cache(int16 blockSize, int16 cacheSize, int16 cacheAssociativity, int16 vcSize, int8 additionalCacheFlags);
		~MSP430Cache();

	private:	
					
		void initCache();
		void Request(const char *c, uint16 address);
		void initLRU();
		void updateLRU(uint16 index, int16 way);
		uint16 getLRU(uint16 index);

		void initVC();
		void initvcLRU();
		void updatevcLRU(int16 way);
		void writeVC(uint16 address, int16 dirtyBit);
		uint16 getvcLRU();
		int16 searchVC(uint16 address);

		MSP430CacheData* cacheData; // 0 L1 cache, 1 L2 cache, 2 L3 cache
	}; 
};