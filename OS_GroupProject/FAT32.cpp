#include "FAT32.h"



FAT32::FAT32()
{
	bootSector = new BootSector();
	rootDirectory = new RDET();
	fileAllocationTable = new FAT();
	sectorReader = new SectorReader();
}
FAT32::~FAT32()
{
    if (!bootSector)
    {
        delete bootSector;
        bootSector = nullptr;
    }
    if (!rootDirectory)
    {
        delete rootDirectory;
        rootDirectory = nullptr;
    }
    if (!fileAllocationTable)
    {
        delete fileAllocationTable;
        fileAllocationTable = nullptr;
    }
    if (!sectorReader)
    {
        delete sectorReader;
        sectorReader = nullptr;
    }
}


void FAT32::readRDET()
{
    this->rootDirectory->show();
}



void FAT32::readVolume(LPCWSTR drive)
{
    sectorReader->SetDirve(drive);
    bootSector->ReadBootSector(sectorReader);
    fileAllocationTable->ReadFatTable(bootSector, sectorReader);
    
    
}
string FAT32::toString() const
{
    return "FAT32";
}