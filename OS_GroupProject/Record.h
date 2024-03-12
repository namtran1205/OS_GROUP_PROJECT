#pragma once
#include "AttributeNTFS.h"

// Record là entry của MFT (MasterFileTable)
class Record {
public:
    
    // Bo qua 16 record dau tien
    Record(uint64_t FirstReadPoint, shared_ptr<BPB>);
public:
    uint64_t GetNextAddressRecord() const;
    std::string getMask() const;
    uint64_t getFlag(); // trả về flag trong attribute standard_info
    std::wstring getName(); // trả về tên của mft entry
    int isUse(); // trả về entry có được sử dụng
    bool isFolder(); // trả về entry có phải folder không
    void printFileContent(); // in nội dung file nếu đó là entry quản lí file
    uint64_t getParentID(); // trả về thứ tự mft entry cha của nó
    uint64_t getStatus();
    uint64_t getSize();
    std::pair<std::wstring, std::wstring> getLastWriteTime(); // trả về thời gian truy cập
private:
    std::vector<shared_ptr<AttributeNTFS>> listAttribute;
    std::string mask;           // 0x00->0x03 address in Record header
    uint64_t firstAttribute; // 0x14->0x15 
    uint64_t FirstReadPoint;
    shared_ptr<BPB> bootSector;
    int status; // status is in use

};

