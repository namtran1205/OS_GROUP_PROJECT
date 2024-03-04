#include "StaticVariable.h"
#include "FileManagementSystem.h"
#include "IParsable.h"
#include "PseudoShell.h"
#include "FAT32.h"


int main()
{
    _setmode(_fileno(stdout), _O_U16TEXT);
    wstring partition;
    wcout << L"Enter the drive or partition name: ";
    wcin >> partition;
    while(Utils::MyBOOL::volumeExists(partition.c_str()) == false)
    {
        wcout << "The volume is not existed!" << endl;
        wcout << L"Enter the drive or partition name: ";
        wcin >> partition;
    }
    wcin.ignore();
    wstring fullPath =  L"\\\\.\\" + partition + L":" ;
    shared_ptr<FileManagementSystem> fileSystem = FileManagementSystem::getObject(fullPath.c_str());
    fullPath += L":";
    PseudoShell cmdEnvironment;
    cmdEnvironment.accessEnvironment(fileSystem, partition, fileSystem->toString());
    return 0;
}

