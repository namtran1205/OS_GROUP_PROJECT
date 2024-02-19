#pragma once
#include "StaticVariable.h"
#include "FAT.h"

class Content
{
public:
    Content(string, uint64_t, shared_ptr<FAT>);
public:
    string getContent() const;
private:
    string extendFileName;
    string content;
};