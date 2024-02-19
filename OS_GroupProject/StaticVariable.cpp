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

string Utils::parseExtendedFileName(string fileName)
{
    string extendedName;
    int dotPos = fileName.find_last_of('.');
    if(dotPos !=  string::npos)
        return fileName.substr(dotPos+1);
    return string();
}
