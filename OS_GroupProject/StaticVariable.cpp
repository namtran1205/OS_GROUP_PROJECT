#include "StaticVariable.h"

namespace StaticVariable
{
    //This place contains global variable
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
    // Tạo một đối tượng wstring_convert với facet codecvt_utf8
    std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converter;

    // Chuyển đổi vector<BYTE> thành một chuỗi std::string
    std::string utf8_string(bytes.begin(), bytes.end());

    // Chuyển đổi std::string thành một wstring
    std::wstring wstr = converter.from_bytes(utf8_string);

    // Trả về kết quả
    return wstr;
}