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

std::string RDET::ReadSector_Data(Volume a, int startOffset, int sector)
{
    std::string res;
    std::vector<BYTE> data = a.ReadSector(a.Drive, startOffset, sector);
    res = getString(data, 0x00, a.GetBytePerSector() * sector);
    return res;
}
void RDET::getData(Volume a, std::string st)
{
    for (int i = 0; i < st.length(); i++)
        st[i] = toupper(st[i]);
    for (int i = 0; i < entries.size(); i++)
    {
        if (entries[i].getExtendedName() == "txt")
        {
            std::string s = entries[i].getMainName() + '.' + entries[i].getExtendedName();
            /*if (entries[i].is_Folder())
                for (int i = 0; entries[)*/
            if (st == s )
            {
                uint16_t StartCluster = entries[i].GetStartCluster();
                std::vector<uint32_t> fatTable = a.GetFatTable();

                while (StartCluster != 0xFFFFFFF && StartCluster != 0xFFFFFF7) 
                {
                    int startOffset = a.ClusterToSector(StartCluster) * a.GetBytePerSector();
                    std::cout << ReadSector_Data(a, startOffset, a.GetSectorPerCluster());
                    StartCluster = fatTable[StartCluster];
                }  // should check situation BAD???


            }
            else
            {

                std::cout << "NOT FOUND" << std::endl;
            }
        }
        else std::cout << "Please use another app to open it\n";
    }
}

