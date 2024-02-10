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

vector<shared_ptr<Entry>> RDET::getEntries() const
{
    return this->entries;
}

string RDET::toString() const
{
    return "RDET";
}

void RDET::readDirectory()
{
}

SDET::SDET(shared_ptr<FAT> fatTable) : RDET(fatTable)
{
}

string SDET::toString() const
{
    return "SDET";
}
