#include "BPB.h"

BPB::BPB(shared_ptr<SectorReader> sectorReader)
{
	// đọc 512 byte đầu tiên
	this->sectorReader = sectorReader;
	std::vector<BYTE> memory = sectorReader->ReadSector(0, 1);
	uint64_t BPB_Address = Utils::MyINTEGER::Convert2LittleEndian(memory.begin() + 0xC6, 4); // đọc địa chỉ bắt đầu vùng BPB
	memory = sectorReader->ReadSector(BPB_Address, 1);                           // đọc vùng BPB 
	// đọc các thông số vùng BPB
	BytePerSector = Utils::MyINTEGER::Convert2LittleEndian(memory.begin() + 0xB, 2);       // 0xB 2 byte
	SectorPerCluster = Utils::MyINTEGER::Convert2LittleEndian(memory.begin() + 0xD, 1);    // 0xD->0xD
	MFTsize = (char) memory[0x40];        // 0x40->0x40  the true size is 2^abs(MFTsize)
	SectorVolume = Utils::MyINTEGER::Convert2LittleEndian(memory.begin() + 0x28, 8);       // 0x28->0x2F
	StartMFTCluster = Utils::MyINTEGER::Convert2LittleEndian(memory.begin() + 0x30, 8);    // 0x30->0x37
	StartMFTMirrorCluster = Utils::MyINTEGER::Convert2LittleEndian(memory.begin() + 0x38, 8); 

	sectorReader->SetByteOfSector(BytePerSector);

}

BPB::~BPB()
{
}

void BPB::readVolumeBootRecord()
{
	
	std::wcout << L"Sectors per cluster - Sc = " << (int)SectorPerCluster << std::endl;
	std::wcout << L"MFTsize (true value) = " << "2^"<<abs(MFTsize) << std::endl;
	std::wcout << L"Sector of Volume - Sv = " << SectorVolume << std::endl;
	std::wcout << L"Bytes per Sectors - BytePerSector = " << BytePerSector << std::endl;
	std::wcout << L"Start cluster of MFT = " << StartMFTCluster << std::endl;
}

shared_ptr<SectorReader> BPB::GetSectorReader() const
{
	return sectorReader;
}

uint64_t BPB::getSectorPerCluster() const
{
	return SectorPerCluster;
}

uint64_t BPB::getBytePerSector() const
{
	return BytePerSector;
}

uint64_t BPB::getMFTsize() const
{
	if (abs(MFTsize) > 64) return -1;
	return 1 << abs(MFTsize);
}

uint64_t BPB::getStartMFTCluster() const
{
	return StartMFTCluster;
}

uint64_t BPB::getSizeOfVolume() const
{
	return SectorVolume * BytePerSector;
}

uint64_t BPB::getMFTMirror() const
{
	return StartMFTMirrorCluster * SectorPerCluster * BytePerSector;
}



