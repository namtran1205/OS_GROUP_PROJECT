#pragma once
#include "StaticVariable.h"

class SectorReader
{
public:
    SectorReader();
    SectorReader(LPCWSTR);
    ~SectorReader();

public:
    vector<BYTE> ReadSector(int64_t readPoint, uint64_t sector) const;
    vector<BYTE> ReadBytes(int64_t readPoint, uint64_t numberByte) const;
    vector<BYTE> collectBytesUntilNull(int64_t readPoint) const;
public:
    void SetDirve(LPCWSTR);
    void SetByteOfSector(int);
private:
    LPCWSTR drive;
    int64_t readPoint;
	uint32_t byteOfSector;
    int sector;

};