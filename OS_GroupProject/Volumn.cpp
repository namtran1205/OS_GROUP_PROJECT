#include "Volumn.h"



uint64_t Convert2LitleEndian(byteArrayPointer offset, int numBytes)
{
    if (numBytes <= 0 || numBytes > 8) return 0;

    uint64_t res = 0;
    for (int i = 0; i < numBytes; i++)
    {
        res |= (*offset) << (i * 8);
        offset++;
    }
    return res;
}
Volume::Volume()
{
    BytePerSector = 512;
}
std::vector<BYTE> Volume:: ReadSector(LPCWSTR drive, int64_t readPoint, int sector) {
    
    int retCode = 0;
    DWORD bytesRead;
    HANDLE device = NULL;

    // Open the specified drive with GENERIC_READ access
    device = CreateFile(drive, GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, NULL);

    if (device == INVALID_HANDLE_VALUE) {
        // Failed to open the drive
        // vector's size == 0
        return std::vector<BYTE>();  
    }

    // Set the file pointer to the specified read point
    SetFilePointer(device, readPoint, NULL, FILE_BEGIN);

    BYTE* tmpSector = new BYTE[BytePerSector * sector];
    std::vector<BYTE> resultSector(1, 0);
    // Read 512 bytes from the specified position
    if (ReadFile(device, tmpSector, BytePerSector * sector, &bytesRead, NULL))
    {
        resultSector.resize(BytePerSector * sector, 0);
        for (int i = 0; i < BytePerSector * sector; i++) resultSector[i] = tmpSector[i];
    }
    delete[] tmpSector;
    tmpSector = NULL;

    // Close the file handle
    CloseHandle(device);

    return resultSector;
}

void Volume::ReadFatTable(const std::wstring& drivePath)
{
    int FatSize = numberOfFat * SectorPerFat;
    int64_t ReadPoint = BytePerSector * SectorPerBootsector;
    std::vector<BYTE> FatSector = ReadSector(drivePath.c_str(), ReadPoint, FatSize);
    for (int i = 0; i < FatSize; i++)
    {
        uint32_t res = Convert2LitleEndian(FatSector.begin() + 4 * i, 4);
        fatTable.push_back(res);
    }


}

void Volume::ReadVolume(const std::wstring& drivePath)
{
    std::vector<BYTE> bootSector = ReadSector(drivePath.c_str(), 0,1);
    this->numberOfFat = (uint8_t)(*(bootSector.begin() + 0x10));
    this->SectorPerFat = Convert2LitleEndian(bootSector.begin() + 0x24, 4);
    this->SectorPerCluster =(uint8_t)(*(bootSector.begin() + 0xD));
    this->SectorPerBootsector = Convert2LitleEndian(bootSector.begin() + 0xE, 2);
    this->SectorVolume = Convert2LitleEndian(bootSector.begin() + 0x20, 4);
    this->BytePerSector = Convert2LitleEndian(bootSector.begin() + 0xB, 2);
    this->StartClusterOfRDET = Convert2LitleEndian(bootSector.begin() + 0x2C, 4);
    ReadFatTable(drivePath);
}

std::vector<uint32_t> Volume::GetFatTable()
{
    return fatTable;

}

int Volume::ClusterToSector(uint16_t k)
{
    int i = SectorPerBootsector + SectorPerFat * numberOfFat + (k - 2) * SectorPerCluster;
    return i;
}



