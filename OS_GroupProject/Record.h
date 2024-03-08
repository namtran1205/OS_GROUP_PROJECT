#pragma once
#include "AttributeNTFS.h"


class Record {
public:
    
    // Bo qua 16 record dau tien
    Record(uint64_t FirstReadPoint, shared_ptr<BPB>);
public:
    uint64_t GetNextAddressRecord() const;
    std::string getMask() const;
    uint64_t getFlag(); // flag is flag of filename attribute -> archive of directory
    std::wstring getName();
    int isUse(); 
    bool isFolder();
    void printFileContent();
    uint64_t getParentID();
    uint64_t getStatus();
    uint64_t getSize();
    std::pair<std::wstring, std::wstring> getLastWriteTime();
private:
    std::vector<shared_ptr<AttributeNTFS>> listAttribute;
    std::string mask;           // 0x00->0x03 address in Record header
    uint64_t firstAttribute; // 0x14->0x15 
    uint64_t FirstReadPoint;
    shared_ptr<BPB> bootSector;
    int status; // status is in use


};

