#pragma once
#include "StaticVariable.h"
#include "Entry.h"
#include "FAT.h"

class RDET
{
public:
    RDET(shared_ptr<FAT>);

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
public:
    int getSize() const;
    int getStartCluster() const;
    vector<shared_ptr<Entry>> getEntries() const;

public:
    virtual string toString() const;
public:
    void readDirectory();
protected:
    std::vector<shared_ptr<Entry>> entries;
    uint16_t size;
	uint16_t startCluster;
    uint16_t clusterNumber;   
};

class SDET : public RDET
{
public:
    SDET(shared_ptr<FAT>);
public:
    string toString() const override;
};
