#include "SectorReader.h"

SectorReader::SectorReader()
{
    byteOfSector = 512;
}

SectorReader::SectorReader(LPCWSTR drive) : SectorReader()
{
    this->drive = drive;
}

SectorReader::~SectorReader()
{
}



void SectorReader::SetDirve(LPCWSTR drive)
{
    this->drive = drive;
}

std::vector<BYTE> SectorReader::ReadSector( int64_t readPoint, uint64_t sector) const
{
    int retCode = 0;
    DWORD bytesRead;
    HANDLE device = NULL;

    // Open the specified drive with GENERIC_READ access
    std::string strDrive(drive, drive + wcslen(drive));
    device = CreateFileA(strDrive.c_str(), GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, NULL);

    if (device == INVALID_HANDLE_VALUE) {
        CloseHandle(device);
        return std::vector<BYTE>();
    }

    LARGE_INTEGER filePointer;
    filePointer.QuadPart = readPoint;
    // Set the file pointer to the specified read point
    SetFilePointerEx(device, filePointer, NULL, FILE_BEGIN);


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

vector<BYTE> SectorReader::collectBytesUntilNull(int64_t readPoint) const 
{
    DWORD bytesRead;
    HANDLE device = NULL;

    // // Open the specified drive with GENERIC_READ access
    std::string strDrive(drive, drive + wcslen(drive));
    device = CreateFileA(strDrive.c_str(), GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, NULL);

    if (device == INVALID_HANDLE_VALUE) {
        CloseHandle(device);
        return std::vector<BYTE>();
    }

    std::vector<BYTE> resultSector;
    BYTE* tmpBuffer = new BYTE[512];
    LARGE_INTEGER filePointer;
    while(true)
    {
        filePointer.QuadPart = readPoint;
        SetFilePointerEx(device, filePointer, NULL, FILE_BEGIN);
        ReadFile(device, tmpBuffer, 512, &bytesRead, NULL);
        for(int i = 0; i < 512; ++i)
        {
            if(i % 32 == 0 && tmpBuffer[i] == 0x0)
            {
                delete[] tmpBuffer;
                tmpBuffer = nullptr;
                CloseHandle(device);
                return resultSector;
            }
            resultSector.push_back(tmpBuffer[i]);
        }
        readPoint += 512;
    }
    delete[] tmpBuffer;
    tmpBuffer = nullptr;
    CloseHandle(device);
    return vector<BYTE>();
}

void SectorReader::SetByteOfSector(int ByteOfSector)
{
    this->byteOfSector = ByteOfSector;
    
}
