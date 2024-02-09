#pragma once
#include "StaticVariable.h"

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

    public:
        bool is_Folder() const { return isFolder; }

        std::string getMainName() const { return mainName; }
        std::string getExtendedName() const { return extendedName; }

        int getSize() const { return sizeData; }
        int GetID() const { return this->ID;}
        
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
        
       
        std::vector<Entry*> ListSubEntry;
        uint16_t StartCluster;
      

};





