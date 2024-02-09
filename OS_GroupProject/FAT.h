#pragma once
#include "StaticVariable.h"
#include "BootSector.h"
#include "SectorReader.h"

class FAT
{
public:
	void ReadFatTable(BootSector* bootSector, SectorReader* sectorReader);

private:
	std::vector<uint32_t> fatTable;
	uint32_t numberOfFat;
};