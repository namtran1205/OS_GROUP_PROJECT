#include "BootSector.h"

BootSector::BootSector()
{
    BytePerSector = 512;
    

}
BootSector::~BootSector()
{
    if (device != INVALID_HANDLE_VALUE)
    {
        CloseHandle(device);
    }
};

uint16_t BootSector::GetBytePerSector() const
{
    return BytePerSector;
}
uint8_t BootSector::GetSectorPerCluster() const
{
    return SectorPerCluster;
}

void BootSector::SetNumberOfFat(uint8_t num)
{
    numberOfFat = num;
}

void BootSector::SetSectorPerCluster(uint8_t sector)
{
    SectorPerCluster = sector;
}

void BootSector::SetSectorPerBootSector(uint16_t sector)
{
    SectorPerBootsector = sector;
}

void BootSector::SetSectorVolume(uint32_t sector)
{
    SectorVolume = sector;
}

int BootSector::GetNumberOfFat()
{
    return numberOfFat;
}

uint32_t BootSector::GetStartClusterOfRootDirectory() const
{
    return StartClusterOfRDET;
}

int BootSector::ClusterToSector(uint16_t k) const
{
    int i = SectorPerBootsector + SectorPerFat * numberOfFat + (k - 2) * SectorPerCluster;
    return i;
}

int BootSector::GetSectorPerFat()
{
    return SectorPerFat;
}

int BootSector::GetSectorPerBootsector()
{
    return SectorPerBootsector;
}



