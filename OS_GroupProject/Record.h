#pragma once
#include "AttributeNTFS.h"
class Record {
public:
    void SetReadPoint(int);
    void ReadRecord(); // Bo qua 16 record dau tien
    Record(uint64_t FirstReadPoint, shared_ptr<BPB>);
private:
    std::vector<shared_ptr<AttributeNTFS>> listAttribute;
    uint64_t mask;           // 0x00->0x03 address in Record header
    uint64_t firstAttribute; // 0x14->0x15 
    uint64_t FirstReadPoint;
    shared_ptr<BPB> bootSector;


};

