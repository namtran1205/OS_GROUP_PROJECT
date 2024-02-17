#include "RDET.h"

RDET::RDET(shared_ptr<FAT> fatTable)
{
    this->fatTable = fatTable;
    this->startSector = fatTable->getBootSector()->getStartSectorOfRDET();
    this->numberOfSector = fatTable->getBootSector()->getNumberSectorOfRDET();
    this->size = numberOfSector * fatTable->getBootSector()->getBytePerSector();
    handleAllEntries();
}

int RDET::getSize() const
{
    return this->size;
}

int RDET::getNumberOfSector() const
{
    return this->numberOfSector;
}

int RDET::getStartSector() const
{
    return this->startSector;
}

shared_ptr<FAT> RDET::getFatTable() const
{
    return this->fatTable;
}

vector<shared_ptr<MainEntry>> RDET::getMainEntries() const
{
    return this->entries;
}

void RDET::handleAllEntries()
{
    int numberOfEntries = size / StaticVariable::BYTES_PER_ENTRY;

    for(int i = 0; i < numberOfEntries; ++i)
    {
    }
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

bool RDET::findEntry(int id, MainEntry& a) const
{
    for (int i = 0; i < entries.size(); i++)
       if (entries[i]->isActiveEntry() && entries[i]->getID() == id)
            return true;
    return false;
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

