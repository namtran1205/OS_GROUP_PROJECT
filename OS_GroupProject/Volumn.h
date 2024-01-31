#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <sstream>



class Volumn
{
private:
	uint8_t numberOfFat;
	std::vector<uint32_t> fatTable;
	uint8_t SectorPerCluster;
	uint16_t SectorPerBootsector;
	uint32_t SectorVolumn;
public:
		void ReadFatTable(std::ifstream);
		

	 

	 

};

