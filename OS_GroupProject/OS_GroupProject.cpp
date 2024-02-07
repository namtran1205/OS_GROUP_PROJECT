// OS_GroupProject.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <filesystem>
#include "Volumn.h"
#include "Entry.h"

void PrintDirectoryTree(const Volume& volume, uint32_t startCluster, int depth = 0) {
    std::string indent(depth * 2, ' '); // Create indentation based on the depth
    std::vector<Entry*> entries = volume.ReadDirectory(startCluster); // Hypothetical method to read directory entries

    for (const auto& entry : entries) {
        if (entry->is_Folder()) {
            // Print folder name with indentation
            std::cout << indent << entry->getMainName() << "\\" << std::endl;
            // Recursively print the contents of the folder
            PrintDirectoryTree(volume, entry->GetStartCluster(), depth + 1);
        }
        else {
            // Print file name with indentation
            std::cout << indent << entry->getMainName();
            if (!entry->getExtendedName().empty()) {
                std::cout << "." << entry->getExtendedName();
            }
            std::cout << std::endl;
        }
    }
}


int main()
{
    Volume volume;
    std::wstring drivePath = L"\\\\.\\F:"; // Example path to the drive
    volume.ReadVolume(drivePath); // Initialize the volume with drive information

    uint32_t startCluster = volume.GetStartClusterOfRootDirectory(); // Get the starting cluster of the root directory
    std::vector<Entry*> testEntries = volume.ReadDirectory(startCluster); // Test reading directory entries
    std::cout << "Number of entries: " << testEntries.size() << std::endl; // Debug statement

    PrintDirectoryTree(volume, startCluster); // Print the directory tree starting from the root
    return   0;
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
