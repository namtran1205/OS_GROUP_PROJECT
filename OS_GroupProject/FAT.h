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
	shared_ptr<BootSector> getBootSector() const;
	vector<uint64_t> GetFatTable() const;

private:
	shared_ptr<BootSector> bootSector;
	std::vector<uint64_t> fatTable;
	uint32_t numberOfFat;
	vector<pair<BYTE, BYTE>> datas;
};