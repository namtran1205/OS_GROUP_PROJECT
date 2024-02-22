#include "FAT32.h"

FAT32::FAT32(LPCWSTR drive)
{
    sectorReader = make_shared<SectorReader>(drive);
    bootSector = make_shared<BootSector>(sectorReader);
    fileAllocationTable = make_shared<FAT>(bootSector);
    rootDirectory = make_shared<RDET>(fileAllocationTable);
    currentDirectory.push(rootDirectory);
}

FAT32::~FAT32()
{
    //No need to delete any pointers because we're using smart pointer C++
}

void FAT32::readVolumeBootRecord()
{
    bootSector->readVolumeBootRecord();
}

void FAT32::readDirectory()
{
    currentDirectory.top().lock()->readDirectory();
}

bool FAT32::changeDirectory(wstring folderName)
    {
    
        for(auto entry : currentDirectory.top().lock()->getMainEntries())
        {
            if(entry->getAttribute()->isDirectory() && entry->getFullName() == folderName)
            {
                currentDirectory.push(entry->getSubDirectory());
                return true;
            }
        }
        return false;
    }

bool FAT32::accessFile(wstring fileName)
{
    for(auto entry : currentDirectory.top().lock()->getMainEntries())
    {
        if(!entry->getAttribute()->isDirectory() && entry->getFullName() == fileName)
        {
            if(entry->getContent())
            {
                wcout << entry->getContent()->getContent();
                wcout << endl;
                return true;
            }
        }
    }
    return false;
}

bool FAT32::returnPreviousDirectory()
{
    if(this->currentDirectory.size() == 1)
        return false;
    this->currentDirectory.pop();
    return true;
}

wstring FAT32::toString() const
{
    return L"FAT32";
}


