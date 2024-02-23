#include "PseudoShell.h"
#include <algorithm>
#include <iomanip>

vector<std::wstring> TABLE_OF_COMMANDS = {
                                          L"show",
                                          L"dir",
                                          L"open",
                                          L"cd",
                                          L"return",
                                          L"cls",
                                          L"exit" };

bool PseudoShell::isValidCommand(std::wstring command) const
{
    return std::find(TABLE_OF_COMMANDS.begin(), TABLE_OF_COMMANDS.end(), command) != TABLE_OF_COMMANDS.end();
}

void PseudoShell::printShellTable(const wstring& partition, const wstring& tokens)
{
    std::wcout << L"▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬《 SHELL ENVIRONMENT 》▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬" << endl;
    std::wcout << L"▎                                                                   ▎" << endl;
    std::wcout << L"▎                           ";
    std::wcout << setw(40) << left <<             L"(" + partition + L":) - " + tokens << L"▎" << endl;
    std::wcout << L"▎                                                                   ▎" << endl;
    std::wcout << L"▎                     ◈ show:   show boot record                    ▎" << endl;
    std::wcout << L"▎                     ◈ dir:    print directories                   ▎" << endl;
    std::wcout << L"▎                     ◈ open:   open a file                         ▎" << endl;
    std::wcout << L"▎                     ◈ cd:     change directory                    ▎" << endl;
    std::wcout << L"▎                     ◈ return: return to previous directory        ▎" << endl;
    std::wcout << L"▎                     ◈ cls:    clear the screen                    ▎" << endl;
    std::wcout << L"▎                     ◈ exit:   exit SHELL ENVIRONMENT              ▎" << endl;
    std::wcout << L"────────────────────────────────────────────────────────────────────" << endl;
}

void PseudoShell::executeCommand(const std::wstring &userInput, shared_ptr<FileManagementSystem> fileSystem, wstring& partition, const wstring& tokens)
{
    if(userInput == L"show")
    {
        fileSystem->readVolumeBootRecord();
        std::wcout << std::endl;
    }
    else if (userInput == L"dir")
    {
        fileSystem->readDirectory();
        std::wcout << std::endl;
    }
    else if (userInput.substr(0,4) == L"open")
    {   
        wstring fileName = userInput.substr(5);
        fileSystem->accessFile(fileName);
    }
    else if (userInput.substr(0,2) == L"cd")
    {
        wstring tokens = userInput.substr(3);
        if(fileSystem->changeDirectory(tokens))
            partition += L"\\" + tokens;
    }
    else if (userInput == L"return")
    {
        if(fileSystem->returnPreviousDirectory())
        {
            int pos = partition.find_last_of('\\');
            partition = partition.substr(0, pos);
        }
        else
        {
            wcout << "No history founded";
        }
        wcout << endl;
    }
    else if (userInput == L"cls")
    {
        system("cls");
        printShellTable(partition, tokens);
        std::wcout << std::endl;
    }
    else if (userInput == L"exit")
    {
        std::wcout << L"Exit!" << std::endl;
        std::cin;
        return;
    }
}

void PseudoShell::accessEnvironment(shared_ptr<FileManagementSystem> fileSystem, wstring& partition, const wstring& tokens) {
    system("cls");

    std::wstring userInput;
    printShellTable(partition, tokens);

    std::wcout << partition << ":>";
    getline(std::wcin, userInput);

    while (!userInput.empty()) {
        //if (!isValidCommand(userInput)) {
        //    std::wcout << L"You typed an invalid command. Please type again." << std::endl;
        //    std::wcout << partition << L":>";
        //    getline(std::wcin, userInput);
        //    continue;
        //}

        executeCommand(userInput, fileSystem, partition, tokens);
        if (userInput == L"exit") return;
        std::wcout << partition << L":>";
        getline(std::wcin, userInput);

    }
}