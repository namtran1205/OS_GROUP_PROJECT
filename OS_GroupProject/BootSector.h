#pragma once
#include "StaticVariable.h"
#include "VolumeBootRecord.h"
#include "SectorReader.h"


class BootSector : public VolumeBootRecord
{
public:
    BootSector();
    BootSector(SectorReader*);
    ~BootSector();
public:
    void SetNumberOfFat(uint8_t num);
    void SetSectorPerCluster(uint8_t sector);
    void SetSectorPerBootSector(uint16_t sector);
    void SetSectorVolume(uint32_t sector);
    
public:
    uint16_t GetBytePerSector() const;
    uint8_t GetSectorPerCluster() const;
    uint32_t GetStartClusterOfRootDirectory() const;
    int ClusterToSector(uint16_t) const;
    int GetSectorPerFat() const;
    int GetSectorPerBootsector() const;
    int GetNumberOfFat() const;

public:
    void readBootSector();


private:
    uint8_t numberOfFat;
    uint32_t SectorPerFat;
    uint8_t SectorPerCluster;
    uint16_t SectorPerBootsector;
    uint32_t SectorVolume;
    uint16_t BytePerSector;
    uint32_t StartClusterOfRDET;
    HANDLE device = INVALID_HANDLE_VALUE;
};