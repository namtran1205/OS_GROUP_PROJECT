#pragma once
#include "StaticVariable.h"
#include "BootSector.h"
#include "SectorReader.h"

class FAT
{
public:
	FAT(shared_ptr<BootSector>);

public:
	void readFatTable();
	vector<uint32_t> GetFatTbale();

private:
	shared_ptr<BootSector> bootSector;
	std::vector<uint32_t> fatTable;
	uint32_t numberOfFat;
};