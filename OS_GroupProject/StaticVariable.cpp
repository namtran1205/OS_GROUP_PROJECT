#include "StaticVariable.h"

namespace StaticVariable
{
    int BYTES_PER_CLUSTER = 4;
    int BYTES_PER_ENTRY = 32;
    vector<wstring> TABLE_OF_COMMANDS = {
        L"help",
        L"show",
        L"dir",
        L"open",
        L"cd",
        L"return",
        L"cls",
        L"exit" 
    };
    
    map<wstring, wstring> MAPPING_FILENAME_APPS = {
        { L".txt", L"Notepad" },
        { L".docx", L"Word" },
        { L".xlsx", L"Excel" },
        { L".pptx", L"PowerPoint" },
        { L".pdf", L"Foxit Reader" },
        { L".jpg", L"Photos" },
        { L".mp3", L"Media Player" },
        { L".mp4", L"Media Player" },
        { L".zip", L"7-Zip" }
    };
}





uint64_t Utils::MyINTEGER::Convert2LitleEndian(byteArrayPointer offset, int numBytes)
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


std::wstring Utils::MySTRING::convertBytesToWstring( std::vector<BYTE> bytes)
{
    std::wstring WCHAR = L"";
    for (int i = 0; i < bytes.size(); i += 2)
    {
        uint64_t tmp;
        if(i == bytes.size() - 1)
        {
            tmp = Utils::MyINTEGER::Convert2LitleEndian(bytes.begin() + i, 1);
            break;
        }
        tmp = Utils::MyINTEGER::Convert2LitleEndian(bytes.begin() + i, 2);
        if(bytes[i] == 0xFF || bytes[i+1] == 0xFF || tmp == 0)
            break;
        WCHAR += static_cast<wchar_t> (tmp);
    }
    return WCHAR;
}

std::wstring Utils::MySTRING::convertCharToWString(const char* input) {
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    return converter.from_bytes(input);
}

const char* Utils::MySTRING::convertWStringToChar(const std::wstring& wstr)
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

wstring Utils::MySTRING::convertBYTEToWstring( std::vector<BYTE>& bytes)
{
    std::wstring WCHAR = L"";
    for (int i = 0; i < bytes.size(); i += 2)
    {
        uint64_t tmp;
        if (i == bytes.size() - 1)
        {
            tmp = Utils::MyINTEGER::Convert2LitleEndian(bytes.begin() + i, 1);
            break;
        }
        tmp = Utils::MyINTEGER::Convert2LitleEndian(bytes.begin() + i, 2);
        if (bytes[i] == 0xFF || bytes[i + 1] == 0xFF || tmp == 0)
            break;
        WCHAR += static_cast<wchar_t> (tmp);
    }
    return WCHAR;
}

string Utils::MySTRING::fixSpace(string name)
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

wstring Utils::MySTRING::fixSpaceWString(wstring name)
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

wstring Utils::MySTRING::fixSpecialCharacter(wstring name)
{
    wstring res;
    for (size_t i = 0; i < name.size(); ++i)
    {
        if (name[i] == L'�')
            break;
        res += name[i];
    }
    return res;
}

string Utils::MySTRING::parseExtendedFileName(string fileName)
{
    string extendedName;
    int dotPos = fileName.find_last_of('.');
    if(dotPos !=  string::npos)
        return fileName.substr(dotPos+1);
    return string();
}

wstring Utils::MySTRING::parseExtendedFileNameWString(const wstring& fileName)
{
    wstring extendedName;
    size_t dotPos = fileName.find_last_of(L'.');
    if (dotPos != wstring::npos)
        return fileName.substr(dotPos + 1);
    return wstring();
}

wstring Utils::MySTRING::splitUserInput(wstring& userInput)
{
    wstring res;
    int spacePos = userInput.find_first_of(L' ');
    if(spacePos != wstring::npos)
    {
        res = userInput.substr(spacePos + 1); 
        userInput = userInput.substr(0, spacePos);
        return res;
    }
    return res;
}

//wstring Utils::AppToOpen(const wstring& fileExtension)
//{
//    auto it = find(TABLE_OF_EXTENSIONS.begin(), TABLE_OF_EXTENSIONS.end(), fileExtension);
//    if (it == TABLE_OF_EXTENSIONS.end())
//    {
//        wcout << L"Failed to determine what application used to open this file." << endl;
//        return L"";
//    }
//
//    size_t index = distance(TABLE_OF_EXTENSIONS.begin(), it);
//    return TABLE_OF_APPS[index];
//}

void Utils::MyTABLE::display(const vector<tuple<wstring, wstring, uint64_t, uint64_t, wstring>> lines)
{
    wcout << L"Mode                 LastWriteTime         StartSector         Length            Name" << endl;
    wcout << L"----                ---------------       -------------       --------           ----" << endl;
    for (const auto& line : lines)
    {
        wcout << setw(23) << get<0>(line);

        //TESTING...
        wcout << setw(20) << L"2/22/2024";
        // wcout << setw(20) << get<1>(line); 
        wcout << setw(19) << get<2>(line);
        wcout << setw(19) << get<3>(line);
        wcout << setw(20) << get<4>(line);
        wcout << endl;
    }
}
