#include "AttributeNTFS.h"

HeaderAttribute::HeaderAttribute(uint64_t Address,vector<BYTE>& data, shared_ptr<BPB> bootSector)
{
	
	this->bootSector = bootSector;
	attributeAddress = Address;
	ID = Utils::MyINTEGER::Convert2LittleEndian(data.begin() + Address, 4);                     // 0x0->0x3 
    Size = Utils::MyINTEGER::Convert2LittleEndian(data.begin() + Address + 0x4, 4);             // 0x4->0x7
    nonResidentFlag = Utils::MyINTEGER::Convert2LittleEndian(data.begin()+ Address + 0x8, 1);  // 0x8->0x8 
    maskFlag = Utils::MyINTEGER::Convert2LittleEndian(data.begin() + Address + 0xC, 2);         // 0xC->0xD

    contentAddress = Utils::MyINTEGER::Convert2LittleEndian(data.begin() + Address + 20, 2) + Address;
	if (!nonResidentFlag) 
	    contentSize = Utils::MyINTEGER::Convert2LittleEndian(data.begin() + Address + 16, 4);
}

void HeaderAttribute::setContentAddress(uint64_t contentAddress)
{
	this->contentAddress = contentAddress;

}

void HeaderAttribute::setContentSize(uint64_t contentSize)
{
	this->contentSize = contentSize;
}

shared_ptr<BPB> HeaderAttribute::GetBPB() const
{
	return this->bootSector;
}

uint64_t HeaderAttribute::getSize() const
{
    return this->Size;
}

uint64_t HeaderAttribute::getMask() const
{
    return maskFlag;
}


bool HeaderAttribute::isResident() const
{
	return !nonResidentFlag;
}
    
uint64_t HeaderAttribute::getID() const
{
	return ID;
}

uint64_t HeaderAttribute::GetAttributeAddress() const
{
	return attributeAddress;
}

uint64_t HeaderAttribute::getContentAddress() const
{
	return contentAddress;
}

uint64_t HeaderAttribute::getContentSize() const
{
	return contentSize;
}







AttributeNTFS::AttributeNTFS() {}

AttributeNTFS::AttributeNTFS(shared_ptr<HeaderAttribute> headerAttribute, vector<BYTE>& data)
{
	this->basicHeader = headerAttribute;
}

uint64_t AttributeNTFS::getNextAttributeAddress() const
{
	return basicHeader->GetAttributeAddress() + basicHeader->getSize();
}

shared_ptr<HeaderAttribute> AttributeNTFS::getBasicHeader() const
{
	return basicHeader;
}

bool AttributeNTFS::isResident() const
{
	return this->basicHeader->isResident();
}

uint32_t AttributeNTFS::getFlag() const
{
	return 0;
}

uint64_t AttributeNTFS::getParentID() const
{
	return 0;
}

std::wstring AttributeNTFS::getFileName() const
{
	return std::wstring();
}

void AttributeNTFS::getBasicInfo()
{
}
std::pair<std::wstring, std::wstring> Standard_Info::getLastWriteTime() const
{
	return lastWriteTime;
}
std::pair<std::wstring, std::wstring> AttributeNTFS::getLastWriteTime() const
{
	return std::pair<std::wstring, std::wstring>();
}

uint64_t AttributeNTFS::getSize()
{
	return 0;
}



Standard_Info::Standard_Info(shared_ptr<HeaderAttribute> headerAttribute, vector<BYTE>& data)
{
	basicHeader = headerAttribute;
	// đọc trạng thái: system, archive,.....
	flag = Utils::MyINTEGER::Convert2LittleEndian(data.begin() + headerAttribute->getContentAddress() + 32, 4);
	// đọc thời gian truy cập
	lastWriteTime = Utils::MyDATE::extractTime_NTFS(data, headerAttribute->getContentAddress() + 24,8);

}

