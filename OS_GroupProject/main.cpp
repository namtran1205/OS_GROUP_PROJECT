#include "StaticVariable.h"
#include "FAT32.h"


int main()
{
    //_setmode(_fileno(stdout), _O_U16TEXT);
    //cout << "Xin Chào Việt Nam\n";
    shared_ptr<FAT32> fat32 = make_shared<FAT32>(L"\\\\.\\F:");
    fat32->readVolume();
    return 0;
}

