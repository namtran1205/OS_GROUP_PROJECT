#include "StaticVariable.h"
#include "FileManagementFactory.h"
#include "IParsable.h"
#include "PseudoShell.h"
#include <conio.h>
#include <io.h>
#include <fcntl.h>


int main()
{
    _setmode(_fileno(stdout), _O_U16TEXT);
    //wcout << L"Xin chào Việt Nam" << endl;
    wstring partition;
    const char* colon = ":";
    wcout << L"Enter the drive or partition name: ";
    wcin >> partition;
    wstring fullPath = L"\\\\.\\";
    fullPath += partition + Utils::MySTRING::convertCharToWString(colon);
    //LPCWSTR drive = fullPath; //User input this
    FileManagementFactory myFactory(fullPath.c_str());
    myFactory.registerWith(make_shared<FAT32Parser>());
    myFactory.registerWith(make_shared<NTFSParser>());

    wcin.ignore();
    wstring tokens;  //User input this
    wcout << L"Enter your file system: ";
    getline(wcin, tokens);
    shared_ptr<IParsable> fileSystem = myFactory.createObject(tokens);

    if(!fileSystem)
    {
        wcout << "INVALID ERRORS";
        return 0;   
    }

    PseudoShell cmdEnvironment;
    cmdEnvironment.accessEnvironment(fileSystem->parse(), partition, tokens);
    return 0;
}

