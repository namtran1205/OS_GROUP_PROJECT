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
    int getStartSector() const;
    shared_ptr<FAT> getFatTable() const;
    vector<shared_ptr<MainEntry>> getMainEntries() const;
    
public:
    void handleAllEntries();

public:
    virtual void readDirectory(int level = 0);
    // bool findEntry(int, MainEntry&) const;
protected:
    shared_ptr<FAT> fatTable;
    std::vector<shared_ptr<MainEntry>> entries;
    uint16_t size; //The size is calculated as "BYTE" unit.

	uint16_t startSector;
    uint16_t numberOfSector;
    int startByte;   
};

class SDET : public RDET
{
public:
    SDET();
    SDET(shared_ptr<FAT>, int);
public:
    void readDirectory(int level = 0) override;
};




    // std::vector<Entry> getActiveEntry() const { return entries; }
    // bool findEntry(int,Entry&) const;
    // //std::vector<std::string> Parse_path(std::string path);
    // std::string getString(std::vector<BYTE>, int, int) const;
    // std::string ReadSector_Data(Volume , int64_t, int, int) const;
    // void AddSector(Volume);
    // void AccessEntry(Volume, int);
    // uint16_t GetStartCluster() const
    // {
    //     return StartCluster;
    // }