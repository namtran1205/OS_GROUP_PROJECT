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
    content = Utils::MySTRING::convertBytesToWstring(vector<BYTE>(dataContents.begin() + 2, dataContents.end()));
}

wstring Content::getContent() const
{
    if(extendFileName == L"TXT" || extendFileName == L"txt")
    {
        return this->content ;
    }
    return L"App to open this file: ";
}