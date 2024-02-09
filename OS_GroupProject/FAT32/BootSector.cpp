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

void BootSector::ReadBootSector(SectorReader sectorReader)
{
    std::vector<BYTE> bootSector = sectorReader.ReadSector(0, 1);
    this->numberOfFat = (uint8_t)(*(bootSector.begin() + 0x10));
    this->SectorPerFat = Utils::Convert2LitleEndian(bootSector.begin() + 0x24, 4);
    this->SectorPerCluster = (uint8_t)(*(bootSector.begin() + 0xD));
    this->SectorPerBootsector = Utils:: Convert2LitleEndian(bootSector.begin() + 0xE, 2);
    this->SectorVolume = Utils:: Convert2LitleEndian(bootSector.begin() + 0x20, 4);
    this->BytePerSector = Utils:: Convert2LitleEndian(bootSector.begin() + 0xB, 2);
    this->StartClusterOfRDET = Utils::Convert2LitleEndian(bootSector.begin() + 0x2C, 4);
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



