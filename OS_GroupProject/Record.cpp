#include "Record.h"

Record::Record(uint64_t FirstReadPoint, shared_ptr<BPB> bootSector)
{
	this->FirstReadPoint = FirstReadPoint;
	this->bootSector = bootSector;
	vector<BYTE> data = bootSector->GetSectorReader()->ReadBytes(FirstReadPoint, bootSector->getMFTsize());
    

	for (int i = 0; i < 4; i++)
		mask += static_cast<char>(data[i]);
	firstAttribute = Utils::MyINTEGER::Convert2LittleEndian(data.begin() + 0x14, 2);
	this->status = Utils::MyINTEGER::Convert2LittleEndian(data.begin() + 0x16, 2);
	if (status == 0) return;
	// Read list Attribute
	uint64_t AdressAttribute = firstAttribute;
	//uint64_t tmp = Utils::MyINTEGER::Convert2LittleEndian(data.begin() + 408, 4);
	while (Utils::MyINTEGER::Convert2LittleEndian(data.begin() + AdressAttribute, 4) != 0xffffffff && AdressAttribute < data.size())
	{
		shared_ptr<HeaderAttribute> tmp = make_shared<HeaderAttribute>(HeaderAttribute(AdressAttribute , data, bootSector));
		shared_ptr<AttributeNTFS> attribute;
		if (tmp->getID() == 16)		//Standard Information
		{
			 attribute = make_shared<Standard_Info>(Standard_Info(tmp, data));
			
			
		}

		else if (tmp->getID() == 48) //File Name
		{
			 attribute = make_shared<File_Name>(File_Name(tmp, data));
			
		}
		else if (tmp->getID() == 128)	//Data
		{
			 attribute = make_shared<Data>(Data(tmp, data));
			
		}
		else // another attribute
		{
			 attribute = make_shared<AttributeNTFS>(AttributeNTFS(tmp, data));

		}

		listAttribute.push_back(attribute);
		AdressAttribute = attribute->getNextAttributeAddress();

	}

}

uint64_t Record::GetNextAddressRecord() const
{
	return FirstReadPoint + bootSector->getMFTsize() ;
}

std::string Record::getMask() const
{
	return mask;
}

uint64_t Record::getFlag()
{
	for (auto it : listAttribute)
	{
		if (it->getBasicHeader()->getID() == 16) {
		
			
			return it->getFlag();
			

		}
	}
	return 2;
}

std::wstring Record::getName() 
{
	for (const auto& it : listAttribute)
		if (it->getBasicHeader()->getID() == 48)
		{
			return it->getFileName();
		}
	return L"";
}

int Record::isUse()
{
	return (status & 1);
}

bool Record::isFolder()
{
	return (status & 2);
}

void Record::printFileContent() 
{
	for(const auto &it: listAttribute)
		if (it->getBasicHeader()->getID() == 128)
		{
			it->getBasicInfo();
			return;
		}
}

uint64_t Record::getParentID()
{
	for (const auto& it : listAttribute)
		if (it->getBasicHeader()->getID() == 48)
		{
			return it->getParentID();
		}
	return 0;
}

uint64_t Record::getStatus()
{
	return status;
}

uint64_t Record::getSize()
{
	if (isFolder()) return 0;
	for(auto it : listAttribute)
		if (it->getBasicHeader()->getID() == 128)
		{
			return it->getSize();
		}
	return 0;
}

std::pair<std::wstring, std::wstring> Record::getLastWriteTime()
{
	for (auto it : listAttribute)
	{
		if (it->getBasicHeader()->getID() == 16)
		{
			return it->getLastWriteTime();
		}
	}

	return std::pair<std::wstring, std::wstring>();
}
