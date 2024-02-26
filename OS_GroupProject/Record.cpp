#include "Record.h"

Record::Record(uint64_t FirstReadPoint, shared_ptr<BPB> bootSector)
{
	this->FirstReadPoint = FirstReadPoint;
	this->bootSector = bootSector;
	vector<BYTE> data = bootSector->GetSectorReader()->ReadBytes(FirstReadPoint, 42);
	for (int i = 0; i < 4; i++)
		mask += static_cast<char>(data[i]);
	firstAttribute = Utils::MyINTEGER::Convert2LitleEndian(data.begin() + 0x14, 2);

	// Read list Attribute
	uint64_t AdressAttribute = firstAttribute;
	while (Utils::MyINTEGER::Convert2LitleEndian((bootSector->GetSectorReader()->ReadBytes(AdressAttribute,4)).begin(), 4) != 0xffffffff && AdressAttribute < FirstReadPoint + bootSector->getMFTsize())
	{
		shared_ptr<HeaderAttribute> tmp = make_shared<HeaderAttribute>(HeaderAttribute(AdressAttribute, bootSector));
		shared_ptr<AttributeNTFS> attribute;
		if (tmp->getID() == 16)		//Standard Information
		{
			 attribute = make_shared<AttributeNTFS>(Standard_Info(tmp));
			
			
		}
		else if (tmp->getID() == 48) //File Name
		{
			 attribute = make_shared<AttributeNTFS>(File_Name(tmp));
			
		}
		else if (tmp->getID() == 128)	//Data
		{
			 attribute = make_shared<AttributeNTFS>(Data(tmp));
			
		}
		else // another attribute
		{
			 attribute = make_shared<AttributeNTFS>(AttributeNTFS(tmp));

		}

		listAttribute.push_back(attribute);
		AdressAttribute = attribute->getNextAttributeAddress();
		
	}

}

uint64_t Record::GetNextAddressRecord() const
{
	return FirstReadPoint + bootSector->getMFTsize() ;
}
