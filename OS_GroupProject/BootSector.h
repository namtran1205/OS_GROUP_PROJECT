#pragma once
#include "StaticVariable.h"
#include "VolumeBootRecord.h"
#include "SectorReader.h"


class BootSector : public VolumeBootRecord
{
public:
    BootSector(shared_ptr<SectorReader>);
    ~BootSector();
public:
    void SetNumberOfFat(uint8_t num);
    void SetSectorPerCluster(uint8_t sector);
    void SetSectorPerBootSector(uint16_t sector);
    void SetSectorVolume(uint32_t sector);
    
public:
    shared_ptr<SectorReader> getSectorReader() const;

    uint16_t GetBytePerSector() const;
    uint8_t GetSectorPerCluster() const;
    uint32_t GetStartClusterOfRootDirectory() const;

    int ClusterToSector(uint16_t) const;
    int GetSectorPerFat() const;
    int GetSectorPerBootsector() const;
    int GetNumberOfFat() const;
    
public:
    void readVolumeBootRecord() override;


private:
    shared_ptr<SectorReader> sectorReader;
    uint8_t numberOfFat;
    uint32_t numberEntriesOfRDET;
    uint32_t sectorPerFat;
    uint8_t sectorPerCluster;
    uint16_t sectorPerBootsector;
    uint32_t sectorVolume;
    uint32_t sectorRDET;
    uint16_t bytePerSector;
    uint32_t startClusterOfFAT1;
    uint32_t startClusterOfRDET;
    uint32_t startClusterOfDATA;
    HANDLE device = INVALID_HANDLE_VALUE;
};