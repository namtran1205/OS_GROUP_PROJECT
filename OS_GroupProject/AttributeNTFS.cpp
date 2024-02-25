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

AttributeNTFS::AttributeNTFS(shared_ptr<HeaderAttribute> headerAttribute)
{
	this->basicHeader = headerAttribute;
}

uint64_t AttributeNTFS::getNextAttributeAddress() const
{
	return basicHeader->GetAttributeAddress() + basicHeader->getSize();
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

Data::Data(shared_ptr<HeaderAttribute> header)
{
	AttributeNTFS(header);
	if (!basicHeader->isResident())
	{
		// n?u l� non resident ta c?n ??c run list ? byte 64 trong data attribute
		// c?u tr�c run list g?m 1 header v� 1 content li�n ti?p nhau
		// - header l� 1 byte 
		// 1/2 byte th?p cho bik S? BYTE quy ??nh s? cluster ?? l?u d? li?u
		// 1/2 byte cao cho bik S? BYTE quy ??nh offset c?a cluster ??u ti�n khi l?u tr?
		// - content l� 1 d�y byte v?i c�c byte ??u l?u tr? s? cluster v� c�c byte sau l?u tr? offset cluster ??u ti�n
		vector<BYTE> memory = basicHeader->GetBPB()->GetSectorReader()->ReadBytes(basicHeader->GetAttributeAddress() + 64, 32);
		uint64_t bytePerCluster = basicHeader->GetBPB()->getBytePerSector() * basicHeader->GetBPB()->getSectorPerCluster();
		basicHeader->setContentSize(Utils::MyINTEGER::Convert2LitleEndian(memory.begin() + 1, (memory[0] | 15)) * bytePerCluster);
		basicHeader->setContentAddress(Utils::MyINTEGER::Convert2LitleEndian(memory.begin() + 1 + (memory[0] | 15), (memory[0] >> 4)) * bytePerCluster - bytePerCluster + 1);
	}
}

void Data::getBasicInfo()
{
	vector<BYTE> data = basicHeader->GetBPB()->GetSectorReader()->ReadBytes(basicHeader->getContentAddress(), basicHeader->getContentSize());
	for(auto c:data) std::wcout << c;
}
