#include "Content.h"

Content::Content(wstring extendedName, uint64_t startCluster, shared_ptr<FAT> fatTable)
{
    extendFileName = extendedName;

    //Implement logic for reading datas
}

wstring Content::getContent() const
{
    if(extendFileName == Utils::convertCharToWString("TXT") || extendFileName == Utils::convertCharToWString("txt"))
        return this->content;
    else
    {
        cout << "App to open this file: ";
    }
}
