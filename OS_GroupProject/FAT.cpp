#include "FAT.h"

FAT::FAT(shared_ptr<BootSector> bootSector)
{
	this->bootSector = bootSector;
}

void FAT::readFatTable()
{
	numberOfFat = bootSector->GetNumberOfFat();
	int FatSize = numberOfFat * bootSector->GetSectorPerFat();
	int64_t ReadPoint = bootSector->GetBytePerSector() * bootSector->GetSectorPerBootsector();
	std::vector<BYTE> FatSector = bootSector->getSectorReader()->ReadSector(ReadPoint, FatSize);
	for (int i = 0; i < FatSize; i++)
	{
		uint32_t res = Utils::Convert2LitleEndian(FatSector.begin() + 4 * i, 4);
		fatTable.push_back(res);
	}
}

vector<uint32_t> FAT::GetFatTbale()
{
	return fatTable;
}
