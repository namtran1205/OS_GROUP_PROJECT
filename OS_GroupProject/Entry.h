#pragma once
#include <iostream>
#include <chrono>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
enum Attribute;
class Entry;
class RDET;


enum Attribute
{
    READ_ONLY,
    HIDDEN,
    SYSTEM,
    VOLLABEL,
    DIRECTORY,
    ARCHIVE,
};


class Entry
{
    public:
        Entry();


    private:
        char reserved;
        std::string mainName;
        std::string extendedName;
        Attribute attribute;
        std::chrono::system_clock::time_point DateCreated;
        std::chrono::system_clock::time_point LastAccess;
        std::chrono::system_clock::time_point DatedUpdated;
        int sizeData;
	    bool isFolder;
        bool isSubEntry;
        bool isEmpty;
        bool isLabel;
        bool isDeleted;
        std::vector<Entry> ListSubEntry;
        uint16_t StartCluster;

};


class RDET
{
public:
    RDET(const std::vector<char> &data);
    std::vector<Entry> getActiveEntry;
    Entry findEntry(const std::string& name);

private:
    std::vector<Entry> entries;

};



#include <windows.h>

#include <stdio.h>
int ReadSector(LPCWSTR  drive, int readPoint, BYTE sector[512])
{
    int retCode = 0;
    DWORD bytesRead;
    HANDLE device = NULL;

    device = CreateFile(drive,    // Drive to open
        GENERIC_READ,           // Access mode
        FILE_SHARE_READ | FILE_SHARE_WRITE,        // Share Mode
        NULL,                   // Security Descriptor
        OPEN_EXISTING,          // How to create
        0,                      // File attributes
        NULL);                  // Handle to template

    if (device == INVALID_HANDLE_VALUE) // Open Error
    {
        printf("CreateFile: %u\n", GetLastError());
        return 1;
    }

    SetFilePointer(device, readPoint, NULL, FILE_BEGIN);//Set a Point to Read

    if (!ReadFile(device, sector, 512, &bytesRead, NULL))
    {
        printf("ReadFile: %u\n", GetLastError());
    }
    else
    {
        printf("Success!\n");
    }
}
int main(int argc, char** argv)
{

    BYTE sector[512];
    ReadSector(L"\\\\.\\C:", 0, sector);
    return 0;
}