#include "RDET.h"

RDET::RDET(shared_ptr<FAT> fatTable)
{
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

void RDET::readDirectory()
{
}

