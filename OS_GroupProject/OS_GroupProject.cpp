// OS_GroupProject.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Volumn.h"
#include "Entry.h"
int main()
{
    std::cout << "Hello World!\n";
    std::ifstream in("your_file_path.bin", std::ios::binary);

    if (!in.is_open()) {
        std::cerr << "Cannot open the file." << std::endl;
        return 1;
    }

    Volume volume;
    // Thay thế giá trị thực tế cho các thông số của Volume
    volume.SetNumberOfFat(/* Your number of FATs */);
    volume.SetSectorPerCluster(/* Your sector per cluster */);
    volume.SetSectorPerBootSector(/* Your sector per boot sector */);
    volume.SetSectorVolume(/* Your total sectors in volume */);

    // Đọc bảng FAT
    volume.ReadFatTable(in);

    // Hiển thị các giá trị trong bảng FAT
    for (int i = 0; i < volume.GetFatTable().size(); ++i) {
        std::cout << "FAT[" << i << "]: " << volume.GetFatTable()[i] << std::endl;
    }

    in.close();
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
