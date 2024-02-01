#pragma once
#include <iostream>
#include <chrono>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include "Volumn.h"
enum Attribute;
class Entry;
class RDET;


enum Attribute
{
    READ_ONLY,
    HIDDEN,
    SYSTEM,
    VOLLABEL,
    DIRECTORY,
    ARCHIVE,
};


class Entry
{
    public:
        Entry();
        std::string getMainName() { return mainName; }
        std::string getExtendedName() { return extendedName; }
        int getSize() { return sizeData; }

    private:
        char reserved;
        std::string mainName;
        std::string extendedName;
        Attribute attribute;
        std::chrono::system_clock::time_point DateCreated;
        std::chrono::system_clock::time_point LastAccess;
        std::chrono::system_clock::time_point DatedUpdated;
        int sizeData;
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
    Entry findEntry(const std::string& name);
    std::vector<std::string> Parse_path(std::string path);
    std::string getString(std::vector<BYTE>, int, int);
    std::string ReadSector_Data(const std::wstring& drivePath, int);
    void getData(const std::wstring& drivePath, std::string);
private:
    std::vector<Entry> entries;
   
};




