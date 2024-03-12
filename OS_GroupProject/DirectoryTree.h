#pragma once
#include"StaticVariable.h"
#include "Record.h"

class FileNode {
public:
    FileNode();
    
public:
    bool isFolder() const;
    bool isFile() const;
    bool isSystem() const;

public: 
    std::wstring name;                                    // tên tệp tin(File_Name)
    std::pair<std::wstring, std::wstring> lastWriteTime;  // thời gian thay đổi cuối cùng(Standard_Info)
    uint64_t size;                                        // kích thước(Data)
    uint64_t flag;                                        // cờ báo(Standard_Info)
    uint64_t parentID;                                    // địa chỉ của thư mục cha (tính từ File_Name)  
    std::vector<uint64_t> childID;                        // được nạp vào nhờ parentID của tệp tin con  
    uint64_t status;                                      // tình trạng của tệp tin(Entry Header)  
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

