#pragma once
#include <iostream>
#include <string>
#include <cmath>
#include <chrono>
#include <vector>
#include <filesystem>
#include <sstream>
#include <memory>
#include <fstream>
#include <codecvt>
#include <cstdint>
#include <windows.h>
#include <Windows.h>




using namespace std;

typedef std::vector<BYTE>::iterator byteArrayPointer;


namespace StaticVariable
{
    //This place contains global variable
    extern int BYTES_PER_CLUSTER;
    extern int BYTES_PER_ENTRY;
}


namespace Utils
{
    uint64_t Convert2LitleEndian(byteArrayPointer offset, int numBytes);
    wstring convertUTF8ToWstring(const std::vector<BYTE>& bytes);

}
