#include "Entry.h"

Attribute::Attribute()
{
}

Attribute::Attribute(BYTE data) : Attribute()
{
    this->data = data;
}

bool Attribute::isReadOnly() const
{
    return ((data & 0x01) != 0);
}

bool Attribute::isHidden() const
{
    return  ((data & 0x02) != 0);
}

bool Attribute::isSystem() const
{
    return ((data & 0x04) != 0);
}

bool Attribute::isVollabel() const
{
    return  ((data & 0x08) != 0);
}

bool Attribute::isDirectory() const
{
    return  ((data & 0x10) != 0);
}

bool Attribute::isArchive() const
{
    return  ((data & 0x20) != 0);
}

Entry::Entry()
{
}

Entry::Entry(std::vector<BYTE> datas) : Entry()
{
    this->datas = datas;
}



MainEntry::MainEntry() : Entry()
{

}


MainEntry::MainEntry(shared_ptr<FAT> fatTable, vector<BYTE> datas) : Entry(datas)
{
    this->fatTable = fatTable;

    mainName = std::string(datas.begin(), datas.begin() + 7);

    extendedName = std::string(datas.begin() + 8, datas.begin() + 10);

    attributes = make_shared<Attribute>(datas[11]);
    // attributes = static_cast<Attribute>(datas[11]);

    reserved = datas[12];

    int highWord = int(Utils::Convert2LitleEndian(datas.begin() + 0x14,2));
    int lowWord = int(Utils::Convert2LitleEndian(datas.begin() + 0x1A,2));
    startCluster = (highWord << 8) + lowWord;
    
    sizeData = int(Utils::Convert2LitleEndian(datas.begin() + 0x1C, 4));


    if(attributes->isDirectory())
    {
        subDirectory = make_shared<SDET>(fatTable);
    }
    else
        subDirectory = nullptr;

}

// bool Entry::isActiveEntry() const
// {
//     return !(iSh || isEmpty || isLabel || isSystem);
// }


std::string MainEntry::getMainName() const
{
    return mainName;
}
std::string MainEntry::getExtendedName() const
{
    return extendedName;
}

int MainEntry::getStartCluster() const
{
    return this->startCluster;
}

int MainEntry::getSize() const
{
    return sizeData;
}

shared_ptr<Attribute> MainEntry::getAttribute() const
{
    return this->attributes;
}

shared_ptr<SDET> MainEntry::getSubDirectory() const
{
    return this->subDirectory;
}

shared_ptr<FAT> MainEntry::getFatTable() const
{
    return this->fatTable;
}

string MainEntry::getFullName() const
{

    //This function which included logical implementation returns the full name of file/folders
    return string();
}

string MainEntry::toString(int level) const
{
    string res = "";
    for(int i = 0; i < level; ++i)
        res += "\t";
    res += this->getFullName();
    return res;
}


SubEntry::SubEntry() : Entry()
{
}

SubEntry::SubEntry(vector<BYTE> datas) : Entry(datas)
{
    seq = int(Utils::Convert2LitleEndian(datas.begin(), 1));
    unicode = wstring(datas.begin() + 1, datas.begin() + 10);
}



int SubEntry::getSeq() const
{
    return this->seq;
}

wstring SubEntry::getUnicode() const
{
    return this->unicode;
}

wstring SubEntry::getExtend1() const
{
    return this->extend1;
}

wstring SubEntry::getExtend2() const
{
    return this->extend2;
}

string SubEntry::toString(int level) const
{
    //for(int i = 0; i < this->.size(); ++i)
    //{
    //    weak_ptr<Entry> entry = entries[i];
    //    entry.lock()->toString(0);
    //}
    return "SubEntry";
}


//bool Entry::findEntry(int id, Entry& res) const
//{
//    if (ID == id)
//    {
//        res = *this;
//        return true;
//    }
//    for (int i = 0; i < ListSubEntry.size(); i++)
//    {
//        if(ListSubEntry[i]->findEntry(id,res)) return true;
//    }
//    return false;
//    
//}

// int Entry::GetID() const
// {
//     return ID;
// }




// RDET::RDET(const uint32_t& startCluster)
// {

// }


//bool RDET::findEntry(int id, Entry& res) const
//{
//    for (int i = 0; i < entries.size(); i++)
//        if (entries[i].findEntry(id, res)) return true;
//    return false;
//}

// std::string RDET::getString(std::vector<BYTE> data, int offset, int num) const
// {
//     std::string res;
//     for (int i = offset; i < offset + num; i++)
//         if (data[i] > 0x00 && data[i] < 0xFF)
//             res += static_cast<char>(data[i]);
//     return res;
// }

// std::string RDET::ReadSector_Data(Volume a, int64_t startOffset, int sector, int size) const
// {
//     std::string res;
//     std::vector<BYTE> data = a.ReadSector(a.Drive, startOffset, size);
//     res = getString(data, 0x00, size);
//     return res;
// }

// ?? s?a sau
/*
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
            std::vector<Entry*> sub = st_entry.getListSubEntry();
            for (int i = 0; i < sub.size(); i++)
            {
                std::cout << sub[i]->getMainName();
                if (!sub[i]->is_Folder())
                    std::cout << '.';
                std::cout << sub[i]->getExtendedName() << std::endl;
 
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
*/


// void RDET::AddSector(Volume)
// {

// }

