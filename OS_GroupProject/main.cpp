#include "StaticVariable.h"
#include "FileManagementFactory.h"
#include "IParsable.h"
#include "PseudoShell.h"
#include <conio.h>


int main()
{
    //_setmode(_fileno(stdout), _O_U16TEXT);
    //cout << "Xin Chào Việt Nam\n";
    wstring partition;
    const char* colon = ":";
    wcout << L"Enter the drive or partition name: ";
    wcin >> partition;
    wstring fullPath = L"\\\\.\\";
    fullPath += partition + Utils::convertCharToWString(colon);
    //LPCWSTR drive = fullPath; //User input this
    FileManagementFactory myFactory(fullPath.c_str());
    myFactory.registerWith(make_shared<FAT32Parser>());
    myFactory.registerWith(make_shared<NTFSParser>());

    cin.ignore();
    string tokens;  //User input this
    cout << "Enter your file system: ";
    getline(cin, tokens);
    shared_ptr<IParsable> fileSystem = myFactory.createObject(tokens);
    

    if(fileSystem != nullptr)
        fileSystem->parse()->readVolume();
    else
    {
        cout << "INVALID ERRORS";
        return 0;   
    }

    PseudoShell cmdEnvironment;
    cout << endl;
    cout << "PRESS ENTER TO ACCESS COMMAND ENVIRONMENT";
    _getch();
    cmdEnvironment.accessEnvironment(fileSystem, 'F');
    return 0;
}

