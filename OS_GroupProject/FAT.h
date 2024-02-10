#pragma once
#include "StaticVariable.h"
#include "BootSector.h"
#include "SectorReader.h"

class FAT
{
public:
	FAT(shared_ptr<BootSector>);

public:
	void readFatTable(shared_ptr<BootSector> bootSector, shared_ptr<SectorReader> sectorReader);
	vector<uint32_t> GetFatTbale();

private:
	std::vector<uint32_t> fatTable;
	uint32_t numberOfFat;
};