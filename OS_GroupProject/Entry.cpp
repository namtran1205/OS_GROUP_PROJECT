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

Entry::Entry(vector<BYTE> bytesData) : Entry()
{
    this->datas = bytesData;
    //BYTE index11 = *(startByte.get() + 3);
}



MainEntry::MainEntry() : Entry()
{

}


MainEntry:: MainEntry(shared_ptr<FAT> fatTable, vector<BYTE> bytes) : Entry(bytes)
{
    this->fatTable = fatTable;

    /*mainName = std::string(datas.begin(), datas.begin() + 7);

    extendedName = std::string(datas.begin() + 8, datas.begin() + 11);
    fullName = Utils::fixSpace(mainName) + "." + Utils::fixSpace(extendedName);
    */
    
    mainName = wstring(datas.begin(), datas.begin() + 7);
    extendedName = wstring(datas.begin() + 8, datas.begin() + 11);
    fullName = Utils::fixSpaceWString(mainName) + L"." + Utils::fixSpaceWString(extendedName);

    attributes = make_shared<Attribute>(datas[0xB]);

    reserved = datas[0xC];

    int highWord = int(Utils::Convert2LitleEndian(datas.begin() + 0x14,2));
    int lowWord = int(Utils::Convert2LitleEndian(datas.begin() + 0x1A,2));
    startCluster = (highWord << 16) + lowWord;
    
    sizeData = (Utils::Convert2LitleEndian(datas.begin() + 0x1C, 4));

    if(attributes->isDirectory())
    {
        fullName = Utils::fixSpaceWString(mainName) + Utils::fixSpaceWString(extendedName);
        uint64_t startByte = this->getFatTable()->getBootSector()->ClusterToSector(startCluster) * this->getFatTable()->getBootSector()->getBytePerSector();
        subDirectory = make_shared<SDET>(fatTable, startByte);
        content = nullptr;
    }
    else
    {
        subDirectory = nullptr;
        wstring extendedName = Utils::parseExtendedFileNameWString(fullName);
        content = make_shared<Content>(extendedName,startCluster, fatTable);
    }

}

void MainEntry::addSubEntry(vector<shared_ptr<SubEntry>> subEntries)
{
    this->subEntries = subEntries;    
    wstring fullNameOfMainEntry;

    //After adding list SubEntries, then convert these entries to the main name.
    //Traversing the vector<BYTE> from the last->first
    for(int i = subEntries.size() - 1; i >= 0; --i)
    {
        fullNameOfMainEntry += subEntries[i]->getFullName();
        
    }
    this->fullName = Utils::fixSpecialCharacter(fullNameOfMainEntry);
}

std::wstring MainEntry::getMainName() const
{
    return mainName;
}
std::wstring MainEntry::getExtendedName() const
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

wstring MainEntry::getFullName() const
{
    return this->fullName;
}

/*
string MainEntry::toString(int level) const
{
    cout << "||";
    string res = "";
    for(int i = 0; i < level; ++i)
        res += "\t";
    res += "|---" + this->getFullName();
    return res;
}
*/

wstring MainEntry::toString(int level) const
{
    wcout << L"||";
    wstring res;
    for (int i = 0; i < level; ++i)
        res += L"\t";
    res += L"|---" + this->getFullName();
    return res;
}


// bool MainEntry::isActiveEntry() const
// {
//     return !(isDeleted || isEmpty || attributes->isVollabel() || attributes->isSystem());
// }

SubEntry::SubEntry() : Entry()
{
}

SubEntry::SubEntry(vector<BYTE> bytesData) : Entry(bytesData)
{
    seq = int(Utils::Convert2LitleEndian(datas.begin(), 1));
    unicode = wstring(datas.begin() + 1, datas.begin() + 10);
    extend1 = wstring(datas.begin() +  0xE, datas.begin() + 0x19);
    extend2 = wstring(datas.begin() +  0x1C, datas.end());
    fullName = unicode + extend1 + extend2;
    
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

wstring SubEntry::getFullName() const
{
    return this->fullName;
}

/*
string SubEntry::toString(int level) const
{
    string res = "";
    for(int i = 0; i < level; ++i)
        res += "\t";
    res += this->getFullName();
    return res;
}
*/

wstring SubEntry::toString(int level) const
{
    wstring res;
    for (int i = 0; i < level; ++i)
        res += L"\t";
    res += this->getFullName();
    return res;
}
