#include "FileManagementFactory.h"

FileManagementFactory::FileManagementFactory()
{
}

FileManagementFactory::FileManagementFactory(LPCWSTR drive) : FileManagementFactory()
{
    this->drive = drive;
}

FileManagementFactory::~FileManagementFactory()
{
}

void FileManagementFactory::registerWith(shared_ptr<IParsable> parser)
{
    parser->setDrive(drive);
    container.insert(
        {parser->parseObjectName(), parser}
    );
}

shared_ptr<IParsable> FileManagementFactory::createObject(wstring typeObject)
{
    return container[typeObject];
}   