#pragma once
#include "../StaticVariable.h"
#include "BootSector.h"

class FAT
{
public:
	void ReadFatTable(BootSector*, LPCWSTR drive);

private:
	std::vector<uint32_t> fatTable;
	uint32_t numberOfFat;
};