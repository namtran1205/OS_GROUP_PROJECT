#pragma once
#include "StaticVariable.h"
#include "BPB.h"
class HeaderAttribute
{
public:
    HeaderAttribute(uint64_t ,vector<BYTE>&, shared_ptr<BPB>);
public:
    void setContentAddress(uint64_t);
    void setContentSize(uint64_t);
public:
    shared_ptr<BPB> GetBPB() const; // trả về BPB
    uint64_t getSize() const; // trả về kích thước attribute
    uint64_t getMask() const; // trả về mask
    bool isResident() const; // trả về đây có phải là attribute resident hay không
    uint64_t getID() const; // trả về ID của attribute để phân biệt loại attribute
    uint64_t GetAttributeAddress() const; // trả về địa chỉ (offset) bắt đầu của attribute
    uint64_t getContentAddress() const; // trả về địa chỉ (offset) bắt đầu của phần nội dung thuộc attribute
    uint64_t getContentSize() const; // trả về kích thước phần nội dung của attribute

private:
    uint64_t attributeAddress;
    uint64_t ID;               // 0x0->0x3 
    uint64_t Size;             // 0x4->0x7
    uint64_t nonResidentFlag;  // 0x8->0x8 
    uint64_t maskFlag;         // 0xC->0xD
    uint64_t contentSize;      // kích thước phần nội dung của attribute
    uint64_t contentAddress;    // địa chỉ (offset) bắt đầu của phần nội dung thuộc attribute
    shared_ptr<BPB> bootSector; // vùng BPB
};

class AttributeNTFS {

public:
    AttributeNTFS();
    AttributeNTFS(shared_ptr<HeaderAttribute>, vector<BYTE>&);
    
    virtual uint64_t getNextAttributeAddress() const; // trả về offset bắt đầu của attribute tiếp theo

    // sử dụng 5 hàm virtual để lấy các thông số từ 3 loại attribute, sẽ giải thích cụ thể bên dưới
    virtual uint32_t getFlag() const; 
    virtual uint64_t getParentID() const; 
    virtual std::wstring getFileName() const;
    virtual void getBasicInfo();
    virtual std::pair<std::wstring, std::wstring> getLastWriteTime() const ;
    virtual uint64_t getSize();


    shared_ptr<HeaderAttribute> getBasicHeader() const; // trả về HeaderAttribute
    bool isResident() const;
protected:
    uint64_t AttributeAddress; // địa chỉ bắt đầu của attribute
    shared_ptr<HeaderAttribute> basicHeader; // HeaderAttribute

};

class Standard_Info : public AttributeNTFS
{
public:
    Standard_Info(shared_ptr<HeaderAttribute>, vector<BYTE>&);
    uint32_t getFlag() const override; // trả về cờ báo trạng thái: system, file,...
    std::pair<std::wstring, std::wstring> getLastWriteTime() const override; // trả về thời gian truy cập file
private:
    uint32_t flag; // 0x32 -> 0x35
    std::pair<std::wstring, std::wstring> lastWriteTime;

};

class File_Name : public AttributeNTFS
{
public:
    File_Name(shared_ptr<HeaderAttribute>, vector<BYTE>&);
    std::wstring getFileName() const override; // trả về tên của entry
    uint64_t getParentID() const override; // trả về thứ tự entry cha của nó
private:
    std::wstring NameOfFile; // 0x66 8 byte
    uint64_t parentID;    //0x0 6 byte // parentID là MTFentry parent

};

class Data : public AttributeNTFS
{
public:
    Data(shared_ptr<HeaderAttribute>,vector<BYTE>&);
public:
    void getBasicInfo() override; // in nội dung
    uint64_t getSize() override; // trả về kích thước, thường là kích thước file
private:
    std::string residentContent;
    vector<std::pair<uint64_t, uint64_t>> runsList;
    uint64_t endingPoint;
};




