#pragma once
#include "StaticVariable.h"

class SectorReader
{
public:
    SectorReader();
    SectorReader(LPCWSTR drive, int64_t readPoint, int byteofsector);
    ~SectorReader();

public:
public:
   
    vector<BYTE> ReadSector( int64_t readPoint, int sector) const;
    void SetByteOfSector(int);
private:
    LPCWSTR drive;
    int64_t readPoint;
	int byteOfSector;
    int sector;

};