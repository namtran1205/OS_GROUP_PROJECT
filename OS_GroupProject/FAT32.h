#pragma once
#include "StaticVariable.h"
#include "FileManagementSystem.h"
#include "BootSector.h"
#include "RDET.h"
#include "FAT.h"
#include "SectorReader.h"

class Entry;
class RDET;

class FAT32 : public FileManagementSystem
{
public:
    FAT32(LPCWSTR drive);
    ~FAT32();
public:
    wstring toString() const override;
public:
    void readVolumeBootRecord() override;

    void readDirectory() override;

    bool changeDirectory(wstring folderName) override;

    bool accessFile(wstring fileName) override;

    bool returnPreviousDirectory() override;
private:
    shared_ptr<SectorReader> sectorReader;
    shared_ptr<BootSector> bootSector;
    shared_ptr<FAT> fileAllocationTable;
    shared_ptr<RDET> rootDirectory;
private:
    stack<weak_ptr<RDET>> currentDirectory;
};