#include "Content.h"

Content::Content()
{
    
}

Content::Content(wstring extendedName, uint64_t startCluster, shared_ptr<FAT> fatTable)
{
    extendFileName = extendedName;
    //Implement logic for reading datas
    int numberOfSectorToRead = (fatTable->findPath(startCluster)[startCluster] - startCluster) + 1;
    uint64_t readPoint = fatTable->getBootSector()->ClusterToSector(startCluster) * fatTable->getBootSector()->getBytePerSector();
    vector<BYTE> dataContents = fatTable->getBootSector()->getSectorReader()->ReadSector(readPoint, numberOfSectorToRead);
    content = wstring(dataContents.begin(), dataContents.end());
}

wstring Content::getContent() const
{
    if(extendFileName == Utils::convertCharToWString("TXT") || extendFileName == Utils::convertCharToWString("txt"))
    {
        return this->content;
    }
    
    wstring temp1 = L"";
    return temp1;
}