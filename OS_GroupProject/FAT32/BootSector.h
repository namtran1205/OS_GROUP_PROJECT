#pragma once
#include "../StaticVariable.h"

class BootSector : public VolumeBootRecord
{
public:
    BootSector();
    ~BootSector();
public:
    uint16_t GetBytePerSector() const;
    uint8_t GetSectorPerCluster() const;
    std::vector<uint32_t> GetFatTable() const;
    uint32_t GetStartClusterOfRootDirectory() const;
    int ClusterToSector(uint16_t) const;

public:
    void SetNumberOfFat(uint8_t num);
    void SetSectorPerCluster(uint8_t sector);
    void SetSectorPerBootSector(uint16_t sector);
    void SetSectorVolume(uint32_t sector);

public:
    void ReadFatTable(const std::wstring &drivePath);
    void 
    ReadVolume(const std::wstring &drivePath);
    void show();

private:
    uint8_t numberOfFat;
    std::vector<uint32_t> fatTable;
    uint32_t SectorPerFat;
    uint8_t SectorPerCluster;
    uint16_t SectorPerBootsector;
    uint32_t SectorVolume;
    uint16_t BytePerSector;
    uint32_t StartClusterOfRDET;
    HANDLE device = INVALID_HANDLE_VALUE;
};