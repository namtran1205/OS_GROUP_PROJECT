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
    //FAT32();
    FAT32(LPCWSTR drive);
    ~FAT32() ;
public:
    

public:
    
    void readVolume() override;
    
    void readRDET();
   
    string toString() const override;
private:

    BootSector* bootSector;
    RDET* rootDirectory;
    FAT* fileAllocationTable;
    SectorReader* sectorReader;
};



