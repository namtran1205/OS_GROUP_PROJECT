#include "Content.h"

Content::Content(string extendedName, uint64_t startCluster, shared_ptr<FAT> fatTable)
{
    extendFileName = extendedName;

    //Implement logic for reading datas 
}

string Content::getContent() const
{
    if(extendFileName == "TXT" || extendFileName == "txt")
        return this->content;
    else
    {
        cout << "App to open this file: ";
    }
}
