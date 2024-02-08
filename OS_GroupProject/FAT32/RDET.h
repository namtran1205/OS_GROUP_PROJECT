#pragma once
#include "../StaticVariable.h"


class RDET
{
public:
    RDET(const uint32_t& startCluster);
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
    void show();


private:
    std::vector<Entry*> entries;
    uint16_t size;
	uint16_t startCluster;

   
};
