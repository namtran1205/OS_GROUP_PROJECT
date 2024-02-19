#pragma once
#include "StaticVariable.h"
#include "FAT.h"
#include "RDET.h"
#include "Content.h"

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
    virtual string getFullName() const = 0;
    virtual string toString(int level) const = 0;
protected:
    vector<BYTE> datas;
    string fullName;
};

class MainEntry : public Entry
{
public:
    MainEntry();
    MainEntry(shared_ptr<FAT>,vector<BYTE>);

public:
    void addSubEntry(vector<shared_ptr<SubEntry>>);

public:
    std::string getMainName() const;
    std::string getExtendedName() const;
    int getStartCluster() const;
    int getSize() const;
    shared_ptr<Attribute> getAttribute() const;
    shared_ptr<SDET> getSubDirectory() const;
    shared_ptr<FAT> getFatTable() const;
public:
    string getFullName() const override;
public:
    string toString(int level) const override;
protected:
    int startCluster;
    int sizeData;
private:
    char reserved;
    std::string mainName;
    std::string extendedName;
    shared_ptr<Attribute> attributes;
    std::chrono::system_clock::time_point dateCreated;
    std::chrono::system_clock::time_point lastAccess;
    std::chrono::system_clock::time_point datedUpdated;
private:
    shared_ptr<Content> content; //If the entry represents for a File, then get it contents.
    shared_ptr<SDET> subDirectory;
    shared_ptr<FAT> fatTable;
    //If the file/folder's name is too long:
    //then the LFN Entry (Long Files Name) will be created to store these names without changing Main Entry's format
    //LFN Entry is the other name of SubEntry.
    std::vector<shared_ptr<SubEntry>> subEntries;
};


class SubEntry : public Entry
{
public:
    SubEntry();
    SubEntry(vector<BYTE>);

public:
    int getSeq() const;
    string getUnicode() const;
    string getExtend1() const;
    string getExtend2() const;

    string getFullName() const override;

public:
    string toString(int level) const override;

private:
    int seq;
    string unicode;
    string extend1;
    string extend2;

};


