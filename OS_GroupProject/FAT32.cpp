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
    sectorReader = new SectorReader(drive);
    bootSector = new BootSector(sectorReader);
    rootDirectory = new RDET();
    fileAllocationTable = new FAT();

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




void FAT32::readVolume()
{
    bootSector->readBootSector();
    fileAllocationTable->readFatTable(bootSector, sectorReader);
    rootDirectory->readDirectory();
}
string FAT32::toString() const
{
    return "FAT32";
}