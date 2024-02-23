#include "FAT.h"

FAT::FAT(shared_ptr<BootSector> bootSector)
{
	this->bootSector = bootSector;
	numberOfFat = bootSector->GetNumberOfFat();
	int fatSize = numberOfFat * bootSector->GetSectorPerFat();
	int64_t ReadPoint = bootSector->getStartSectorOfFAT1() *  bootSector->getBytePerSector();
	std::vector<BYTE> fatElement = bootSector->getSectorReader()->ReadSector(ReadPoint, fatSize);
	for (int i = 0; i < fatSize; i++)
	{
		uint64_t res = Utils::MyINTEGER::Convert2LitleEndian(fatElement.begin() + 4 * i, 4);
		fatTable.push_back(res);
	}
}

map<uint64_t,uint64_t> FAT::findPath(uint64_t startCluster) const
{
	bool isEnd = false;
	map<uint64_t, uint64_t> res;
	uint64_t endCluster = startCluster; 
	res.insert(make_pair(startCluster, endCluster));
	while(isEnd == true)
	{
		if(fatTable[endCluster] == 0xFFFFFFF || fatTable[endCluster] == 0xFFFFFF7)
			isEnd =  true;
		else
		{
			res.insert(make_pair(endCluster, fatTable[endCluster]));
			endCluster = fatTable[endCluster];
		}
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
