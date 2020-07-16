#include <cstddef>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <memory>
#include <vector>

// Build on g++ with -std=c++11
static constexpr char versionString[] = "1.0";

void displayTitle()
{
    std::cout << "snap (version " << versionString << ")" << std::endl;
}

void displayUsage()
{
    std::cout << "A utility to patch a binary file into another" << std::endl << std::endl;
    std::cout << "Usage: " << std::endl;
    std::cout << "        snap <file> <patchfile> [offset]" << std::endl << std::endl;
}

void processFiles(const std::string& target, const std::string& patch, size_t offset)
{
    std::fstream targetFile;
    std::fstream patchFile;

    targetFile.exceptions(std::fstream::failbit | std::fstream::badbit);
    patchFile.exceptions(std::fstream::failbit | std::fstream::badbit);

    targetFile.open(target, std::ios::binary | std::ios::out | std::ios::in | std::ios::ate);
    patchFile.open(patch, std::ios::binary | std::ios::in | std::ios::ate);

    size_t patchFileSize = patchFile.tellg();
    size_t targetFileSize = targetFile.tellg();

    if ((patchFileSize + offset) > targetFileSize)
    {
        throw std::exception("Patch exceeds original size");
    }

    patchFile.seekg(0);
    targetFile.seekg(offset);
    std::vector<uint8_t> patchBuffer(patchFileSize);
    patchFile.read(reinterpret_cast<char*>(patchBuffer.data()), patchFileSize);
    targetFile.write(reinterpret_cast<char*>(patchBuffer.data()), patchBuffer.size());
    patchFile.close();
    targetFile.close();
}

int main(int argc, char** argv)
{
    std::string inputFile;
    std::string patchFile;
    size_t offset = 0;

    if (argc == 3)
    {
        inputFile = argv[1];
        patchFile = argv[2];
        offset = 0;
    }
    else if (argc == 4)
    {
        inputFile = argv[1];
        patchFile = argv[2];

        try
        {
            offset = std::stoi(argv[3]);
        }
        catch (const std::exception&)
        {
            displayUsage();

            return 1;
        }
    }
    else
    {
        displayTitle();
        displayUsage();

        return 1;
    }

    try
    {
        processFiles(inputFile, patchFile, offset);

        return 0;
    }
    catch (const std::exception& e)
    {
        std::cout << "Error: " << e.what() << std::endl;
    }

    return 1;
}
