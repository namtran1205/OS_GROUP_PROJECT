#pragma once
#include "vector"
class Record {
private:
    std::vector<Attribute> listAttribute;
    uint32_t mask;           // 0x00->0x03 address in Record header
    uint32_t firstAttribute; // 0x14->0x15 
public:

};

class NTFSVolumn {
private:
    uint32_t BytePerSector;    // 0xB 2 byte
    uint32_t SectorPerCluster; // 0xD->0xE
    int32_t MFTsize;           // 0x40->0x40  the true size is 2^abs(MFTsize)
    uint64_t SectorVolume;     // 0x28->0x2F
    uint64_t StartMFTCluster;  // 0x30->0x37
    std::vector<Record> ListRecord;
};

class Attribute {
private:
    uint32_t AttributeID;      // 0x0->0x3 
    uint32_t AttributeSize;    // 0x4->0x7
    uint32_t residentFlag;     // 0x8->0x8 
    uint32_t maskFlag;         // 0xC->0xD

};

