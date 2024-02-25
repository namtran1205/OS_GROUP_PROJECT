#pragma once
#include "StaticVariable.h"
#include "BPB.h"
class HeaderAttribute
{
public:
    HeaderAttribute(uint64_t Address, shared_ptr<BPB>);
public:
    void setContentAddress(uint64_t);
    void setContentSize(uint64_t);
public:
    shared_ptr<BPB> GetBPB() const;
    uint64_t getSize() const;
    uint64_t getMask() const;
    bool isResident() const;
    uint64_t getID() const;
    uint64_t GetAttributeAddress() const;
    uint64_t getContentAddress() const;
    uint64_t getContentSize() const;

private:
    uint64_t attributeAddress;
    uint64_t ID;               // 0x0->0x3 
    uint64_t Size;             // 0x4->0x7
    uint64_t nonResidentFlag;  // 0x8->0x8 
    uint64_t maskFlag;         // 0xC->0xD
    uint64_t contentSize;
    uint64_t contentAddress;
    shared_ptr<BPB> bootSector;
};

class AttributeNTFS {

public:
    AttributeNTFS();
    AttributeNTFS(shared_ptr<HeaderAttribute>);
    uint64_t getNextAttributeAddress() const;

protected:
    uint64_t AttributeAddress;
    shared_ptr<HeaderAttribute> basicHeader;

};

class Standard_Info : public AttributeNTFS
{
public:
    Standard_Info(shared_ptr<HeaderAttribute>);
private:
    uint32_t flag; // 0x32 -> 0x35

};

class File_Name : public AttributeNTFS
{
public:
    File_Name(shared_ptr<HeaderAttribute>);
    std::wstring getFileName() const;
private:
    std::wstring NameOfFile; // 0x66 8 byte

};

class Data : public AttributeNTFS
{
public:
    Data(shared_ptr<HeaderAttribute>);
public:
    void getBasicInfo();

};




