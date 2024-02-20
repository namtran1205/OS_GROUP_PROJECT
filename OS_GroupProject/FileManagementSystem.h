#pragma once
#include "StaticVariable.h"

using namespace std;

class FileManagementSystem
{
public:
    FileManagementSystem();
public:
    virtual void readVolume() = 0;
    virtual void readDirectory() = 0;
    virtual wstring toString() const = 0;
private:
};
