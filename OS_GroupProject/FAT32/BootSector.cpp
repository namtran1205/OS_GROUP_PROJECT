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
void BootSector::show()
{
    std::cout << "Nf = " << (int)numberOfFat << std::endl;
    std::cout << "Sf = " << SectorPerFat << std::endl;
    std::cout << "Sc = " << (int)SectorPerCluster << std::endl;
    std::cout << "Sb = " << SectorPerBootsector << std::endl;
    std::cout << "Sv = " << SectorVolume << std::endl;
    std::cout << "BytePerSector = " << BytePerSector << std::endl;
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

uint32_t BootSector::GetStartClusterOfRootDirectory() const
{
    return StartClusterOfRDET;
}

int BootSector::ClusterToSector(uint16_t k) const
{
    int i = SectorPerBootsector + SectorPerFat * numberOfFat + (k - 2) * SectorPerCluster;
    return i;
}



void BootSector::ReadFatTable(const std::wstring& drivePath)
{
    int FatSize = numberOfFat * SectorPerFat;
    int64_t ReadPoint = BytePerSector * SectorPerBootsector;
    SectorReader sectorReader;
    std::vector<BYTE> FatSector = sectorReader.ReadSector(drivePath.c_str(), ReadPoint, FatSize);
    for (int i = 0; i < FatSize; i++)
    {
        uint32_t res = Utils::Convert2LitleEndian(FatSector.begin() + 4 * i, 4);
        fatTable.push_back(res);
    }


}

void BootSector::ReadVolume(const std::wstring& drivePath)
{
    SectorReader sectorReader;
    std::vector<BYTE> bootSector = sectorReader.ReadSector(drivePath.c_str(), 0,1);
    this->numberOfFat = (uint8_t)(*(bootSector.begin() + 0x10));
    this->SectorPerFat = Utils::Convert2LitleEndian(bootSector.begin() + 0x24, 4);
    this->SectorPerCluster =(uint8_t)(*(bootSector.begin() + 0xD));
    this->SectorPerBootsector = Utils::Convert2LitleEndian(bootSector.begin() + 0xE, 2);
    this->SectorVolume = Utils::Convert2LitleEndian(bootSector.begin() + 0x20, 4);
    this->BytePerSector = Utils::Convert2LitleEndian(bootSector.begin() + 0xB, 2);
    this->StartClusterOfRDET = Utils::Convert2LitleEndian(bootSector.begin() + 0x2C, 4);
    ReadFatTable(drivePath);
}

std::vector<uint32_t> BootSector::GetFatTable() const
{
    return fatTable;

}

int BootSector::ClusterToSector(uint16_t k) const
{
    int i = SectorPerBootsector + SectorPerFat * numberOfFat + (k - 2) * SectorPerCluster;
    return i;
}

s