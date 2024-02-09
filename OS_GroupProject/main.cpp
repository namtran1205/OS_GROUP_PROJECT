// OS_GroupProject.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "StaticVariable.h"
#include "FAT32.h"


// void PrintDirectoryTree(const Volume& volume, uint32_t startCluster, int depth = 0) {
//     std::string indent(depth * 2, ' '); // Create indentation based on the depth
//     std::vector<Entry*> entries = volume.ReadDirectory(startCluster); // Hypothetical method to read directory entries

//     for (const auto& entry : entries) {
//         if (entry->is_Folder()) {
//             // Print folder name with indentation
//             std::cout << indent << entry->getMainName() << "\\" << std::endl;
//             // Recursively print the contents of the folder
//             PrintDirectoryTree(volume, entry->GetStartCluster(), depth + 1);
//         }
//         else {
//             // Print file name with indentation
//             std::cout << indent << entry->getMainName();
//             if (!entry->getExtendedName().empty()) {
//                 std::cout << "." << entry->getExtendedName();
//             }
//             std::cout << std::endl;
//         }
//     }
// }


int main()
{
    // Volume volume;
    // std::wstring drivePath = L"\\\\.\\F:"; // Example path to the drive
    // volume.ReadVolume(drivePath); // Initialize the volume with drive information
    // uint32_t startCluster = volume.GetStartClusterOfRootDirectory(); // Get the starting cluster of the root directory
    // std::vector<Entry*> testEntries = volume.ReadDirectory(startCluster); // Test reading directory entries
    // std::cout << "Number of entries: " << testEntries.size() << std::endl; // Debug statement
    // PrintDirectoryTree(volume, startCluster); // Print the directory tree starting from the root
    
    FAT32* fat32 = new FAT32();
    fat32->readVolume(L"\\\\.\\F:");
    delete fat32;
    fat32 = nullptr;
    return   0;
}

