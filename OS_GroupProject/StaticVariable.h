#pragma once
#include <iostream>
#include <string>
#include <cmath>
#include <map> 
#include <chrono>
#include <vector>
#include <filesystem>
#include <sstream>
#include <memory>
#include <fstream>
#include <codecvt>
#include <cstdint>
#include <io.h>
#include <windows.h>
#include <Windows.h>
#include <stdio.h>
#include <conio.h>
#include <fcntl.h>



using namespace std;

typedef std::vector<BYTE>::iterator byteArrayPointer;


//This place contains global variable
namespace StaticVariable
{
    extern int BYTES_PER_CLUSTER;
    extern int BYTES_PER_ENTRY;
}


namespace Utils
{
    uint64_t Convert2LitleEndian(byteArrayPointer offset, int numBytes);
    wstring convertUTF8ToWstring(const std::vector<BYTE>& bytes);
    wstring convertCharToWString(const char* input);
    const char* convertWStringToChar(const std::wstring& wstr);
    wstring convertBYTEToWstring( std::vector<BYTE>& byte);
    //HELLO   . TXT --> HELLO.TXT
    string fixSpace(string name);
    wstring fixSpaceWString(wstring name);
    wstring fixSpecialCharacter(wstring name);
    string parseExtendedFileName(string fileName);
    wstring parseExtendedFileNameWString(const wstring& fileName);
}
