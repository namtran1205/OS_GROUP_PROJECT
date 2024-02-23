#pragma once
#include "StaticVariable.h"
#include "FileManagementSystem.h"
#include "BPB.h"

using namespace std;


// class Record;
// class NTFSVolume;
// class AttributeNTFS;
// class Data;
// class File_Name;
// class Standard_Info;



// class Record {
// private:
//     std::vector<AttributeNTFS> listAttribute;
//     uint32_t mask;           // 0x00->0x03 address in Record header
//     uint32_t firstAttribute; // 0x14->0x15 
//     int FirstReadPoint;
// public:
//     void SetReadPoint(int);
//     void ReadRecord(); // Bo qua 16 record dau tien

// };

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
    // std::vector<Record> ListRecord;


};

// class AttributeNTFS {
// protected:
//     uint32_t ID;      // 0x0->0x3 
//     uint32_t Size;    // 0x4->0x7
//     uint32_t residentFlag;     // 0x8->0x8 
//     uint32_t maskFlag;         // 0xC->0xD
// public:
//     virtual void ReadBasicInfo();
    


// };

// class Standard_Info : public AttributeNTFS
// {
//     uint32_t flag; // 0x32 -> 0x35
// public:
//     void ReadBasicInfo();
//      void ReadStandard_info();



// };
// class File_Name : public AttributeNTFS 
// {
//     uint32_t LengthOfName; //0x64
//     std::wstring NameOfFile; // 0x66 8 byte
// public:
//     void ReadBasicInfo();
//     void ReadFile_Name();

   

// };
// class Data : public AttributeNTFS
// {
//     uint32_t type; //0x8 : if value = 0 -> resident
// public:
//     void ReadBasicInfo();
//     void ReadData();
// };



