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
    FAT32();
    ~FAT32() override;
public:
    

public:
    
    void readVolume(LPCWSTR drive) override;
    
    void readRDET();
   
    string toString() const override;
private:

    BootSector* bootSector;
    RDET* rootDirectory;
    FAT* fileAllocationTable;
    SectorReader* sectorReader;
};



