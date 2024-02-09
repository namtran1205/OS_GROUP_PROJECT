#include "FAT32.h"



FAT32::FAT32()
{
}
FAT32::~FAT32()
{
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