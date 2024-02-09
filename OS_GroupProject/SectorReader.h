#pragma once
#include "StaticVariable.h"

class SectorReader
{
public:
    SectorReader();
  
    ~SectorReader();


    void SetDirve(LPCWSTR);
    vector<BYTE> ReadSector( int64_t readPoint, int sector) const;
    void SetByteOfSector(int);
private:
    LPCWSTR drive;
    int64_t readPoint;
	uint32_t byteOfSector;
    int sector;

};