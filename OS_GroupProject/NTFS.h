#pragma once
#include "StaticVariable.h"
#include "FileManagementSystem.h"
#include "BPB.h"

using namespace std;





class NTFS : public FileManagementSystem
{
public:
    NTFS(LPCWSTR);
    ~NTFS();
public:
    wstring toString() const override;
public:
    void readVolumeBootRecord() override;

    void readDirectory() override;

    bool changeDirectory(wstring folderName) override;

    bool accessFile(wstring fileName) override;
    
    bool returnPreviousDirectory() override;

private:
    shared_ptr<BPB> bootSector;
    shared_ptr<SectorReader> sectorReader;
    shared_ptr<Record> MTF;


};

class Record {
public:
    void SetReadPoint(int);
    void ReadRecord(); // Bo qua 16 record dau tien
    Record(uint64_t FirstReadPoint);
private:
    std::vector<shared_ptr<AttributeNTFS>> listAttribute;
    uint64_t mask;           // 0x00->0x03 address in Record header
    uint64_t firstAttribute; // 0x14->0x15 
    uint64_t FirstReadPoint;


};

class HeaderAttribute
{
public:
    void readHeaderAttribute(uint64_t Address);
private:
    uint64_t ID;      // 0x0->0x3 
    uint64_t Size;    // 0x4->0x7
    uint64_t residentFlag;     // 0x8->0x8 
    uint64_t maskFlag;         // 0xC->0xD
};

class AttributeNTFS {

public:
    virtual void ReadBasicInfo();
    AttributeNTFS(shared_ptr<HeaderAttribute>, uint64_t AttributeAddress);
    uint64_t getNextAttributeAddress() const;

protected:
    uint64_t AttributeAddress;
    shared_ptr<HeaderAttribute> basicHeader;

};

class Standard_Info : public AttributeNTFS
{
private:
    uint32_t flag; // 0x32 -> 0x35
public:
    void ReadBasicInfo();
    Standard_Info(shared_ptr<HeaderAttribute>, uint64_t AttributeAddress);

};

class File_Name : public AttributeNTFS 
{
private:
    uint32_t LengthOfName; //0x64
    std::wstring NameOfFile; // 0x66 8 byte
public:
    void ReadBasicInfo();
   File_Name(shared_ptr<HeaderAttribute>, uint64_t AttributeAddress);

    
};

class Data : public AttributeNTFS
{
    uint32_t type; //0x8 : if value = 0 -> resident
public:
    void ReadBasicInfo();
   
};



