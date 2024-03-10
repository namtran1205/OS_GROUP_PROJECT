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
#include <tuple>
#include<memory>
#include <chrono>
#include <ctime>
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
	class MyBOOL
	{
	public:
		static bool volumeExists(const wchar_t* volumePath);
		static bool getVolumeFileSystem(const std::wstring& volumePath, std::wstring& fileSystem);
	};
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
            static wstring AppToOpen(const wstring& fileExtension);
            static wstring splitUserInput(wstring& userInput);
            static wstring toUpperCase(const wstring& wstr);
    };

    class MyINTEGER
    {
        public:
            static uint64_t Convert2LittleEndian(byteArrayPointer offset, int numBytes);
    };

    class MyTABLE
    {
        public:
            static void display(const vector<tuple<wstring, wstring, wstring, uint64_t, uint64_t, wstring>>);
    };
    class MyDATE
    {
    public:
        static wstring toString(vector<BYTE>);
        //wstring secondsToDateTime(uint64_t milliseconds);
        static std::pair<std::wstring, std::wstring> extractTime_NTFS(std::vector<BYTE>& byteVector, int startIndex, int numberByte);
    private:
        //int day = 0;
        //int month = 0;
        //int year = 0;
    };

    class MyTIME
    {
    public:
        static wstring toString(vector<BYTE>);
    private:
        //int second = 0;
        //int minute = 0;
        //int hour = 0;
    };
}
void printSector(vector<BYTE> sector);