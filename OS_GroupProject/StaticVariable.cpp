#include "StaticVariable.h"

namespace StaticVariable
{
    int BYTES_PER_CLUSTER = 4;
    int BYTES_PER_ENTRY = 32;
}




uint64_t Utils::Convert2LitleEndian(byteArrayPointer offset, int numBytes)
{
    if (numBytes <= 0 || numBytes > 8)
        return 0;

    uint64_t res = 0;
    for (int i = 0; i < numBytes; i++)
    {
        res |= (*offset) << (i * 8);
        offset++;
    }
    return res;
}


std::wstring Utils::convertUTF8ToWstring(const std::vector<BYTE>& bytes)
{
    wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converter;
    string utf8_string(bytes.begin(), bytes.end());
    wstring wstr = converter.from_bytes(utf8_string);
    return wstr;
}

std::wstring Utils::convertCharToWString(const char* input) {
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    return converter.from_bytes(input);
}

const char* Utils::convertWStringToChar(const std::wstring& wstr)
{
    size_t size = wcstombs(nullptr, wstr.c_str(), 0);
    if (size == static_cast<size_t>(-1)) {
        std::wcerr << L"Error converting wstring to multibyte string" << std::endl;
        return nullptr;
    }

    char* result = new char[size + 1];

    if (wcstombs(result, wstr.c_str(), size + 1) == static_cast<size_t>(-1)) {
        std::wcerr << L"Error converting wstring to multibyte string" << std::endl;
        delete[] result;
        return nullptr;
    }

    return result;
}

wstring Utils::convertBYTEToWstring( std::vector<BYTE>& byte)
{
    std::wstring WCHAR = L"";
    for (int i = 0; i < bytes.size(); i += 2)
    {
        uint64_t tmp;
        if (i == bytes.size() - 1)
        {
            tmp = Utils::Convert2LitleEndian(bytes.begin() + i, 1);
            break;
        }
        tmp = Utils::Convert2LitleEndian(bytes.begin() + i, 2);
        if (bytes[i] == 0xFF  bytes[i + 1] == 0xFF  tmp == 0)
            break;
        WCHAR += static_cast<wchar_t> (tmp);
    }
    return WCHAR;
}

string Utils::fixSpace(string name)
{
    string res;
    for (int i = 0; i < name.size(); ++i)
    {
        if (name[i] == ' ')
            break;
        res += name[i];

    }
    return res;
}

wstring Utils::fixSpaceWString(wstring name)
{
    wstring res;
    for (size_t i = 0; i < name.size(); ++i)
    {
        if (name[i] == L' ')
            break;
        res += name[i];
    }
    return res;
}

wstring Utils::fixSpecialCharacter(wstring name)
{
    wstring res;
    for (size_t i = 0; i < name.size(); ++i)
    {
        if (name[i] == L'ÿ')
            break;
        res += name[i];
    }
    return res;
}

string Utils::parseExtendedFileName(string fileName)
{
    string extendedName;
    int dotPos = fileName.find_last_of('.');
    if(dotPos !=  string::npos)
        return fileName.substr(dotPos+1);
    return string();
}

wstring Utils::parseExtendedFileNameWString(const wstring& fileName)
{
    wstring extendedName;
    size_t dotPos = fileName.find_last_of(L'.');
    if (dotPos != wstring::npos)
        return fileName.substr(dotPos + 1);
    return wstring();
}
