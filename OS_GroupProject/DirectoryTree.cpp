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
        if (tmp->getStatus() == 0) continue;
        if (!tmp->isFolder() && !tmp->isUse()) continue;
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
        // std::wofstream ofs;
        // ofs.open("check.txt", ios::app|ios::out);
        // if (!ofs.is_open()) continue;
        // ofs << newNode.name << '\n';
        // ofs << tmp->getParentID() << '\n';
        // ofs << tmp->getStatus() << '\n';
        // ofs << newNode.flag << '\n';
        // ofs << cnt << '\n';

        // //ofs << "mask:" << tmp->getMask() << '\n';
        // ofs << "------------------\n";
        // ofs.close();

    }

    rootID = firstReadPoint + bootSector->getMFTsize() * 5;
    listNode[rootID].status |= 2;
    listNode[rootID].flag &= ~(6);
    listNode[rootID].name = L"Drive";
    listNode[rootID].parentID = rootID;
    // for(auto it:listNode) 
    // {
    //     wcout << "Status: " << ((it.second.status >> 1) & 1) << '\n';
    //     wcout << "ID: " << (it.first - firstReadPoint) / 1024 << '\n';
    //     wcout << "Name: " << it.second.name << '\n';
    //     wcout << "Flag: ";
    //     for(int i = 0; i < 8; i++) 
    //         wcout << ((it.second.flag >> i) & 1) << ' ';
    //     wcout << "\nChild: ";
    //     for(auto id : it.second.childID)
    //     {
    //         wcout << (id - firstReadPoint) / 1024 << ' ';
    //     }
    //     wcout << "\n-------------------\n";
    // }
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