#include "BootSector.h"


BootSector::BootSector(shared_ptr<SectorReader> sectorReader)
{
    this->sectorReader = sectorReader;
    std::vector<BYTE> bootSector = sectorReader->ReadSector(0, 1);
    this->numberOfFat = (uint8_t)(*(bootSector.begin() + 0x10));
    this->numberEntriesOfRDET = Utils::MyINTEGER::Convert2LittleEndian(bootSector.begin() + 0x11, 4);
    this->sectorPerFat = Utils::MyINTEGER::Convert2LittleEndian(bootSector.begin() + 0x24, 4);
    this->sectorPerCluster = (uint8_t)(*(bootSector.begin() + 0xD));
    this->sectorPerBootsector = Utils::MyINTEGER::Convert2LittleEndian(bootSector.begin() + 0xE, 2);
    this->sectorRDET = this->numberEntriesOfRDET * 32 / this->bytePerSector;
    this->sectorVolume = Utils::MyINTEGER::Convert2LittleEndian(bootSector.begin() + 0x20, 4);
    this->bytePerSector = Utils::MyINTEGER::Convert2LittleEndian(bootSector.begin() + 0xB, 2);
    this->startSectorOfFAT1 = this->sectorPerBootsector;
    this->startSectorOfRDET = ClusterToSector((int)Utils::MyINTEGER::Convert2LittleEndian(bootSector.begin() + 0x2C, 4));
    this->startSectorOfDATA = this->startSectorOfRDET + sectorRDET;
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

uint64_t BootSector::getBytePerSector() const
{
    return bytePerSector;
}
uint8_t BootSector::getSectorPerCluster() const
{
    return sectorPerCluster;
}

void BootSector::readVolumeBootRecord()
{
    std::wcout << L"Number of FAT Table - Nf = " << (int)numberOfFat << std::endl;
    std::wcout << L"Sectors per FAT Table - Sf = " << sectorPerFat << std::endl;
    std::wcout << L"Sectors per cluster - Sc = " << (int)sectorPerCluster << std::endl;
    std::wcout << L"Sectors of Boot Sector Sb = " << sectorPerBootsector << std::endl;
    std::wcout << L"Sector of Volume - Sv = " << sectorVolume << std::endl;
    std::wcout << L"Bytes per Sectors - BytePerSector = " << bytePerSector << std::endl;
}

void BootSector::setNumberOfFat(uint8_t num)
{
    numberOfFat = num;
}

void BootSector::setSectorPerCluster(uint8_t sector)
{
    sectorPerCluster = sector;
}

void BootSector::setSectorPerBootSector(uint16_t sector)
{
    sectorPerBootsector = sector;
}

void BootSector::setSectorVolume(uint32_t sector)
{
    sectorVolume = sector;
}

int BootSector::GetNumberOfFat() const
{
    return numberOfFat;
}



uint32_t BootSector::getStartSectorOfRDET() const
{
    return startSectorOfRDET;
}

uint32_t BootSector::getStartSectorOfFAT1() const
{
    return startSectorOfFAT1;
}

uint32_t BootSector::getStartSectorOfDATA() const
{
    return startSectorOfDATA;
}

uint32_t BootSector::getNumberSectorOfRDET() const
{
    return this->sectorRDET;
}

uint64_t BootSector::ClusterToSector(uint64_t k) const
{
    uint64_t i = sectorPerBootsector + sectorPerFat * numberOfFat + (k - 2) * sectorPerCluster;
    return i;
}

uint64_t BootSector::GetSectorPerFat() const
{
    return sectorPerFat;
}

int BootSector::GetSectorPerBootsector() const
{
    return sectorPerBootsector;
}



