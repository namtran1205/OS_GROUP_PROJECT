#include "PseudoShell.h"




bool PseudoShell::isValidCommand(std::wstring command) const
{
    return std::find(StaticVariable::TABLE_OF_COMMANDS.begin(), StaticVariable::TABLE_OF_COMMANDS.end(), command) != StaticVariable::TABLE_OF_COMMANDS.end();
}

void PseudoShell::printShellTable(const wstring& partition, const wstring& tokens)
{
    std::wcout << L"▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬《 SHELL ENVIRONMENT 》▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬" << endl;
    std::wcout << L"▎                                                                   ▎" << endl;
    std::wcout << L"▎                          ";
    std::wcout << setw(41) << left <<         L"(" + partition + L":) - " + tokens << L"▎" << endl;
    std::wcout << L"▎                                                                   ▎" << endl;
    std::wcout << L"▎                     ◈ help:   how to type commands                ▎" << endl;
    std::wcout << L"▎                     ◈ show:   show boot record                    ▎" << endl;
    std::wcout << L"▎                     ◈ dir:    print directories                   ▎" << endl;
    std::wcout << L"▎                     ◈ open:   open a file                         ▎" << endl;
    std::wcout << L"▎                     ◈ cd:     change directory                    ▎" << endl;
    std::wcout << L"▎                     ◈ return: return to previous directory        ▎" << endl;
    std::wcout << L"▎                     ◈ cls:    clear the screen                    ▎" << endl;
    std::wcout << L"▎                     ◈ exit:   exit SHELL ENVIRONMENT              ▎" << endl;
    std::wcout << L"────────────────────────────────────────────────────────────────────" << endl;
}

 void PseudoShell::executeCommand(const std::wstring &userInput,wstring fileName, shared_ptr<FileManagementSystem> fileSystem, wstring& partition, const wstring& tokens)
{
    if (userInput == L"help")
    {
        std::wcout << L"  [partition]:>show"                        << endl;
        std::wcout << L"  [partition]:>dir"                         << endl;
        std::wcout << L"  [partition]:>open [foler_name/file_name]" << endl;
        std::wcout << L"  [partition]:>cd [folder_name/file_name]"  << endl;
        std::wcout << L"  [partition]:>return"                      << endl;
        std::wcout << L"  [partition]:>cls"                         << endl;
        std::wcout << L"  [partition]:>exit"                        << endl;
    }
    else if(userInput == L"show")
    {
        fileSystem->readVolumeBootRecord();
    }
    else if (userInput == L"dir")
    {
        fileSystem->readDirectory();
    }
    else if (userInput == L"open")
    {   
        if (fileSystem->accessFile(fileName) == false)
        {
            wcout << L"The file is not existed" << endl;
        }
        else
        {
            wcout << endl;
        }
        
    }
    else if (userInput == L"cd")
    {
        if(fileSystem->changeDirectory(fileName))
            partition += L"\\" + fileName;
        else
        {
            std::wcout << L"The folder is not existed" << endl;
        }
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
            std::wcout << "No history founded" << endl;
        }
    }
    else if (userInput == L"cls")
    {
        system("cls");
        printShellTable(partition, tokens);
    }
    else if (userInput == L"exit")
    {
        std::wcout << L"Exit!" << std::endl;
        return;
    }
}

void PseudoShell::accessEnvironment(shared_ptr<FileManagementSystem> fileSystem, wstring& partition, const wstring& tokens) {
    system("cls");
    printShellTable(partition, tokens);
    while(true)
    {
        std::wcout << partition << ":>";
        std::wstring userInput;
        getline(std::wcin, userInput);
        wstring fileName = Utils::MySTRING::splitUserInput(userInput);
        if (!isValidCommand(userInput))
        {
            wcout << L"Invalid Command. Please type again." << endl;
            continue;
        }
        executeCommand(userInput, fileName, fileSystem, partition, tokens);
        if (userInput == L"exit") return;
    }

    // while (!userInput.empty()) {
    //     if (!isValidCommand(userInput)) {
    //        std::wcout << L"Invalid Command. Please type again." << std::endl;
    //        std::wcout << partition << L":>";
    //        getline(std::wcin, userInput);
    //        continue;
    //     }
    //     wstring fileName = Utils::MySTRING::splitUserInput(userInput);
    //     executeCommand(userInput, fileName, fileSystem, partition);
    //     if (userInput == L"exit") return;
    //     std::wcout << partition << L":>";
    //     getline(std::wcin, userInput);

    // }
}