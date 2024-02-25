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
    
	std::map<std::wstring, std::wstring> MAPPING_FILENAME_APPS = {
		{ L"TXT", L"Notepad" },                  { L"txt", L"Notepad" },

		{ L"DOCX", L"Word" },{ L"docx", L"Word" },

		{ L"XLSS", L"Excel" },
		{ L"xlsx", L"Excel" },

		{ L"PPTX", L"PowerPoint" },
		{ L"pptx", L"PowerPoint" },

		{ L"PPT", L"PowerPoint" },
		{ L"ppt", L"PowerPoint" },

		{ L"PDF", L"Foxit Reader" },
		{ L"pdf", L"Foxit Reader" },

		{ L"JPG", L"Photos" },
		{ L"jpg", L"Photos" },

		{ L"PNG", L"Photos" },
		{ L"png", L"Photos" },

		{ L"GIF", L"Photos" },
		{ L"gif", L"Photos" },

		{ L"BMP", L"Photos" },
		{ L"bmp", L"Photos" },

		{ L"MP3", L"Media Player" },
		{ L"mp3", L"Media Player" },

		{ L"MP4", L"Media Player" },
		{ L"mp4", L"Media Player" },

		{ L"AVI", L"Media Player" },
		{ L"avi", L"Media Player" },

		{ L"FLAC", L"Media Player" },
		{ L"flac", L"Media Player" },

		{ L"ZIP", L"7-Zip" },
		{ L"zip", L"7-Zip" },
        { L"RAR", L"WinRAR" },
        { L"rar", L"WinRAR" },

        { L"EXE", L"Windows Explorer" },
        { L"exe", L"Windows Explorer" },

        { L"BAT", L"Command Prompt" },
        { L"bat", L"Command Prompt" },

        { L"CPP", L"Visual Studio" },
        { L"cpp", L"Visual Studio" },

        { L"CS", L"Visual Studio" },
        { L"cs", L"Visual Studio" },

        { L"JAVA", L"Eclipse" },
        { L"java", L"Eclipse" },

        { L"HTML", L"Web Browser" },
        { L"html", L"Web Browser" },

        { L"CSS", L"Text Editor" },
        { L"css", L"Text Editor" }
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

wstring Utils::MySTRING::toUpperCase(const wstring& wstr)
{
    std::wstring upperStr;
    for (wchar_t ch : wstr) {
        upperStr += std::toupper(ch); 
    }
    return upperStr;
}

wstring Utils::MySTRING::AppToOpen(const wstring& fileExtension)
{
    return StaticVariable::MAPPING_FILENAME_APPS[fileExtension];
}

void Utils::MyTABLE::display(const vector<tuple<wstring, wstring, wstring, uint64_t, uint64_t, wstring>> lines)
{
    wcout << L"Mode            LastWriteTime       StartSector          Length     Name" << endl;
    wcout << L"----           ---------------      ----------          -------     ----" << endl;
    for (const auto& line : lines)
    {
        wcout << setw(10) << left << get<0>(line);
        //TESTING...
        wcout << setw(13) << right << get<1>(line);
        // wcout << setw(20) << get<1>(line); 
        wcout << setw(8) << right << get<2>(line);
        wcout << setw(15) << right << get<3>(line) ;
        wcout << setw(17) << right << get<4>(line);
        wcout << L"     ";
        wcout << setw(25) << left  << get<5>(line);
        wcout << endl;
    }
}

wstring Utils::MyDATE::toString(vector<BYTE> bytes)
{
    uint16_t data = (bytes[1] << 8) | bytes[0];
    wstring res = L"";
    uint16_t year = ((data >> 9) & 0x7F) + 1980;
    uint16_t month = (data >> 5) & 0x0F; 
    uint16_t day = data & 0x1F;
    
    res += to_wstring(month) + L"/" + to_wstring(day) + L"/" + to_wstring(year);
    // wcout << res;
    // string s;
    // cin >> s;
    return res;
}

wstring Utils::MyTIME::toString(vector<BYTE> bytes)
{
    uint16_t data = (bytes[1] << 8) | bytes[0];
    wstring res = L"";
    uint16_t hour = (data >> 11) & 0x1F;
    uint16_t minute = (data >> 5) & 0x3F;
    if(minute < 10)
        res = to_wstring(hour) + L":0" + to_wstring(minute);
    else
        res = to_wstring(hour) + L":" + to_wstring(minute);
    return res;
}
