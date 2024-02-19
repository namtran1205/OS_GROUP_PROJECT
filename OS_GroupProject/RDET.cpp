#include "RDET.h"

RDET::RDET()
{
}

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

uint64_t RDET::getStartSector() const
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

        int64_t startBytesRDET = this->fatTable->getBootSector()->getStartSectorOfRDET() * this->fatTable->getBootSector()->getBytePerSector();
        SectorReader read = *(this->getFatTable()->getBootSector()->getSectorReader());
        vector<BYTE> vectorBytesOfDirectory = read.collectBytesUntilNull(startBytesRDET);
        int numberOfEntries = vectorBytesOfDirectory.size() / StaticVariable::BYTES_PER_ENTRY;

        //Ignore the first entry of RDET because it's store the detailed of disk.
        for (int i = 1; i < numberOfEntries; ++i)
        {
            //Get the vector bytes at this offset.
            vector<BYTE> vectorBytes(vectorBytesOfDirectory.begin() + (32 * i), vectorBytesOfDirectory.begin() + (32 * i) + 32);

            // //When we read the empty entry, it means we dont need to read anymore.
            if (vectorBytes[0] == 0x00)
            {
                return;
            }

            // //If the entry is deleted, go to the next entry
            if(vectorBytes[0] == 0xE5)
                continue;

            // //Get the subEntry of MainEntry if the name is LFN
            if (vectorBytes[0xB] == 0x0F)
            {
                vector<shared_ptr<SubEntry>> listSubEntries;
                while (vectorBytes[0xB] == 0x0F)
                {
                    shared_ptr<SubEntry> subEntry = make_shared<SubEntry>(vectorBytes);
                    listSubEntries.push_back(subEntry);
                    ++i;
                    vectorBytes = vector<BYTE>(vectorBytesOfDirectory.begin() + (32 * i), vectorBytesOfDirectory.begin() + (32 * i) + 32);
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
    // entries.erase(entries.begin());
}

void RDET::readDirectory(int level)
{
    for(int i = 0; i < entries.size(); ++i)
    {
        weak_ptr<MainEntry> entry = entries[i];
        cout << entry.lock()->toString(0);
        cout << endl;

        //If an entry contains folder, display it
         if(entry.lock()->getSubDirectory() != nullptr)
             entry.lock()->getSubDirectory()->readDirectory(1);
    }
}


SDET::SDET() : RDET()
{

}

SDET::SDET(shared_ptr<FAT> fatTable, uint64_t startByte) : SDET()
{
    this->fatTable = fatTable;
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
            vector<BYTE> vectorBytes(vectorBytesOfDirectory.begin() + (32 * i), vectorBytesOfDirectory.begin() + (32 * i) + 32);

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
                    vectorBytes = vector<BYTE>(vectorBytesOfDirectory.begin() + (32 * i), vectorBytesOfDirectory.begin() + (32 * i) + 32);
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
        cout << entry.lock()->toString(level);
        cout << endl;
        //If an entry contains folder, display it
         if(entry.lock()->getSubDirectory() != nullptr)
         {
             entry.lock()->getSubDirectory()->readDirectory(level+1);
         }
        //  string s;
        //  cin >> s;
        cout << endl;
    }
}

