#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <sstream>
#include <fstream>
#include <Windows.h>

class Entry;

class RDET;

typedef std::vector<BYTE>::iterator byteArrayPointer;


class Volume
{
private:
	uint8_t numberOfFat;
	std::vector<uint32_t> fatTable;
    RDET DirectoryTable;
    uint32_t SectorPerFat;
	uint8_t SectorPerCluster;
	uint16_t SectorPerBootsector;
	uint32_t SectorVolume;
    uint16_t BytePerSector;
    uint32_t StartClusterOfRDET;
	HANDLE device = INVALID_HANDLE_VALUE;

public:
    Volume();
    ~Volume()
    {
		if (device != INVALID_HANDLE_VALUE) {
			CloseHandle(device);
		}
    };
    LPCWSTR Drive;
    std::vector<BYTE> ReadSector(LPCWSTR drive, int64_t readPoint, int sector) const; // int sector: Number of sector you want read
		void ReadFatTable(const std::wstring& drivePath);
        uint16_t GetBytePerSector() const
        {
            return BytePerSector;
        }
        uint8_t GetSectorPerCluster() const
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
        std::vector<uint32_t> GetFatTable() const;
        uint32_t GetStartClusterOfRootDirectory() const {
            return StartClusterOfRDET;
        }

        int ClusterToSector(uint16_t) const;

        std::vector<Entry*> ReadDirectory(uint32_t startCluster) const;

};



uint64_t Convert2LitleEndian(byteArrayPointer offset, int numBytes);
