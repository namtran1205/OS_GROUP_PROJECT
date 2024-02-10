#include "RDET.h"

RDET::RDET()
{
}

RDET::RDET(const uint32_t &startCluster)
{
}

int RDET::getSize() const
{
    return this->size;
}

int RDET::getStartCluster() const
{
    return 0;
}

vector<Entry *> RDET::getEntries() const
{
    return this->entries;
}

void RDET::readDirectory()
{
}

