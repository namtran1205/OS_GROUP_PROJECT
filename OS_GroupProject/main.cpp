#include "StaticVariable.h"
#include "FileManagementFactory.h"
#include "IParsable.h"
#include <algorithm>
#include <conio.h>


// Hàm pseudo shell
vector<std::string> TABLE_OF_COMMANDS = { "root",
                                          "cls",
                                          "exit" };

bool isValidCommand(std::string command)
{
    return std::find(TABLE_OF_COMMANDS.begin(), TABLE_OF_COMMANDS.end(), command) != TABLE_OF_COMMANDS.end();
}

void printShellTable()
{
    std::cout << "===================== SHELL ENVIRONMENT =====================" << endl;
    std::cout << "| --root:  print root directory tree                         " << endl;
    std::cout << "| --cls:   clear the screen                                  " << endl;
    std::cout << "| --exit:  exit SHELL ENVIRONMENT                            " << endl;
    std::cout << "=============================================================" << endl;
}

void executeCommand(const std::string& userInput, shared_ptr<IParsable> fileSystem, char partition) {
    if (userInput == "root") {
        fileSystem->parse()->readDirectory();
        std::cout << std::endl;
    }
    else if (userInput == "cls") {
        system("cls");
        printShellTable();
        std::cout << std::endl;
    }
    else if (userInput == "exit") {
        std::cout << "Exit!" << std::endl;
        std::cin;
        return;
    }
}

void pseudoShell(shared_ptr<IParsable> fileSystem, char partition) {
    std::string userInput;

    std::cout << std::endl;
    printShellTable();

    std::cout << partition << ":>";
    getline(std::cin, userInput);

    while (!userInput.empty()) {
        if (!isValidCommand(userInput)) {
            std::cout << "You typed an invalid command. Please type again." << std::endl;
            std::cout << partition << ":>";
            getline(std::cin, userInput);
            continue;
        }

        executeCommand(userInput, fileSystem, partition);
        if (userInput == "exit") return;
        std::cout << partition << ":>";
        getline(std::cin, userInput);
    }
}



int main()
{
    //_setmode(_fileno(stdout), _O_U16TEXT);
    //cout << "Xin Chào Việt Nam\n";
    wstring partition;
    const char* expression = ":";
    wcout << L"Enter the drive or partition name: ";
    wcin >> partition;
    wstring fullPath = L"\\\\.\\";
    fullPath += partition + Utils::convertCharToWString(expression);
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
    cout << endl;
    cout << "PRESS ENTER TO ACCESS COMMAND ENVIRONMENT";
    _getch();
    pseudoShell(fileSystem, 'F');
    return 0;
}

