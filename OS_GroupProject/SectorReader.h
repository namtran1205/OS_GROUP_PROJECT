#pragma once
#include "StaticVariable.h"

class SectorReader
{
public:
    SectorReader();
    SectorReader(LPCWSTR drive, int64_t readPoint, int sector);
    ~SectorReader();

public:
public:
    int ReadSector(LPCWSTR drive, int readPoint, BYTE sector[512]) const;
    vector<BYTE> ReadSector(LPCWSTR drive, int64_t readPoint, int sector) const;
private:
    LPCWSTR drive;
    int64_t readPoint;
    int sector;

};