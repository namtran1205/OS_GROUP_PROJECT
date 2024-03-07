#include "DirectoryTree.h"

DirectoryTree::DirectoryTree(shared_ptr<BPB> bootSector)
{
    uint64_t firstReadPoint = bootSector->getStartMFTCluster() * bootSector->getSectorPerCluster() * bootSector->getBytePerSector();
    uint64_t curReadPoint = firstReadPoint;
    uint64_t endPoint = firstReadPoint + bootSector->getSizeOfVolume();
    int cnt = 0;
    for (; curReadPoint < endPoint; curReadPoint += bootSector->getMFTsize())
    {
        shared_ptr<Record> tmp = make_shared<Record>(Record(curReadPoint, bootSector));
       
        if (tmp->getStatus() == 0) continue;
        if (tmp->getMask() != "FILE") continue;
        if (!tmp->isFolder() && !tmp->isUse()) continue;
        FileNode newNode;
        newNode.flag = tmp->getFlag();
        newNode.name = tmp->getName();
        newNode.parentID = tmp->getParentID() * bootSector->getMFTsize() + firstReadPoint;
        
        if (listNode.find(newNode.parentID) == listNode.end())
        {
            listNode.insert(make_pair(newNode.parentID, FileNode()));
            listNode[newNode.parentID].childID.push_back(curReadPoint);
        }
        else 
        {
            bool isExist = false;
            for(auto id:listNode[newNode.parentID].childID)
                if (id == curReadPoint) 
                {
                    isExist = true;
                    break;
                }
            if (isExist) continue;
            listNode[newNode.parentID].childID.push_back(curReadPoint);
        }
        if (listNode.find(curReadPoint) == listNode.end())
        {
            listNode.insert(make_pair(curReadPoint, newNode));
            std::wofstream ofs;
            ofs.open("check.txt", ios::app|ios::out);
            if (!ofs.is_open()) continue;
            ofs << newNode.name << '\n';
            ofs << tmp->getParentID() << '\n';
            ofs << cnt++ << '\n';

            //ofs << "mask:" << tmp->getMask() << '\n';
            ofs << "------------------\n";
            ofs.close();
        }
    }

    for(auto it:listNode)
    {
        if (it.first == it.second.parentID)
        {
            rootID = it.first;
            break;
        }
    }
    throw (std::string) "doesnt have root id";
}

std::vector<FileNode> DirectoryTree::getChild(uint64_t parentID)
{
	std::vector<FileNode> listChild;
    if (listNode.find(parentID) == listNode.end()) return listChild;

    for(uint64_t id : listNode[parentID].childID)
        listChild.push_back(listNode[id]);

    return listChild;
}

FileNode DirectoryTree::getParent(uint64_t childID)
{
    if (listNode.find(childID) != listNode.end()) return listNode[childID];
    FileNode res;
    res.name = L"No exist";
	return res;
}

FileNode::FileNode()
{
}

bool FileNode::isFolder() const
{
    for(auto c:name) 
        if (c == wchar_t('.')) 
            return true;
	return false;
}

bool FileNode::isFile() const
{
	return !FileNode::isFolder();
}


FileNode DirectoryTree::getRoot()
{
    return listNode[rootID];
}

bool DirectoryTree::isRoot(uint64_t ID)
{
    return ID = rootID;
}

FileNode DirectoryTree::getNode(uint64_t nodeID)
{
    if (listNode.find(nodeID) == listNode.end()) return FileNode();
    return listNode[nodeID];
}