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
    content = Utils::MySTRING::AppToOpen(extendedName);
}

wstring Content::getContent() const
{
    if(extendFileName == L"TXT" || extendFileName == L"txt")
    {
        wstring res;
        vector<uint64_t> clusterToRead = fatTable->findPath(startCluster);
        bool isUTF16 = false;
        bool isUTF8withBOM = false;
        for(int i = 0; i < clusterToRead.size(); ++i)
        {
            uint64_t readPoint = fatTable->getBootSector()->ClusterToSector(clusterToRead[i]) * fatTable->getBootSector()->getBytePerSector();
            vector<BYTE> dataContents = fatTable->getBootSector()->getSectorReader()->collectBytesUntilNull(readPoint);
            //vector<BYTE> dataContents = fatTable->getBootSector()->getSectorReader()->ReadSector(readPoint, fatTable->getBootSector()->getSectorPerCluster());
            if (i == 0)
            {
                //UTF16 - Little Endian or UTF8 with BOM
                if (dataContents[0] == 0xFF && dataContents[1] == 0xFE)
                {
                    isUTF16 = true;
                    res += Utils::MySTRING::convertBytesToWstring(vector<BYTE>(dataContents.begin() + 2, dataContents.end()));
                }
                //UTF8 with BOM
                else if (dataContents[0] == 0xEF && dataContents[1] == 0xBB)
                {
                    isUTF8withBOM = true;
                    res += wstring(dataContents.begin() + 2, dataContents.end());
                }
                //UTF8
                else
                {
                    res += wstring(dataContents.begin(), dataContents.end());
                }
            }
            else
            {
                if (isUTF16)
                {
                    res += Utils::MySTRING::convertBytesToWstring(vector<BYTE>(dataContents.begin() + 2, dataContents.end()));
                }
                else if (isUTF8withBOM)
                {
                    res += wstring(dataContents.begin() + 2, dataContents.end());
                }
                else
                {
                    res += wstring(dataContents.begin(), dataContents.end());
                }
            }
        }
        return res;
    }
    return L"App to open this file: " +  content;
    wcin.ignore();
}