#pragma once
#include"StaticVariable.h"
#include "Record.h"

class FileNode {
public:
    FileNode();
    
public:
    bool isFolder() const;
    bool isFile() const;

public:
    std::wstring name;
    uint64_t flag;
    uint64_t parentID;
    std::vector<uint64_t> childID;
};

class DirectoryTree
{
public:
    DirectoryTree(shared_ptr<BPB> bootSector);

public:
    std::vector<FileNode> getChild(uint64_t parentID);
    FileNode getParent(uint64_t childID) ;
    FileNode getRoot();
    FileNode getNode(uint64_t nodeID);
    bool isRoot(uint64_t ID);
private:
    uint64_t rootID;
    std::map<uint64_t, FileNode> listNode; 

};

