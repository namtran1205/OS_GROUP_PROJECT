#include "AttributeNTFS.h"

HeaderAttribute::HeaderAttribute(uint64_t Address, shared_ptr<BPB> bootSector)
{
	
	this->bootSector = bootSector;

	std::vector<BYTE> data = bootSector->GetSectorReader()->ReadBytes(Address, 22);
	ID = Utils::MyINTEGER::Convert2LitleEndian(data.begin(), 4);                     // 0x0->0x3 
    Size = Utils::MyINTEGER::Convert2LitleEndian(data.begin() + 0x4, 4);             // 0x4->0x7
    nonResidentFlag = Utils::MyINTEGER::Convert2LitleEndian(data.begin() + 0x8, 1);  // 0x8->0x8 
    maskFlag = Utils::MyINTEGER::Convert2LitleEndian(data.begin() + 0xC, 2);         // 0xC->0xD

	if (!nonResidentFlag)
	{
	    contentSize = Utils::MyINTEGER::Convert2LitleEndian(data.begin() + 0x16, 4);
    	contentAddress = Utils::MyINTEGER::Convert2LitleEndian(data.begin() + 0x20, 2) + Address;
	}

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

AttributeNTFS::AttributeNTFS(shared_ptr<HeaderAttribute> headerAttribute)
{
	this->basicHeader = headerAttribute;
} 

Standard_Info::Standard_Info(shared_ptr<HeaderAttribute> headerAttribute)
{
	AttributeNTFS(headerAttribute);
	vector<BYTE> data = headerAttribute->GetBPB()->GetSectorReader()->ReadBytes(basicHeader->getContentAddress(), basicHeader->getContentSize());

	flag = Utils::MyINTEGER::Convert2LitleEndian(data.begin() + 0x32, 4);
}

File_Name::File_Name(shared_ptr<HeaderAttribute> headerAttribute)
{
	AttributeNTFS(headerAttribute);
	vector<BYTE> data = headerAttribute->GetBPB()->GetSectorReader()->ReadBytes(basicHeader->getContentAddress(), basicHeader->getContentSize());
	uint64_t LengthOfName = Utils::MyINTEGER::Convert2LitleEndian(data.begin() + 0x64, 1);
	NameOfFile = Utils::MySTRING::convertBytesToWstring(vector<BYTE>(data.begin() + 0x66, data.begin() + 0x66 + LengthOfName* 2 - 1));

}

std::wstring File_Name::getFileName() const
{
	return NameOfFile;
}

Data::Data(shared_ptr<HeaderAttribute> headerAttribute)
{
	AttributeNTFS(headerAttribute);
}

void Data::getBasicInfo()
{
	vector<BYTE> data = basicHeader->GetBPB()->GetSectorReader()->ReadBytes(basicHeader->getContentAddress(), basicHeader->getContentSize());
	for(auto c:data) std::wcout << c;
}
