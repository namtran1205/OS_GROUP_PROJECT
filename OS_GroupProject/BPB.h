#pragma once
#include "StaticVariable.h"
#include "VolumeBootRecord.h"
#include "SectorReader.h"
class BPB : public VolumeBootRecord
{
public:
    BPB(shared_ptr<SectorReader>);
    ~BPB();
public:
    void readVolumeBootRecord() override;

private:
    std::wstring driveName;
    uint32_t BytePerSector;    // 0xB 2 byte
    uint32_t SectorPerCluster; // 0xD->0xE
    uint32_t MFTsize;           // 0x40->0x40  the true size is 2^abs(MFTsize) 
    uint64_t SectorVolume;     // 0x28->0x2F
    uint64_t StartMFTCluster;  // 0x30->0x37
    shared_ptr<SectorReader> sectorReader;
    

};

