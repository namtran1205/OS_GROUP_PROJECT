#include "StaticVariable.h"
#include "FileManagementFactory.h"
#include "IParsable.h"

int main()
{
    //_setmode(_fileno(stdout), _O_U16TEXT);
    //cout << "Xin Chào Việt Nam\n";
    LPCWSTR drive = L"\\\\.\\F:"; //User input this
    FileManagementFactory myFactory(drive);
    myFactory.registerWith(make_shared<FAT32Parser>());
    myFactory.registerWith(make_shared<NTFSParser>());


    string tokens = "FAT32";  //User input this
    shared_ptr<IParsable> fileSystem = myFactory.createObject(tokens);
    fileSystem->parse()->readVolume();
    return 0;
}

