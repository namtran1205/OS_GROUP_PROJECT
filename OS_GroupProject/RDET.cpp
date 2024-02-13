#include "RDET.h"

RDET::RDET(shared_ptr<FAT> fatTable)
{
    this->fatTable = fatTable;

    
}

int RDET::getSize() const
{
    return this->size;
}

int RDET::getStartCluster() const
{
    return this->startCluster;
}

shared_ptr<FAT> RDET::getFAT() const
{
    return this->fatTable;
}

vector<shared_ptr<MainEntry>> RDET::getMainEntries() const
{
    return this->entries;
}

void RDET::readDirectory(int level)
{
    for(int i = 0; i < entries.size(); ++i)
    {
        weak_ptr<MainEntry> entry = entries[i];
        cout << entry.lock()->toString(0);
        //If an entry contains folder, display it
        if(entry.lock()->getSubDirectory() != nullptr)
            entry.lock()->getSubDirectory()->readDirectory(1);
        cout << endl;
    }
}

SDET::SDET(shared_ptr<FAT> fatTable) : RDET(fatTable)
{
    
}

void SDET::readDirectory(int level)
{
    for(int i = 0; i < entries.size(); ++i)
    {
        weak_ptr<MainEntry> entry = entries[i];
        cout << entry.lock()->toString(level);
        //If an entry contains folder, display it
        if(entry.lock()->getSubDirectory() != nullptr)
            entry.lock()->getSubDirectory()->readDirectory(level+1);
        cout << endl;
    }
}

