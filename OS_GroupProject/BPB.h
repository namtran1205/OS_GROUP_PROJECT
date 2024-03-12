#pragma once
#include "StaticVariable.h"
#include "VolumeBootRecord.h"
#include "SectorReader.h"
//vùng Bios Parameter Block
class BPB : public VolumeBootRecord
{
public:
    BPB(shared_ptr<SectorReader>);
    ~BPB();
public:
    void readVolumeBootRecord() override;
public:
    shared_ptr<SectorReader> GetSectorReader() const;
public:
    uint64_t getSectorPerCluster() const; // trả về số sector mỗi cluster
    uint64_t getBytePerSector() const; // trả về số byte mỗi sector
    uint64_t getMFTsize() const; // trả về kích thước MFT entry (đơn vị byte)
    uint64_t getStartMFTCluster() const; // trả về cluster bắt đầu của MFT
    uint64_t getSizeOfVolume() const; // trả về kích thước phân vùng
    uint64_t getMFTMirror() const;
    uint64_t getEndMFT();
private:
    std::wstring driveName;
    uint64_t BytePerSector;    // 0xB 2 byte
    uint64_t SectorPerCluster; // 0xD->0xE
    int64_t MFTsize;           // 0x40->0x40 kích thước thật là 2^abs(MFTsize) 
    uint64_t SectorVolume;     // 0x28->0x2F
    uint64_t StartMFTCluster;  // 0x30->0x37
    uint64_t StartMFTMirrorCluster;
    shared_ptr<SectorReader> sectorReader;
    

};

