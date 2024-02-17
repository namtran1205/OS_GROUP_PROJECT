#include "RDET.h"

RDET::RDET(shared_ptr<FAT> fatTable)
{
    this->fatTable = fatTable;
    this->startSector = fatTable->getBootSector()->getStartSectorOfRDET();
    this->startByte = startSector * fatTable->getBootSector()->getBytePerSector();
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
    if (fatTable != nullptr)
    {

        int numberOfEntries = size / StaticVariable::BYTES_PER_ENTRY;
        int64_t startBytesRDET = this->fatTable->getBootSector()->getStartSectorOfRDET() * this->fatTable->getBootSector()->getBytePerSector();
        // int bytePerSector = StaticVariable::BYTES_PER_ENTRY / fatTable->getBootSector()->getBytePerSector();

        SectorReader sectorReader;
        vector<BYTE> vectorBytesOfDirectory = sectorReader.ReadSector(startBytesRDET, numberOfSector);
        //Ignore the first entry of RDET because it's store the detailed of disk.
        for (int i = 1; i < numberOfEntries; ++i)
        {
            //Get the vector bytes at this offset.
            vector<BYTE> vectorBytes = vector<BYTE>((vectorBytesOfDirectory[32 * i],vectorBytesOfDirectory[32 * i] + 31));

            //When we read the empty entry, it means we dont need to read anymore.
            if(vectorBytes[0] == 0x00)
                return;

            //If the entry is deleted, go to the next entry
            if(vectorBytes[0] == 0xE5)
                continue;

            //Get the subEntry of MainEntry if the name is LFN
            if(vectorBytes[0xB] == 0x0F)
            {
                vector<shared_ptr<SubEntry>> listSubEntries;
                while(vectorBytes[0xB] == 0x0F)
                {
                    shared_ptr<SubEntry> subEntry = make_shared<SubEntry>(vectorBytes);
                    listSubEntries.push_back(subEntry);
                    ++i;
                    vectorBytes = vector<BYTE>((vectorBytesOfDirectory[32 * i],vectorBytesOfDirectory[32 * i] + 31));
                }
                shared_ptr<MainEntry> mainEntry = make_shared<MainEntry>(fatTable, vectorBytes);
                mainEntry->addSubEntry(listSubEntries);
                this->entries.push_back(mainEntry);
            }
            else
            {
                this->entries.push_back(make_shared<MainEntry>(fatTable, vectorBytes));
            }
        }
    }
}

void RDET::readDirectory(int level)
{
    for(int i = 0; i < entries.size(); ++i)
    {
        weak_ptr<MainEntry> entry = entries[i];
        wcout << entry.lock()->toString(0);
        //If an entry contains folder, display it
        if(entry.lock()->getSubDirectory() != nullptr)
            entry.lock()->getSubDirectory()->readDirectory(1);
        cout << endl;
    }
}

// bool RDET::findEntry(int id, MainEntry& a) const
// {
//     for (int i = 0; i < entries.size(); i++)
//        if (entries[i]->isActiveEntry() && entries[i]->getID() == id)
//             return true;
//     return false;
// }

SDET::SDET(shared_ptr<FAT> fatTable, uint16_t startByte) : RDET(fatTable)
{
    this->startByte = startByte;
    if (fatTable != nullptr)
    {
        SectorReader read = *(this->getFatTable()->getBootSector()->getSectorReader());
        vector<BYTE> vectorBytesOfDirectory = read.collectBytesUntilNull(startByte);
        int numberOfEntries = vectorBytesOfDirectory.size() / StaticVariable::BYTES_PER_ENTRY;


        //Ignore the first two entry of SDET because it's store the detailed of current disk and its father's disk
        for (int i = 2; i < numberOfEntries; ++i)
        {
            //Get the vector bytes at this offset.
            vector<BYTE> vectorBytes = vector<BYTE>((vectorBytesOfDirectory[32 * i],vectorBytesOfDirectory[32 * i] + 31));

            //When we read the empty entry, it means we dont need to read anymore.
            if(vectorBytes[0] == 0x00)
                return;

            //If the entry is deleted, go to the next entry
            if(vectorBytes[0] == 0xE5)
                continue;

            //Get the subEntry of MainEntry if the name is LFN
            if(vectorBytes[0xB] == 0x0F)
            {
                vector<shared_ptr<SubEntry>> listSubEntries;
                while(vectorBytes[0xB] == 0x0F)
                {
                    shared_ptr<SubEntry> subEntry = make_shared<SubEntry>(vectorBytes);
                    listSubEntries.push_back(subEntry);
                    ++i;
                    vectorBytes = vector<BYTE>((vectorBytesOfDirectory[32 * i],vectorBytesOfDirectory[32 * i] + 31));
                }
                shared_ptr<MainEntry> mainEntry = make_shared<MainEntry>(fatTable, vectorBytes);
                mainEntry->addSubEntry(listSubEntries);
                this->entries.push_back(mainEntry);
            }
            else
            {
                this->entries.push_back(make_shared<MainEntry>(fatTable, vectorBytes));
            }
        }
    }
}

void SDET::readDirectory(int level)
{
    for(int i = 0; i < entries.size(); ++i)
    {
        weak_ptr<MainEntry> entry = entries[i];
        wcout << entry.lock()->toString(level);
        //If an entry contains folder, display it
        if(entry.lock()->getSubDirectory() != nullptr)
            entry.lock()->getSubDirectory()->readDirectory(level+1);
        cout << endl;
    }
}

