#pragma once
#include <iostream>
#include <chrono>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <cmath>
#include <string>
#include <vector>
#include "Volumn.h"
#include <wincrypt.h>
enum Attribute;
class Entry;
class RDET;


enum Attribute
{
    READ_ONLY = 0x01,
    HIDDEN = 0x02,
    SYSTEM = 0x04,
    VOLLABEL = 0x08,
    DIRECTORY = 0x10,
    ARCHIVE = 0x20,
};


class Entry
{
    public:
        Entry();
        std::string getMainName() { return mainName; }
        std::string getExtendedName() { return extendedName; }
        int getSize() { return sizeData; }
        bool is_Folder() { return isFolder; }
        uint16_t GetStartCluster()
        {
            return StartCluster;
        }
        std::vector<Entry> getListSubEntry()
        {
            return ListSubEntry;
        }
        bool findEntry(int, Entry&);
        int GetID();
        
    private:
        char reserved;
        std::string mainName;
        std::string extendedName;
        Attribute attribute;
        std::chrono::system_clock::time_point DateCreated;
        std::chrono::system_clock::time_point LastAccess;
        std::chrono::system_clock::time_point DatedUpdated;
        int sizeData;
        int ID; // create ID for entry
	    bool isFolder;
        bool isSubEntry;
        bool isEmpty;
        bool isLabel;
        bool isDeleted;
       
        std::vector<Entry> ListSubEntry;
        uint16_t StartCluster;
      

};


class RDET
{
public:
    RDET(const std::vector<char> &data);
    std::vector<Entry> getActiveEntry;
    bool findEntry(int,Entry&);
    //std::vector<std::string> Parse_path(std::string path);
    std::string getString(std::vector<BYTE>, int, int);
    std::string ReadSector_Data(Volume , int64_t, int, int);
    void AccessEntry(Volume, int);
private:
    std::vector<Entry> entries;
   
};




