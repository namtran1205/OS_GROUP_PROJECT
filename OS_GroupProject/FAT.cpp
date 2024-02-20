#include "FAT.h"

FAT::FAT(shared_ptr<BootSector> bootSector)
{
	this->bootSector = bootSector;
}

void FAT::readFatTable()
{
	numberOfFat = bootSector->GetNumberOfFat();
	int fatSize = numberOfFat * bootSector->GetSectorPerFat();
	int64_t ReadPoint = bootSector->getStartSectorOfFAT1() *  bootSector->getBytePerSector();
	std::vector<BYTE> fatBytes = bootSector->getSectorReader()->ReadSector(ReadPoint, fatSize);

	for(int i = 0; i < fatBytes.size(); i += 2)
	{
		datas.push_back(make_pair(fatBytes[i], fatBytes[i+1]));
	}
}

shared_ptr<BootSector> FAT::getBootSector() const
{
    return this->bootSector;
}

vector<uint64_t> FAT::GetFatTable() const
{
	return fatTable;
}
