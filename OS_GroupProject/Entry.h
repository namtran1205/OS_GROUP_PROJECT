#pragma once
#include <iostream>
#include <chrono>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include "Volumn.h"
#include <wincrypt.h>

class Entry;
class RDET;


enum AttributeFAT32
{
    READ_ONLY = 0x01,
    HIDDEN = 0x02,
    SYSTEM = 0x04,
    VOLLABEL = 0x08,
    DIRECTORY = 0x10,
    ARCHIVE = 0x20
};

class Entry
{
    public:
        Entry() {};
        Entry(std::vector<BYTE>);
        std::string getMainName() const { return mainName; }
        std::string getExtendedName() const { return extendedName; }
        int getSize() const { return sizeData; }
        bool is_Folder() const { return isFolder; }
        //uint16_t GetStartCluster() const
        //{
        //    return StartCluster;
        //}
        //std::vector<Entry*> getListSubEntry() const
        //{
        //    return ListSubEntry;
        //}
        //bool findEntry(int, Entry&) const;
        int GetID() const;
        
    private:
        char reserved;
        std::string mainName;
        std::string extendedName;
        AttributeFAT32 attribute;
        std::chrono::system_clock::time_point DateCreated;
        std::chrono::system_clock::time_point LastAccess;
        std::chrono::system_clock::time_point DatedUpdated;
        int sizeData;
        int ID; // create ID for entry
	    bool isFolder;
        bool isEmpty;
        bool isLabel;
        bool isDeleted;
        
        bool isSubEntry;
        char seq;
        std::wstring unicode;
        std::string extend1;
        std::string extend2;
        
       
        //std::vector<Entry*> ListSubEntry;
        //uint16_t StartCluster;
      

};

class SubEntry : public Entry
{
private:
    char seq;
    
};


class RDET
{
public:
    RDET(const uint32_t& startCluster);
    std::vector<Entry> getActiveEntry() const { return entries; }
    bool findEntry(int,Entry&) const;
    //std::vector<std::string> Parse_path(std::string path);
    std::string getString(std::vector<BYTE>, int, int) const;
    std::string ReadSector_Data(Volume , int64_t, int, int) const;
    void AddSector(Volume);
    void AccessEntry(Volume, int);
    uint16_t GetStartCluster() const
    {
        return StartCluster;
    }
private:
    std::vector<Entry> entries;
	uint16_t StartCluster;
   
};






