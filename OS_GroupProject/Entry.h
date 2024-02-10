#pragma once
#include "StaticVariable.h"

class Entry;
class RDET;


enum Attribute
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
        bool is_Folder() const;
        bool isActiveEntry() const;

        std::string getMainName() const;
        std::string getExtendedName() const;

        int getSize() const;
        int GetID() const;
        
    private:
        char reserved;
        std::string mainName;
        std::string extendedName;
        Attribute attributes;
        std::chrono::system_clock::time_point DateCreated;
        std::chrono::system_clock::time_point LastAccess;
        std::chrono::system_clock::time_point DatedUpdated;
        int sizeData;
        int ID; // create ID for entry
	    bool isFolder;
        bool isEmpty;
        bool isLabel;
        bool isSystem;
        bool isDeleted;
        
        bool isSubEntry;
        char seq;
        std::wstring unicode;
        std::string extend1;
        std::string extend2;
        
       
        std::vector<shared_ptr<Entry>> ListSubEntry; // must have List sub entry because an entry may have many sub entries in it
        uint16_t StartCluster;
      

};





