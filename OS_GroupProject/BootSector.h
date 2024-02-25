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
    void setNumberOfFat(uint8_t num);
    void setSectorPerCluster(uint8_t sector);
    void setSectorPerBootSector(uint16_t sector);
    void setSectorVolume(uint32_t sector);
    
public:
    shared_ptr<SectorReader> getSectorReader() const;

    uint64_t getBytePerSector() const;
    uint8_t getSectorPerCluster() const;
    uint32_t getStartSectorOfRDET() const;
    uint32_t getStartSectorOfFAT1() const;
    uint32_t getStartSectorOfDATA() const;
    uint32_t getNumberSectorOfRDET() const;
    uint64_t ClusterToSector(uint64_t) const;
    uint64_t GetSectorPerFat() const;
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
    uint64_t bytePerSector;
    uint32_t startSectorOfFAT1;
    uint32_t startSectorOfRDET;
    uint32_t startSectorOfDATA;
    HANDLE device = INVALID_HANDLE_VALUE;
};