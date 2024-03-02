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
public:
    wstring toString() const;
private:
    BYTE data;
};

class Entry
{
public:
    Entry();
    Entry(std::vector<BYTE>);
public:
    virtual wstring getFullName() const = 0;
    virtual wstring toString(int level) const = 0;
protected:
    vector<BYTE> datas;
    wstring fullName;
};

class MainEntry : public Entry, public enable_shared_from_this<MainEntry>
{
public:
    MainEntry();
    MainEntry(shared_ptr<FAT>,vector<BYTE>);

public:
    void addSubEntry(vector<shared_ptr<SubEntry>>);
public:
    std::wstring getMainName() const;
    std::wstring getExtendedName() const;
    int getStartCluster() const;
    uint64_t getStartSector() const;
    int getSize() const;
    shared_ptr<Attribute> getAttribute() const;
    shared_ptr<SDET> getSubDirectory() const;
    shared_ptr<FAT> getFatTable() const;
    shared_ptr<Content> getContent() const;
    wstring getFullName() const override;
    wstring getLastWriteDate() const;
    wstring getLastWriteTime() const;
public:
    void initializeContent();
public:
    wstring toString(int level) const override;
protected:
    int startCluster;
    uint64_t sizeData;
private:
    char reserved;
    std::wstring mainName;
    std::wstring extendedName;
    shared_ptr<Attribute> attributes;
    wstring lastWriteDate;
    wstring lastWriteTime;
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
    wstring getUnicode() const;
    wstring getExtend1() const;
    wstring getExtend2() const;

    wstring getFullName() const override;

public:
    wstring toString(int level) const override;

private:
    int seq;
    wstring unicode;
    wstring extend1;
    wstring extend2;

};


