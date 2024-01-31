#include "Volumn.h"
uint32_t ConvertEndian(uint32_t bigEndianValue) {
    return ((bigEndianValue & 0xFF) << 24) |
        (((bigEndianValue >> 8) & 0xFF) << 16) |
        (((bigEndianValue >> 16) & 0xFF) << 8) |
        ((bigEndianValue >> 24) & 0xFF);
}
void Volume::ReadFatTable(std::ifstream in)
{
    int fatSize = SectorPerBootsector * numberOfFat;

    // Di chuyển đến vị trí của bảng FAT trong file
    in.seekg(SectorPerBootsector * BytePerSector, std::ios::beg);

    // Đọc từng entry trong bảng FAT và chuyển đổi sang Little Endian 
    for (int i = 0; i < fatSize; ++i) {
        uint32_t fatEntry;
        in.read(reinterpret_cast<char*>(&fatEntry), sizeof(uint32_t));
        fatTable.push_back(ConvertEndian(fatEntry));
    }
}

std::vector<uint32_t> Volume::GetFatTable()
{
    return fatTable;

}

