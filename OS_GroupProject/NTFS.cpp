#include "NTFS.h"


NTFS::NTFS(LPCWSTR drive)
{
    sectorReader = make_shared<SectorReader>(drive);
    bootSector = make_shared<BPB>(sectorReader);
    directoryTree = make_shared<DirectoryTree>(bootSector);
    currentFileNodeID = directoryTree->getRoot().parentID;
}
    
NTFS::~NTFS()
{

}

void NTFS::readVolumeBootRecord()
{
    bootSector->readVolumeBootRecord();
}
// Xử lí in ra cây thư mục (lệnh dir)
void NTFS::readDirectory()
{
    vector<tuple<wstring, wstring, wstring, uint64_t, uint64_t, wstring>> lines;
    auto curNode = directoryTree->getNode(currentFileNodeID);
    for(auto x:curNode.childID)
    {
        auto childFile = directoryTree->getNode(x);
        if (childFile.isSystem()) continue;
        wstring type = childFile.isFolder()? L"Directory" : L"Archive"; 
        auto line = make_tuple(type, childFile.lastWriteTime.first, childFile.lastWriteTime.second, x / bootSector->getBytePerSector(), childFile.size, childFile.name);
        lines.push_back(line);
    }
    Utils::MyTABLE::display(lines);
}


bool NTFS::changeDirectory(wstring folderName)
{
    bool res = false;
    auto curNode = directoryTree->getNode(currentFileNodeID);

    // tìm con hợp lệ
    for(auto id:curNode.childID)
    {
        auto childFile = directoryTree->getNode(id);
        if (!childFile.isSystem() && childFile.name == folderName )
        {
            currentFileNodeID = id;
            return true;
        }
    }

    return false;
}

bool NTFS::accessFile(wstring fileName)
{
    auto curNode = directoryTree->getNode(currentFileNodeID);
    for (auto id:curNode.childID)
    {
        auto childFile = directoryTree->getNode(id);
        if (!childFile.isSystem() && childFile.name == fileName)
        {
            shared_ptr<Record> it = make_shared<Record>(Record(id, bootSector));
            it->printFileContent();
            return true;
        }
    }
    return false;
}

bool NTFS::returnPreviousDirectory()
{
    if (directoryTree->isRoot(currentFileNodeID)) return false;
    auto curNode = directoryTree->getNode(currentFileNodeID);
    currentFileNodeID = curNode.parentID;
    return true;
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

