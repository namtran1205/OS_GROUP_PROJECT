#pragma once
#include "StaticVariable.h"
#include "FileManagementSystem.h"

class IParsable
{
public:
    virtual shared_ptr<FileManagementSystem> parse() = 0;
    virtual string parseObjectName() const = 0;
public: 
    void setDrive(LPCWSTR);
protected:
    LPCWSTR drive;
};


class FAT32Parser : public IParsable
{
public:
    shared_ptr<FileManagementSystem> parse() override;
    string parseObjectName() const override;
};


class NTFSParser : public IParsable
{
public:
    shared_ptr<FileManagementSystem> parse() override;
    string parseObjectName() const override;
};