#include "FileManagementSystem.h"
#include "FAT32.h"
#include "NTFS.h"


FileManagementSystem::FileManagementSystem()
{
}

shared_ptr<FileManagementSystem> FileManagementSystem::getObject(LPCWSTR drive)
{
	wstring fileSystemName;
    wstring backFlash = L"\\";
    wstring fullDrive = drive + backFlash;
    if (Utils::MyBOOL::getVolumeFileSystem(fullDrive, fileSystemName))
    {
        if(fileSystemName == L"FAT32")
            return dynamic_pointer_cast<FileManagementSystem>(make_shared<FAT32>(drive));
        if(fileSystemName == L"NTFS")
            return dynamic_pointer_cast<FileManagementSystem>(make_shared<NTFS>(drive));
    }
    return NULL;
}

