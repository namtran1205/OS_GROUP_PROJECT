#include "DirectoryTree.h"

DirectoryTree::DirectoryTree(shared_ptr<BPB> bootSector)
{
    uint64_t firstReadPoint = bootSector->getStartMFTCluster() * bootSector->getSectorPerCluster() * bootSector->getBytePerSector();
    uint64_t curReadPoint = firstReadPoint;
    uint64_t endPoint = firstReadPoint + 50*1024;
    int cnt = 0;
    

    for (; curReadPoint < endPoint; curReadPoint += bootSector->getMFTsize())
    {

        shared_ptr<Record> tmp = make_shared<Record>(Record(curReadPoint, bootSector));
        cnt++;
        if (tmp->getMask() != "FILE")
        {
            // if (tmp->getMask() != "BAAD") break;
            continue;
        }
        if (tmp->getStatus() == 0 || !tmp->isUse()) continue;
        FileNode newNode;
        {
            newNode.flag = tmp->getFlag();
            newNode.name = tmp->getName();
            newNode.parentID = tmp->getParentID() * bootSector->getMFTsize() + firstReadPoint;
            newNode.status = tmp->getStatus();
            newNode.lastWriteTime = tmp->getLastWriteTime();
            newNode.size = tmp->getSize();
        }
        if (listNode.find(newNode.parentID) == listNode.end())
        {
            listNode.insert(make_pair(newNode.parentID, FileNode()));
            listNode[newNode.parentID].childID.push_back(curReadPoint);
        }
        else if (newNode.parentID != curReadPoint)
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
        if (listNode.find(curReadPoint) == listNode.end()) listNode.insert(make_pair(curReadPoint, newNode));
        else
        {
            newNode.childID = listNode[curReadPoint].childID;
            listNode[curReadPoint] = newNode;
        }

    }

    rootID = firstReadPoint + bootSector->getMFTsize() * 5;
    listNode[rootID].status |= 2;
    listNode[rootID].flag &= ~(6);
    listNode[rootID].name = L"Drive";
    listNode[rootID].parentID = rootID;
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
    flag = 6;
    childID.resize(0);
}

bool FileNode::isFolder() const
{
    return (status & 2) != 0;
}

bool FileNode::isFile() const
{
	return (flag & (1<<5)) != 0;
}

bool FileNode::isSystem() const
{
    return (flag & 6); 
}


FileNode DirectoryTree::getRoot()
{
    return listNode[rootID];
}

bool DirectoryTree::isRoot(uint64_t ID)
{
    return ID == rootID;
}

FileNode DirectoryTree::getNode(uint64_t nodeID)
{
    if (listNode.find(nodeID) == listNode.end()) return FileNode();
    return listNode[nodeID];
}