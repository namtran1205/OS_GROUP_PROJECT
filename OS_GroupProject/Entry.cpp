#include "Entry.h"


Entry::Entry()
{
    
}

Entry RDET::findEntry(const std::string& name)
{
    return Entry();
}




std::string RDET::getString(std::vector<BYTE> data, int offset, int num)
{
    std::string res;
    for (int i = offset; i < offset + num; i++)
        if (data[i] != 0x00 && data[i] != 0xFF)
            res += static_cast<char>(data[i]);
    return res;
}

std::string RDET::ReadSector_Data(Volume a, int id)
{
    std::string res;
    std::vector<BYTE> data = a.ReadSector(a.Drive, id * 512, 1);
    res = getString(data, 0x00, 512);
    return res;
}
void RDET::getData(Volume a, std::string st)
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
                std::cout << ReadSector_Data(a, id);
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

