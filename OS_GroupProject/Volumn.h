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
    uint32_t SectorPerFat;
	uint8_t SectorPerCluster;
	uint16_t SectorPerBootsector;
	uint32_t SectorVolume;
    uint16_t BytePerSector;
    uint32_t StartClusterOfRDET;
public:
    Volume();
    LPCWSTR Drive;
    std::vector<BYTE> ReadSector(LPCWSTR drive, int readPoint, int sector); // int sector: Number of sector you want read
		void ReadFatTable(const std::wstring& drivePath);
        uint16_t GetBytePerSector()
        {
            return BytePerSector;
        }
        uint8_t GetSectorPerCluster()
        {
            return SectorPerCluster;
        }
        void ReadVolume(const std::wstring& drivePath);
        void ShowBootSector()
        {
            std::cout << "Nf = " <<(int) numberOfFat << std::endl;
            std::cout << "Sf = " << SectorPerFat << std::endl;
            std::cout << "Sc = " <<(int) SectorPerCluster << std::endl;
            std::cout << "Sb = " << SectorPerBootsector << std::endl;
            std::cout << "Sv = " << SectorVolume << std::endl;
            std::cout << "BytePerSector = " << BytePerSector << std::endl;



        }
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
            SectorVolume = sector;
        }
        std::vector<uint32_t> GetFatTable();

        int ClusterToSector(uint16_t);
	 

	 

};



uint64_t Convert2LitleEndian(byteArrayPointer offset, int numBytes);