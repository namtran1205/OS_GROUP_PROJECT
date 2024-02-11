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

string RDET::toString() const
{
    return "RDET";
}

void RDET::readDirectory()
{
    for(int i = 0; i < entries.size(); ++i)
    {
        weak_ptr<MainEntry> entry = entries[i];
        entry.lock()->toString(0);
    }
}

SDET::SDET(shared_ptr<FAT> fatTable) : RDET(fatTable)
{
}

string SDET::toString() const
{
    return "SDET";
}
