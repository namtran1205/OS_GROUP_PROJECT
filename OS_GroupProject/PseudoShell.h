#pragma once

#include "StaticVariable.h"
#include "FileManagementFactory.h"
#include "IParsable.h"


class PseudoShell
{
public:
	void accessEnvironment(shared_ptr<IParsable> fileSystem, const char* partition);

private:
	void executeCommand(const std::string& userInput, shared_ptr<IParsable> fileSystem, const char* partition);
	void printShellTable();
	bool isValidCommand(std::string command) const;
};