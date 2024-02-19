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
    string toString() const override;
    void readVolume() override;
   
private:

    shared_ptr<BootSector> bootSector;
    shared_ptr<RDET> rootDirectory;
    shared_ptr<FAT> fileAllocationTable;
    shared_ptr<SectorReader> sectorReader;
};



