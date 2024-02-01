#include "Volumn.h"

uint32_t ConvertEndian(uint32_t bigEndianValue) {
    return ((bigEndianValue & 0xFF) << 24) |
        (((bigEndianValue >> 8) & 0xFF) << 16) |
        (((bigEndianValue >> 16) & 0xFF) << 8) |
        ((bigEndianValue >> 24) & 0xFF);
}

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

std::vector<BYTE> ReadSector(LPCWSTR drive, int readPoint) {
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

    BYTE* tmpSector = new BYTE[512];
    std::vector<BYTE> resultSector(1, 0);
    // Read 512 bytes from the specified position
    if (ReadFile(device, tmpSector, 512, &bytesRead, NULL))
    {
        resultSector.resize(512, 0);
        for (int i = 0; i < 512; i++) resultSector[i] = tmpSector[i];
    }
    delete[] tmpSector;
    tmpSector = NULL;

    // Close the file handle
    CloseHandle(device);

    return resultSector;
}

void Volume::ReadFatTable(std::ifstream in)
{
    int fatSize = (SectorPerFat/SectorPerCluster) * numberOfFat ;

    // Di chuyển đến vị trí của bảng FAT 
    in.seekg(SectorPerBootsector * BytePerSector, std::ios::beg);

    // Đọc từng entry trong bảng FAT và chuyển đổi sang Little Endian 
    for (int i = 0; i < fatSize; ++i) {
        uint32_t fatEntry;
        in.read(reinterpret_cast<char*>(&fatEntry), sizeof(uint32_t));
        fatTable.push_back(ConvertEndian(fatEntry));
    }
}

void Volume::ReadVolume(const std::wstring& drivePath)
{
    std::vector<BYTE> bootSector = ReadSector(drivePath.c_str(), 0);
    this->numberOfFat = Convert2LitleEndian(bootSector.begin() + 0x10, 1);
    //this->SectorPerFat = Convert2LitleEndian(bootSector.begin() + 0x24, 4);
    this->SectorPerCluster = Convert2LitleEndian(bootSector.begin() + 0xD, 1);
    this->SectorPerBootsector = Convert2LitleEndian(bootSector.begin() + 0xE, 2);
    this->SectorVolumn = Convert2LitleEndian(bootSector.begin() + 0x20, 4);
    this->BytePerSector = Convert2LitleEndian(bootSector.begin() + 0xB, 2);
}

std::vector<uint32_t> Volume::GetFatTable()
{
    return fatTable;

}

