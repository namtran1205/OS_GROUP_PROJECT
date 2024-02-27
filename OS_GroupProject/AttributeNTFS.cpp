#include "AttributeNTFS.h"

HeaderAttribute::HeaderAttribute(uint64_t Address,vector<BYTE>& data, shared_ptr<BPB> bootSector)
{
	//printSector(data);
	this->bootSector = bootSector;
	attributeAddress = Address;
	ID = Utils::MyINTEGER::Convert2LitleEndian(data.begin() + Address, 4);                     // 0x0->0x3 
    Size = Utils::MyINTEGER::Convert2LitleEndian(data.begin() + Address + 0x4, 4);             // 0x4->0x7
    nonResidentFlag = Utils::MyINTEGER::Convert2LitleEndian(data.begin()+ Address + 0x8, 1);  // 0x8->0x8 
    maskFlag = Utils::MyINTEGER::Convert2LitleEndian(data.begin() + Address + 0xC, 2);         // 0xC->0xD

	if (!nonResidentFlag) // check
	{
	    contentSize = Utils::MyINTEGER::Convert2LitleEndian(data.begin() + Address + 0x16, 4);
    	contentAddress = Utils::MyINTEGER::Convert2LitleEndian(data.begin() + Address + 0x20, 2) + Address;
	}
	else
	{
		contentSize = 0;
		contentAddress = 0;
	}

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



Standard_Info::Standard_Info(shared_ptr<HeaderAttribute> headerAttribute, vector<BYTE>& data)
{
	basicHeader = headerAttribute;
	
	flag = Utils::MyINTEGER::Convert2LitleEndian(data.begin()+ headerAttribute->GetAttributeAddress() + 0x32, 4);
}

File_Name::File_Name(shared_ptr<HeaderAttribute> headerAttribute, vector<BYTE>& data)
{
	basicHeader = headerAttribute;
	uint64_t LengthOfName = Utils::MyINTEGER::Convert2LitleEndian(data.begin() + headerAttribute->GetAttributeAddress() + 0x64, 1);
	
	if (LengthOfName > 0) NameOfFile = Utils::MySTRING::convertBytesToWstring(vector<BYTE>(data.begin()+ headerAttribute->GetAttributeAddress() + 0x66, data.begin()+ headerAttribute->GetAttributeAddress() + 0x66 + LengthOfName* 2 - 1));

}

std::wstring File_Name::getFileName() const
{
	return NameOfFile;
}

Data::Data(shared_ptr<HeaderAttribute> header, vector<BYTE>& memory)
{
	basicHeader = header;
	if (!basicHeader->isResident())
	{
		// nễu là non resident, ta cần đọc run list ở byte 64 trong data attribute
		// cấu trúc run list gồm 1 header và 1 content liên tiếp nhau
		// - header là 1 byte 
		// 1/2 byte thấp cho bik SỐ BYTE quy định số cluster để lưu dữ liệu
		// 1/2 byte cao cho bik SỐ BYTE quy định offset của cluster đầu tiên khi lưu trữ
		// - content là 1 dãy byte với các byte đầu lưu trữ số cluster và các byte sau lưu trữ offset cluster đầu tiên
		
		uint64_t bytePerCluster = basicHeader->GetBPB()->getBytePerSector() * basicHeader->GetBPB()->getSectorPerCluster();
		basicHeader->setContentSize(Utils::MyINTEGER::Convert2LitleEndian(memory.begin()+ header->GetAttributeAddress() + 1, (memory[0] | 15)) * basicHeader->GetBPB()->getSectorPerCluster());
		basicHeader->setContentAddress(Utils::MyINTEGER::Convert2LitleEndian(memory.begin() + header->GetAttributeAddress()+ 1 + (memory[0] | 15), (memory[0] >> 4)) * bytePerCluster);
	}
	else 
	{
		this->residentContent = string(memory.begin() + basicHeader->getContentAddress(), memory.begin() + basicHeader->getContentAddress() + basicHeader->getContentSize());
	}
}

void Data::getBasicInfo()
{
	if (basicHeader->isResident())
	{
		std::wcout << residentContent.c_str() << '\n';
		return;
	}
	vector<BYTE> data = basicHeader->GetBPB()->GetSectorReader()->ReadSector(basicHeader->getContentAddress(), basicHeader->getContentSize());
	for(char c:data) std::wcout << c;
	wcout << '\n';
}
