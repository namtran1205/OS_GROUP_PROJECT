#pragma once
#include "StaticVariable.h"
#include "FAT.h"

class Content
{
public:
    Content();
    Content(wstring, uint64_t, shared_ptr<FAT>);
public:
    wstring getContent() const;
private:
    wstring extendFileName;
    wstring content;
    shared_ptr<FAT> fatTable;
    uint64_t startCluster;
};