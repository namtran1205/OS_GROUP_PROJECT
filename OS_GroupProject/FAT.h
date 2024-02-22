#pragma once
#include "StaticVariable.h"
#include "BootSector.h"
#include "SectorReader.h"

class FAT
{
public:
	FAT(shared_ptr<BootSector>);
public:
	shared_ptr<BootSector> getBootSector() const;
	vector<uint64_t> GetFatTable() const;
public:
	map<uint64_t,uint64_t> findPath(uint64_t) const;
private:
	shared_ptr<BootSector> bootSector;
	std::vector<uint64_t> fatTable;
	uint32_t numberOfFat;
	vector<pair<BYTE, BYTE>> datas;
};