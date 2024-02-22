#pragma once

#include "StaticVariable.h"
#include "FileManagementFactory.h"
#include "IParsable.h"
#include "FileManagementSystem.h"

class PseudoShell
{
public:
	void accessEnvironment(shared_ptr<FileManagementSystem> fileSystem, wstring& partition);

private:
	void executeCommand(const std::wstring& userInput, shared_ptr<FileManagementSystem> fileSystem, wstring& partition);
	void printShellTable();
	bool isValidCommand(std::wstring command) const;

private:
};