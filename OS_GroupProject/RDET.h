#pragma once
#include "StaticVariable.h"
#include "FAT.h"
#include "Entry.h"

class RDET;
class SDET;
class MainEntry;

class RDET
{
public:
    RDET();
    RDET(shared_ptr<FAT>);


public:
    //The size of RDET is stored as number of "BYTE" unit.
    int getSize() const;
    int getNumberOfSector() const;
    uint64_t getStartSector() const;
    shared_ptr<FAT> getFatTable() const;
    vector<shared_ptr<MainEntry>> getMainEntries() const;
    
public:
    void handleAllEntries();

public:
    virtual void readDirectory(int level = 0);
protected:
    shared_ptr<FAT> fatTable;
    std::vector<shared_ptr<MainEntry>> entries;
    uint16_t size; //The size is calculated as "BYTE" unit.
	uint64_t startSector;
    uint16_t numberOfSector;
    uint64_t startByte;
};

class SDET : public RDET
{
public:
    SDET();
    SDET(shared_ptr<FAT>, uint64_t);
public:
    void readDirectory(int level = 0) override;
};
