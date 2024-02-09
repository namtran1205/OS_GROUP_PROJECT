#pragma once
#include "StaticVariable.h"

using namespace std;

class FileManagementSystem
{
public:
    FileManagementSystem();
public:
    virtual void readVolume() = 0;
    virtual string toString() const = 0;
private:
};
