#pragma once
#include "StaticVariable.h"
#include "FileManagementSystem.h"
#include "BPB.h"
#include "Record.h"
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
  


};



