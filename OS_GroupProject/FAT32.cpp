#include "FAT32.h"



//FAT32::FAT32()
//{
//	sectorReader = new SectorReader();
//	bootSector = new BootSector();
//	rootDirectory = new RDET();
//	fileAllocationTable = new FAT();
//}
FAT32::FAT32(LPCWSTR drive)
{
    sectorReader = make_shared<SectorReader>(drive);
    bootSector = make_shared<BootSector>(sectorReader);
    fileAllocationTable =  make_shared<FAT>(bootSector);
    rootDirectory =  make_shared<RDET>(fileAllocationTable);

}
FAT32::~FAT32()
{
    //No need to delete any pointers because we're using smart pointer C++
}




void FAT32::readVolume()
{
    bootSector->readVolumeBootRecord();
    fileAllocationTable->readFatTable();
}

void FAT32::readDirectory()
{
    rootDirectory->readDirectory();
}

string FAT32::toString() const
{
    return "FAT32";
}