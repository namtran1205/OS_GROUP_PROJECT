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
    std::cout << "===================== SHELL ENVIRONMENT =====================" << endl;
    std::cout << "| --root:  print root directory tree                         " << endl;
    std::cout << "| --cls:   clear the screen                                  " << endl;
    std::cout << "| --exit:  exit SHELL ENVIRONMENT                            " << endl;
    std::cout << "=============================================================" << endl;
}

void PseudoShell::executeCommand(const std::string& userInput, shared_ptr<IParsable> fileSystem, char partition) {
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

void PseudoShell::accessEnvironment(shared_ptr<IParsable> fileSystem, char partition) {
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