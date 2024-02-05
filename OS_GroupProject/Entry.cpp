#include "Entry.h"


Entry::Entry()
{
    
}

bool Entry::findEntry(int id, Entry& res)
{
    if (ID == id)
    {
        res = *this;
        return true;
    }
    for (int i = 0; i < ListSubEntry.size(); i++)
    {
        if(ListSubEntry[i].findEntry(id,res)) return true;
    }
    return false;
    
}

int Entry::GetID()
{
    return ID;
}






bool RDET::findEntry(int id, Entry& res)
{
    for (int i = 0; i < entries.size(); i++)
        if (entries[i].findEntry(id, res)) return true;
    return false;
}

std::string RDET::getString(std::vector<BYTE> data, int offset, int num)
{
    std::string res;
    for (int i = offset; i < offset + num; i++)
        if (data[i] > 0x00 && data[i] < 0xFF)
            res += static_cast<char>(data[i]);
    return res;
}

std::string RDET::ReadSector_Data(Volume a, int64_t startOffset, int sector, int size)
{
    std::string res;
    std::vector<BYTE> data = a.ReadSector(a.Drive, startOffset, size);
    res = getString(data, 0x00, size);
    return res;
}

void RDET::AccessEntry(Volume a, int id)
{
    
    Entry st_entry;
    if (!findEntry(id, st_entry))
    {
        std::cout << "NOT FOUND\n";
        return;

    }
    if (st_entry.is_Folder())
    {
            std::vector<Entry> sub = st_entry.getListSubEntry();
            for (int i = 0; i < sub.size(); i++)
            {
                std::cout << sub[i].getMainName();
                if (!sub[i].is_Folder())
                    std::cout << '.';
                std::cout << sub[i].getExtendedName() << std::endl;
 
            return;

        }
    }
    else if (st_entry.getExtendedName() == "txt")
        {
            uint16_t StartCluster = st_entry.GetStartCluster();
            std::vector<uint32_t> fatTable = a.GetFatTable();
            int size = st_entry.getSize();
            while (size > 0 && StartCluster != 0xFFFFFFF && StartCluster != 0xFFFFFF7)
            {
                int64_t startOffset = a.ClusterToSector(StartCluster) * a.GetBytePerSector();
                int num = min(a.GetBytePerSector() * a.GetSectorPerCluster(), size);
                std::cout << ReadSector_Data(a, startOffset, a.GetSectorPerCluster(), num);
                size -= a.GetBytePerSector() * a.GetSectorPerCluster();
                StartCluster = fatTable[StartCluster];

            }  // should check situation BAD???
        }
        else std::cout << "Please use another app to open it\n";
        

    
   
}

