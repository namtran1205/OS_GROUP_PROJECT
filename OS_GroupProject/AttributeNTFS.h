#pragma once
#include "StaticVariable.h"
class HeaderAttribute
{
public:
    HeaderAttribute(uint64_t Address);
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
    Data(shared_ptr<HeaderAttribute>, uint64_t AttributeAddress);
public:
    void ReadBasicInfo();

};




