#pragma once
#include "../StaticVariable.h"


class FAT
{
public:
	void ReadFatTable(BootSector* bootSector, SectorReader* sectorReader);

private:
	std::vector<uint32_t> fatTable;
	uint32_t numberOfFat;
};