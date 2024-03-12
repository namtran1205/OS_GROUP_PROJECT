#pragma once
#include "StaticVariable.h"
#include "FileManagementSystem.h"
#include "BPB.h"

#include"DirectoryTree.h"
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
    shared_ptr<BPB> bootSector; // vùng Bios Parameter Block
    shared_ptr<SectorReader> sectorReader;
    shared_ptr<DirectoryTree> directoryTree; // cây thư mục
    uint64_t currentFileNodeID; // địa chỉ bắt đầu của entry quản lí thư mục đang được trỏ đến hiện tại của phân vùng


};



