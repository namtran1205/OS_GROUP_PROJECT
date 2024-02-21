#include "PseudoShell.h"
#include <algorithm>

vector<std::string> TABLE_OF_COMMANDS = { "root",
                                          "cls",
                                          "exit" };

bool PseudoShell::isValidCommand(std::string command) const
{
    return std::find(TABLE_OF_COMMANDS.begin(), TABLE_OF_COMMANDS.end(), command) != TABLE_OF_COMMANDS.end();
}

void PseudoShell::printShellTable()
{
    std::wcout << L"===================== SHELL ENVIRONMENT =====================" << endl;
    std::wcout << L"| --root:  print root directory tree                         " << endl;
    std::wcout << L"| --cls:   clear the screen                                  " << endl;
    std::wcout << L"| --exit:  exit SHELL ENVIRONMENT                            " << endl;
    std::wcout << L"=============================================================" << endl;
}

void PseudoShell::executeCommand(const std::string& userInput, shared_ptr<FileManagementSystem> fileSystem, const wstring& partition) {
    if (userInput == "root") {
        fileSystem->readDirectory();
        std::wcout << std::endl;
    }
    else if (userInput == "cls") {
        system("cls");
        printShellTable();
        std::wcout << std::endl;
    }
    else if (userInput == "exit") {
        std::wcout << L"Exit!" << std::endl;
        std::cin;
        return;
    }
}

void PseudoShell::accessEnvironment(shared_ptr<FileManagementSystem> fileSystem, const wstring& partition) {
    std::string userInput;

    std::wcout << std::endl;
    printShellTable();

    std::wcout << partition << ":>";
    getline(std::cin, userInput);

    while (!userInput.empty()) {
        if (!isValidCommand(userInput)) {
            std::wcout << L"You typed an invalid command. Please type again." << std::endl;
            std::wcout << partition << L":>";
            getline(std::cin, userInput);
            continue;
        }

        executeCommand(userInput, fileSystem, partition);
        if (userInput == "exit") return;
        std::wcout << partition << L":>";
        getline(std::cin, userInput);
    }
}