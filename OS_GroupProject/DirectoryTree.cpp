#include "DirectoryTree.h"

DirectoryTree::DirectoryTree(shared_ptr<BPB> bootSector)
{
    uint64_t firstReadPoint = bootSector->getStartMFTCluster() * bootSector->getSectorPerCluster() * bootSector->getBytePerSector();
    uint64_t endPoint = firstReadPoint + bootSector->getSizeOfVolume();
    while (firstReadPoint < endPoint)
    {
        shared_ptr<Record> tmp = make_shared<Record>(Record(firstReadPoint, bootSector));
        if (tmp->isFolder() || tmp->isUse())
        {
            FileNode newNode;
            newNode.flag = tmp->getFlag();
            newNode.name = tmp->getName();
            newNode.parentID = tmp->getParentID();
            if (listNode.find(newNode.parentID) != listNode.end())
            {

            }
        }

        firstReadPoint += bootSector->getMFTsize();
    }
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
