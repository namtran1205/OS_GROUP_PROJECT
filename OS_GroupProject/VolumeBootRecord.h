#pragma once
#include "StaticVariable.h"
#include "SectorReader.h"
using namespace std;


//NTFS va FAT32 deu co 1 vung VolumeBootRecord
//Trong FAT32 thi goi la BootSector
//Trong NTFS thi goi la VolumeBootRecord


class VolumeBootRecord
{
public:
	VolumeBootRecord();
	virtual ~VolumeBootRecord();

public:
	virtual void ReadSector(SectorReader* sectorReader) = 0;

private:

};