File_Name::File_Name(shared_ptr<HeaderAttribute> headerAttribute, vector<BYTE>& data)
{
	basicHeader = headerAttribute;
	// đọc thứ tự entry cha : đọc 6 byte đầu
	parentID = Utils::MyINTEGER::Convert2LittleEndian(data.begin() + headerAttribute->getContentAddress(), 6);
	// đọc chiều dài tên
	uint64_t LengthOfName = Utils::MyINTEGER::Convert2LittleEndian(data.begin() + headerAttribute->getContentAddress() + 64, 1);
	// đọc tên
	if (LengthOfName > 0) NameOfFile = Utils::MySTRING::convertBytesToWstring(vector<BYTE>(data.begin()+ headerAttribute->getContentAddress() + 66, data.begin() + headerAttribute->getContentAddress() + 66 + LengthOfName * 2 ));
	

}

std::wstring File_Name::getFileName() const
{
	return NameOfFile;
}

uint64_t File_Name::getParentID() const
{
	return parentID;
}

Data::Data(shared_ptr<HeaderAttribute> header, vector<BYTE>& memory)
{
	basicHeader = header;
	if (basicHeader->isResident())
	{
		this->residentContent.resize(0);
		for (int i = basicHeader->getContentAddress(); i < basicHeader->getContentAddress() + basicHeader->getContentSize(); i++)
			residentContent.push_back(memory[i]);
		return;
	}

	// nễu là non resident, ta cần đọc run list ở byte 64 trong data attribute
	// cấu trúc run list gồm 1 header và 1 content liên tiếp nhau
	// - header là 1 byte 
	// 1/2 byte thấp cho bik SỐ BYTE quy định số cluster để lưu dữ liệu
	// 1/2 byte cao cho bik SỐ BYTE quy định offset của cluster đầu tiên khi lưu trữ
	// - content là 1 dãy byte với các byte đầu lưu trữ số cluster và các byte sau lưu trữ offset cluster đầu tiên
	
	uint64_t curRunsListAddress = Utils::MyINTEGER::Convert2LittleEndian(memory.begin() + basicHeader->GetAttributeAddress() + 32, 2) + basicHeader->GetAttributeAddress();
	uint64_t bytePerCluster = basicHeader->GetBPB()->getBytePerSector() * basicHeader->GetBPB()->getSectorPerCluster();
	uint64_t attributeLim = basicHeader->GetAttributeAddress() + basicHeader->getSize();
	while (curRunsListAddress < attributeLim)
	{
		BYTE numByteContentSize = memory[curRunsListAddress] & 15;
		BYTE numByteContentAddress = (memory[curRunsListAddress] >> 4);
		if (!numByteContentSize || !numByteContentAddress || curRunsListAddress + numByteContentAddress + numByteContentSize + 1 >= attributeLim) break;
		uint64_t contentSize = Utils::MyINTEGER::Convert2LittleEndian(memory.begin() + curRunsListAddress + 1, numByteContentSize) * bytePerCluster;
		uint64_t contentAddress = Utils::MyINTEGER::Convert2LittleEndian(memory.begin() + curRunsListAddress + 1 + numByteContentSize, numByteContentAddress) * bytePerCluster;
		this->runsList.push_back(make_pair(contentAddress, contentSize));
		curRunsListAddress += numByteContentAddress + numByteContentSize + 1;
	}

}

void Data::getBasicInfo()
{
	// xử lí in nội dung với trường hợp resident
	if (basicHeader->isResident())
	{
		std::wcout << residentContent.c_str();
		return;
	}

	// xử lí in nội dung với trường hơp non-resident
	vector<BYTE> data;
	for(auto it:runsList)
	{
		data = basicHeader->GetBPB()->GetSectorReader()->ReadSector(it.first, it.second);
		for (char c : data)
		{
			if (c == '\0') return;
			std::wcout << c;
		}
	}
}

uint64_t Data::getSize()
{
	if (basicHeader->isResident()) return basicHeader->getContentSize();
	// xử lí riêng với trường hợp non-resident
	uint64_t sumSize = 0;
	for(auto it:runsList) sumSize += it.second;
	return sumSize;
}

uint32_t Standard_Info::getFlag() const
{
	return flag; // trạng thái entry
}
