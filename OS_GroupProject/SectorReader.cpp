#include "SectorReader.h"

SectorReader::SectorReader()
{
}
SectorReader::SectorReader(LPCWSTR drive, int64_t readPoint, int sector)
{
    this->drive = drive;
    this->readPoint = readPoint;
    this->sector = sector;
}
SectorReader::~SectorReader()
{
}

int SectorReader::ReadSector(LPCWSTR drive, int readPoint, BYTE sector[512]) const
{
    int retCode = 0;
    DWORD bytesRead;
    HANDLE device = NULL;

    device = CreateFile(drive,                              // Drive to open
                        GENERIC_READ,                       // Access mode
                        FILE_SHARE_READ | FILE_SHARE_WRITE, // Share Mode
                        NULL,                               // Security Descriptor
                        OPEN_EXISTING,                      // How to create
                        0,                                  // File attributes
                        NULL);                              // Handle to template

    if (device == INVALID_HANDLE_VALUE) // Open Error
    {
        printf("CreateFile: %u\n", GetLastError());
        return 1;
    }

    SetFilePointer(device, readPoint, NULL, FILE_BEGIN); // Set a Point to Read

    if (!ReadFile(device, sector, 512, &bytesRead, NULL))
    {
        printf("ReadFile: %u\n", GetLastError());
    }
    else
    {
        printf("Success!\n");
    }
}

std::vector<BYTE> SectorReader::ReadSector(LPCWSTR drive, int64_t readPoint, int sector) const
{
    
}
