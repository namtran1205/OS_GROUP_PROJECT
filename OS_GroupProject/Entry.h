#pragma once
#include "StaticVariable.h"
#include "FAT.h"
#include "RDET.h"


class Attribute;
class Entry;
class MainEntry;
class SubEntry;
class SDET;

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
    virtual string toString(int level) const = 0;

protected:
    vector<BYTE> datas;
};

class MainEntry : public Entry
{
public:
    MainEntry();
    MainEntry(shared_ptr<FAT>,vector<BYTE>);

public:
    // bool is_Folder() const;

    std::string getMainName() const;
    std::string getExtendedName() const;
    int getStartCluster() const;
    int getSize() const;
 
     int getID() const;

public:
    string toString(int level) const override;

public:
     bool isActiveEntry() const;
protected:
    int startCluster;
private:
    char reserved;
    std::string mainName;
    std::string extendedName;
    Attribute attributes;
    std::chrono::system_clock::time_point dateCreated;
    std::chrono::system_clock::time_point lastAccess;
    std::chrono::system_clock::time_point datedUpdated;
    int sizeData;
    bool isEmpty;
    bool isDeleted;

    //If the file/folder's name is too long:
    //then the LFN Entry (Long Files Name) will be created to store these names without changing Main Entry's format
    //LFN Entry is the other name of SubEntry.
    std::vector<shared_ptr<SubEntry>> subEntries;


private:
    shared_ptr<SDET> subDirectory;
    shared_ptr<FAT> fatTable;

     //int ID; // create ID for entry (first sector of entry)
    
};

class SubEntry : public Entry
{
public:
    SubEntry();
    SubEntry(vector<BYTE>);

public:
    int getSeq() const;
    wstring getUnicode() const;
    wstring getExtend1() const;
    wstring getExtend2() const;

public:
    string toString(int level) const override;

private:
    int seq;
    wstring unicode;
    wstring extend1;
    wstring extend2;

    string name;
};
