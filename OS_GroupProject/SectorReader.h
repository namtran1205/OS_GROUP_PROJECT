#pragma once
#include "StaticVariable.h"

class SectorReader
{
public:
    SectorReader();
    SectorReader(LPCWSTR);
    ~SectorReader();

public:
    vector<BYTE> ReadSector( int64_t readPoint, int sector) const;
public:
    void SetDirve(LPCWSTR);
    void SetByteOfSector(int);
private:
    LPCWSTR drive;
    int64_t readPoint;
	uint32_t byteOfSector;
    int sector;

};