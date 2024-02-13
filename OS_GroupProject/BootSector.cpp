#include "BootSector.h"


BootSector::BootSector(shared_ptr<SectorReader> sectorReader)
{
    this->sectorReader = sectorReader;
    std::vector<BYTE> bootSector = sectorReader->ReadSector(0, 1);
    this->numberOfFat = (uint8_t)(*(bootSector.begin() + 0x10));
    this->numberEntriesOfRDET = Utils::Convert2LitleEndian(bootSector.begin() + 0x11, 2);
    this->sectorPerFat = Utils::Convert2LitleEndian(bootSector.begin() + 0x24, 4);
    this->sectorPerCluster = (uint8_t)(*(bootSector.begin() + 0xD));
    this->sectorPerBootsector = Utils::Convert2LitleEndian(bootSector.begin() + 0xE, 2);
    this->sectorRDET = this->numberEntriesOfRDET * 32 / this->bytePerSector;
    this->sectorVolume = Utils::Convert2LitleEndian(bootSector.begin() + 0x20, 4);
    this->bytePerSector = Utils::Convert2LitleEndian(bootSector.begin() + 0xB, 2);
    this->startClusterOfFAT1 = this->sectorPerBootsector;
    this->startClusterOfRDET = this->startClusterOfFAT1 + this->sectorPerFat * this->numberOfFat;
    this->startClusterOfDATA = this->startClusterOfRDET + sectorRDET;
    sectorReader->SetByteOfSector(bytePerSector);
}
BootSector::~BootSector()
{
    if (device != INVALID_HANDLE_VALUE)
    {
        CloseHandle(device);
    }
};

shared_ptr<SectorReader> BootSector::getSectorReader() const
{
    return this->sectorReader;
}

uint16_t BootSector::GetBytePerSector() const
{
    return bytePerSector;
}
uint8_t BootSector::GetSectorPerCluster() const
{
    return sectorPerCluster;
}

void BootSector::readVolumeBootRecord()
{
    std::cout << "Number of FAT Table - Nf = " << (int)numberOfFat << std::endl;
    std::cout << "Sectors per FAT Table - Sf = " << sectorPerFat << std::endl;
    std::cout << "Sectors per cluster - Sc = " << (int)sectorPerCluster << std::endl;
    std::cout << "Sectors of Boot Sector Sb = " << sectorPerBootsector << std::endl;
    std::cout << "Sector of Volume - Sv = " << sectorVolume << std::endl;
    std::cout << "Bytes per Sectors - BytePerSector = " << bytePerSector << std::endl;
}

void BootSector::SetNumberOfFat(uint8_t num)
{
    numberOfFat = num;
}

void BootSector::SetSectorPerCluster(uint8_t sector)
{
    sectorPerCluster = sector;
}

void BootSector::SetSectorPerBootSector(uint16_t sector)
{
    sectorPerBootsector = sector;
}

void BootSector::SetSectorVolume(uint32_t sector)
{
    sectorVolume = sector;
}

int BootSector::GetNumberOfFat() const
{
    return numberOfFat;
}



uint32_t BootSector::GetStartClusterOfRootDirectory() const
{
    return startClusterOfRDET;
}

int BootSector::ClusterToSector(uint16_t k) const
{
    int i = sectorPerBootsector + sectorPerFat * numberOfFat + (k - 2) * sectorPerCluster;
    return i;
}

int BootSector::GetSectorPerFat() const
{
    return sectorPerFat;
}

int BootSector::GetSectorPerBootsector() const
{
    return sectorPerBootsector;
}



