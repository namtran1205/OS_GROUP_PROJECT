#pragma once
#include "StaticVariable.h"
#include "BootSector.h"
#include "SectorReader.h"

class FAT
{
public:
	void readFatTable(BootSector* bootSector, SectorReader* sectorReader);
	vector<uint32_t> GetFatTbale();
private:
	std::vector<uint32_t> fatTable;
	uint32_t numberOfFat;
};