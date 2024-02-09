#include "SectorReader.h"

SectorReader::SectorReader()
{
    byteOfSector = 512;
}

SectorReader::~SectorReader()
{
}



void SectorReader::SetDirve(LPCWSTR drive)
{
    this->drive = drive;
}

std::vector<BYTE> SectorReader::ReadSector( int64_t readPoint, int sector) const
{
    
    int retCode = 0;
    DWORD bytesRead;
    HANDLE device = NULL;

    // Open the specified drive with GENERIC_READ access
    // device = CreateFile(drive, GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, NULL);

    if (device == INVALID_HANDLE_VALUE) {
        // Failed to open the drive
        // vector's size == 0
        return std::vector<BYTE>();
    }

    // Set the file pointer to the specified read point
    SetFilePointer(device, readPoint, NULL, FILE_BEGIN);

    BYTE* tmpSector = new BYTE[byteOfSector * sector];
    std::vector<BYTE> resultSector(1, 0);
    // Read 512 bytes from the specified position
    if (ReadFile(device, tmpSector, byteOfSector * sector, &bytesRead, NULL))
    {
        resultSector.resize(byteOfSector * sector, 0);
        for (int i = 0; i < byteOfSector * sector; i++) resultSector[i] = tmpSector[i];
    }
    delete[] tmpSector;
    tmpSector = NULL;

    // Close the file handle
    CloseHandle(device);

    return resultSector;
    
}

void SectorReader::SetByteOfSector(int ByteOfSector)
{
    this->byteOfSector = ByteOfSector;
    
}
