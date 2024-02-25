#include "Content.h"

Content::Content()
{
    
}

Content::Content(wstring extendedName, uint64_t startCluster, shared_ptr<FAT> fatTable)
{
    extendFileName = extendedName;
    //Implement logic for reading datas
    this->fatTable = fatTable;
    this->startCluster = startCluster;
}

wstring Content::getContent() const
{
    if(extendFileName == L"TXT" || extendFileName == L"txt")
    {
        wstring res;
        vector<uint64_t> clusterToRead = fatTable->findPath(startCluster);
        for(auto cluster : clusterToRead)
        {
            uint64_t readPoint = fatTable->getBootSector()->ClusterToSector(cluster) * fatTable->getBootSector()->getBytePerSector();
            vector<BYTE> dataContents = fatTable->getBootSector()->getSectorReader()->ReadSector(readPoint, fatTable->getBootSector()->getSectorPerCluster());
            res += Utils::MySTRING::convertBytesToWstring(vector<BYTE>(dataContents.begin() + 2, dataContents.end()));
        }
        return res;
    }
    return L"App to open this file: ";
}