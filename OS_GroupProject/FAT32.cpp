#pragma once
#include "FAT32.h"

FAT32::FAT32()
{
}
FAT32::~FAT32()
{
}

void FAT32::readBootSector()
{
    this->bootSector->show();
}
void FAT32::readRDET()
{
    this->rootDirectory->show();
}

void FAT32::readFAT()
{
}

void FAT32::readVolume(LPCWSTR drive)
{
    this->readBootSector();
}
string FAT32::toString() const
{
}