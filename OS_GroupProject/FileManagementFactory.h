#pragma once
#include "StaticVariable.h"
#include "IParsable.h"

class FileManagementFactory
{
    public:
        FileManagementFactory();
        FileManagementFactory(LPCWSTR);
        ~FileManagementFactory();
    public:
        void registerWith(shared_ptr<IParsable>);
        shared_ptr<IParsable> createObject(wstring);
    private:
        map<wstring, shared_ptr<IParsable>> container;
        LPCWSTR drive;

};