#include "Entry.h"


Entry::Entry()
{
    
}

Entry RDET::findEntry(const std::string& name)
{
    return Entry();
}

std::vector<std::string> RDET::Parse_path(std::string path)
{
    std::vector<std::string> direct;
    std::string dir = "";
    for (char ch : dir)
        if (ch == '\\' || ch == '/')
        {
            direct.push_back(dir);
            dir = "";
        }
        else dir += ch;
    if (dir != "")
        direct.push_back(dir);
    return direct;
}


std::string RDET::getString(std::vector<BYTE> data, int offset, int num)
{
    std::string res;
    for (int i = offset; i < offset + num; i++)
        if (data[i] != 0x00 && data[i] != 0xFF)
            res += static_cast<char>(data[i]);
    return res;
}

std::string RDET::ReadSector_Data(const std::wstring& drivePath, int id)
{
    std::string res;
    std::vector<BYTE> data = Volume::ReadSector(drivePath.c_str(), id * 512, 1);
    res = getString(data, 0x00, 512);
    return res;
}
void RDET::getData(const std::wstring& drivePath, std::string st)
{
    for (int i = 0; i < st.length(); i++)
        st[i] = toupper(st[i]);
    for (int i = 0; i < entries.size(); i++)
    {
        std::string s = entries[i].getMainName() + '.' + entries[i].getExtendedName();
        if (st == s)
        {
            int size = entries[i].getSize();
            std::vector<BYTE> data;
            int id = i;
            while (size > 0)
            {
                std::cout << ReadSector_Data(drivePath, id);
                size -= 512;
                id++;
            }
            std::cout << std::endl;
        }
        else
        {
            std::cout << "NOT FOUND" << std::endl;
        }
    }
}

