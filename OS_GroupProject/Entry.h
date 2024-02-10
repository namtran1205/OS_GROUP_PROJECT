#pragma once
#include "StaticVariable.h"

class Entry;
class Attribute;
class MainEntry;
class SubEntry;


class Attribute 
{


public:
    Attribute();
    Attribute(BYTE);

public:
    bool isReadOnly() const;
    bool isHidden() const;
    bool isSystem() const;
    bool isVollabel() const;
    bool isDirectory() const;
    bool isArchive() const;

private:
    BYTE data;
};


class Entry
{
    public:
        Entry();
        Entry(std::vector<BYTE>);
    public:
        virtual string toString() const = 0;
    protected: 
        vector<BYTE> datas;
};



class MainEntry : public Entry
{
    public:
        MainEntry();
        MainEntry(std::vector<BYTE>);

    public:
        // bool is_Folder() const;
        // bool isActiveEntry() const;

        std::string getMainName() const;
        std::string getExtendedName() const;
        int getStartCluster() const;
        int getSize() const;
        // int GetID() const;
        
    private:
        char reserved;
        std::string mainName;
        std::string extendedName;
        Attribute attributes;
        std::chrono::system_clock::time_point dateCreated;
        std::chrono::system_clock::time_point lastAccess;
        std::chrono::system_clock::time_point datedUpdated;
        int sizeData;
        int startCluster;
        // int ID; // create ID for entry

	    // bool isFolder;
        // bool isEmpty;
        // bool isLabel;
        // bool isSystem;
        // bool isDeleted;
        std::vector<shared_ptr<SubEntry>> subEntries; // must have List sub entry because an entry may have many sub entries in it
};


class SubEntry : public Entry 
{
public:
    SubEntry();
    SubEntry(vector<BYTE>);
public:
    int getSeq() const;
    wstring getUnicode() const;
    string getExtend1() const;
    string getExtend2() const;

private:
    int seq;
    std::wstring unicode;
    std::string extend1;
    std::string extend2;
};





