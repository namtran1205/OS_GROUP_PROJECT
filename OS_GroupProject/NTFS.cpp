#include "NTFS.h"


NTFS::NTFS(LPCWSTR drive) 
{
    sectorReader = make_shared<SectorReader>(drive);
    bootSector = make_shared<BPB>(sectorReader);
}
NTFS::~NTFS()
{

}

void NTFS::readVolumeBootRecord()
{
    bootSector->readVolumeBootRecord();
}

void NTFS::readDirectory()
{
    cout << 2;
}

bool NTFS::changeDirectory(wstring folderName)
{
    return true;
}

bool NTFS::accessFile(wstring fileName)
{
    return true;
}

bool NTFS::returnPreviousDirectory()
{
    return false;
}

wstring NTFS::toString() const
{
    return L"NTFS";
}



// std::vector<BYTE> ReadData(LPCWSTR drive, int readPoint, int numBytes) {
    
//     int retCode = 0;
//     DWORD bytesRead;
//     HANDLE device = NULL;

//     // Open the specified drive with GENERIC_READ access
//     device = CreateFile(drive, GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, NULL);

//     if (device == INVALID_HANDLE_VALUE || numBytes <= 0) {
//         // Failed to open the drive
//         // vector's size == 0
//         return std::vector<BYTE>();  
//     }

//     // Set the file pointer to the specified read point
//     SetFilePointer(device, readPoint, NULL, FILE_BEGIN);

//     BYTE* tmpSector = new BYTE[numBytes];
//     std::vector<BYTE> resultSector(1, 0);
//     // Read 512 bytes from the specified position
//     if (ReadFile(device, tmpSector, numBytes, &bytesRead, NULL))
//     {
//         resultSector.resize(numBytes, 0);
//         for (int i = 0; i < numBytes; i++) resultSector[i] = tmpSector[i];
//     }
//     delete[] tmpSector;
//     tmpSector = NULL;

//     // Close the file handle
//     CloseHandle(device);

//     return resultSector;
// }

// NTFSVolume::NTFSVolume(const std::wstring &drive)
// {
//     this->driveName = drive;
//     readBootSector(drive);
// }

// void NTFSVolume::readBootSector(const std::wstring &drive)
// {
//     std::vector<BYTE> memory = ReadData(drive.c_str(), 0, 80);

//     BytePerSector = Convert2LitleEndian(memory.begin() + 0xB, 2);       // 0xB 2 byte
//     SectorPerCluster = Convert2LitleEndian(memory.begin() + 0xD, 2);    // 0xD->0xE
//     MFTsize = Convert2LitleEndian(memory.begin() + 0x40, 1);            // 0x40->0x40  the true size is 2^abs(MFTsize)
//     SectorVolume = Convert2LitleEndian(memory.begin() + 0x28, 8);       // 0x28->0x2F
//     StartMFTCluster = Convert2LitleEndian(memory.begin() + 0x30, 8);    // 0x30->0x37
// }

