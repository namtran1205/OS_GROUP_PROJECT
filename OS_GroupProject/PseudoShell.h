#pragma once

#include "StaticVariable.h"
#include "FileManagementFactory.h"
#include "IParsable.h"


class PseudoShell
{
public:
	void accessEnvironment(shared_ptr<FileManagementSystem> fileSystem, const wstring& partition);

private:
	void executeCommand(const std::string& userInput, shared_ptr<FileManagementSystem> fileSystem, const wstring& partition);
	void printShellTable();
	bool isValidCommand(std::string command) const;
};