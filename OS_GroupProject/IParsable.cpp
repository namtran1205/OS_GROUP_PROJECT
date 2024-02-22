#include "IParsable.h"
#include "FAT32.h"
#include "NTFS.h"


void IParsable::setDrive(LPCWSTR drive)
{
    this->drive = drive;
}

shared_ptr<FileManagementSystem> FAT32Parser::parse()
{
    return make_shared<FAT32>(drive);
}

wstring FAT32Parser::parseObjectName() const
{
    return L"FAT32";
}

shared_ptr<FileManagementSystem> NTFSParser::parse()
{
    return make_shared<NTFS>(drive);
}

wstring NTFSParser::parseObjectName() const
{
    return L"NTFS";
}


