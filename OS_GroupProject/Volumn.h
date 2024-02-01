#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <sstream>
#include <fstream>
#include <Windows.h>

typedef std::vector<BYTE>::iterator byteArrayPointer;

class Volume
{
private:
	uint8_t numberOfFat;
	std::vector<uint32_t> fatTable;
    uint8_t SectorPerFat;
	uint8_t SectorPerCluster;
	uint16_t SectorPerBootsector;
	uint32_t SectorVolumn;
    uint16_t BytePerSector;
public:
		void ReadFatTable(std::ifstream);
        void ReadVolume(const std::wstring& drivePath);
        void SetNumberOfFat(uint8_t num) {
            numberOfFat = num;
        }

        void SetSectorPerCluster(uint8_t sector) {
            SectorPerCluster = sector;
        }

        void SetSectorPerBootSector(uint16_t sector) {
            SectorPerBootsector = sector;
        }

        void SetSectorVolume(uint32_t sector) {
            SectorVolumn = sector;
        }
        std::vector<uint32_t> GetFatTable();


	 

	 

};

std::vector<BYTE> ReadSector(LPCWSTR drive, int readPoint);

