#include "FAT.h"

FAT::FAT(shared_ptr<BootSector> bootSector)
{
}

void FAT::readFatTable(shared_ptr<BootSector> bootSector, shared_ptr<SectorReader> sectorReader)
{
	numberOfFat = bootSector->GetNumberOfFat();
	int FatSize = numberOfFat * bootSector->GetSectorPerFat();
	int64_t ReadPoint = bootSector->GetBytePerSector() * bootSector->GetSectorPerBootsector();
	std::vector<BYTE> FatSector = sectorReader->ReadSector(ReadPoint, FatSize);
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
