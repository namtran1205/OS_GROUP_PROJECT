#pragma once
#include "StaticVariable.h"

using namespace std;

class FileManagementSystem
{
public:
    FileManagementSystem();
public:
    virtual wstring toString() const = 0;
public:

    //This function is server for command "show"
    virtual void readVolumeBootRecord() = 0;

    //This function is serverd for command "dir"
    virtual void readDirectory() = 0;

    //This function is serverd for command "cd"
    virtual bool changeDirectory(wstring folderName) = 0;

    //This function is serverd for command "open"
    virtual bool accessFile(wstring fileName) = 0;

    virtual bool returnPreviousDirectory() = 0;
private:
};
