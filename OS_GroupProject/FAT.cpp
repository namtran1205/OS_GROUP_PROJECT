#include "FAT.h"

FAT::FAT(shared_ptr<BootSector> bootSector)
{
	this->bootSector = bootSector;
	uint64_t fatSize =  bootSector->GetSectorPerFat();
	int64_t ReadPoint = bootSector->getStartSectorOfFAT1() *  bootSector->getBytePerSector();
	std::vector<BYTE> fatElement = bootSector->getSectorReader()->ReadSector(ReadPoint, fatSize);
	for (int i = 0; i < fatElement.size(); i+=4)
	{
		uint64_t res = Utils::MyINTEGER::Convert2LitleEndian(fatElement.begin() + i, 4);
		fatTable.push_back(res);
	}
}

vector<uint64_t> FAT::findPath(uint64_t startCluster) const
{
	bool isEnd = false;
	vector<uint64_t> res;
	while(isEnd == false)
	{
		res.push_back(startCluster);
		if(fatTable[startCluster] == 0x0FFFFFFF || fatTable[startCluster] == 0x0FFFFFF7)
		{
			isEnd =  true;
		}
		else
			startCluster = fatTable[startCluster];
	}
	return res;
}

shared_ptr<BootSector> FAT::getBootSector() const
{
    return this->bootSector;
}

vector<uint64_t> FAT::GetFatTable() const
{
	return fatTable;
}
