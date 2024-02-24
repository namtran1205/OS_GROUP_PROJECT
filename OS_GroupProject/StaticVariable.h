#pragma once
#define _CRT_SECURE_NO_WARNINGS

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
#include <stack>
#include <queue>
#include <limits>
#include <stdio.h>
#include <conio.h>
#include <fcntl.h>
#include <algorithm>
#include <iomanip>


using namespace std;

typedef std::vector<BYTE>::iterator byteArrayPointer;


//This place contains global variable
namespace StaticVariable
{
    extern int BYTES_PER_CLUSTER;
    extern int BYTES_PER_ENTRY;
    extern vector<wstring> TABLE_OF_COMMANDS;
}


namespace Utils
{

    class MySTRING
    {
        public:
            static wstring convertBytesToWstring( std::vector<BYTE> bytes);
            static wstring convertCharToWString(const char* input);
            static const char* convertWStringToChar(const std::wstring& wstr);
            static wstring convertBYTEToWstring( std::vector<BYTE>& byte);
            //HELLO   . TXT --> HELLO.TXT
            static string fixSpace(string name);
            static wstring fixSpaceWString(wstring name);
            static wstring fixSpecialCharacter(wstring name);
            static string parseExtendedFileName(string fileName);
            static wstring parseExtendedFileNameWString(const wstring& fileName);
            wstring AppToOpen(const wstring& fileExtension);
            static wstring splitUserInput(wstring& userInput);
    };

    class MyINTEGER
    {
        public:
            static uint64_t Convert2LitleEndian(byteArrayPointer offset, int numBytes);
    };
}
