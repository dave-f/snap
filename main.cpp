#include <cstddef>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <memory>
#include <vector>

// Build on g++ with -std=c++11
static constexpr char versionString[] = "1.1";

void displayTitle()
{
    std::cout << "snap (version " << versionString << ")" << std::endl;
}

void displayUsage()
{
    std::cout << "A utility to patch a binary file into another," << std::endl;
    std::cout << "optionally writing out to a new file." << std::endl << std::endl;
    std::cout << "Usage: " << std::endl;
    std::cout << "        snap <file> <patchfile> <offset> [newfile]" << std::endl << std::endl;
}

void processFiles(const std::string& src, const std::string& patch, const std::string& dst, size_t offset)
{
    std::fstream srcFile;
    std::fstream patchFile;
    std::fstream dstFile;

    srcFile.exceptions(std::fstream::failbit | std::fstream::badbit);
    patchFile.exceptions(std::fstream::failbit | std::fstream::badbit);
    dstFile.exceptions(std::fstream::failbit | std::fstream::badbit);

    srcFile.open(src, std::ios::binary | std::ios::out | std::ios::in | std::ios::ate);
    patchFile.open(patch, std::ios::binary | std::ios::in | std::ios::ate);

    std::streamoff patchFileSize = patchFile.tellg();
    std::streamoff srcFileSize = srcFile.tellg();

    if ((patchFileSize + (int)offset) > srcFileSize)
    {
        throw std::runtime_error("Patch exceeds original size");
    }

    std::vector<uint8_t> patchBuffer(static_cast<size_t>(patchFileSize));
	patchFile.seekg(0);
    patchFile.read(reinterpret_cast<char*>(patchBuffer.data()), patchFileSize);

    if (dst.empty())
    {
		srcFile.seekg(offset);
		srcFile.write(reinterpret_cast<char*>(patchBuffer.data()), patchBuffer.size());
    }
    else
    {
		std::vector<uint8_t> srcBuffer(static_cast<size_t>(srcFileSize));
		srcFile.seekg(0);
		srcFile.read(reinterpret_cast<char*>(srcBuffer.data()), srcFileSize);
		std::copy(patchBuffer.begin(), patchBuffer.end(), srcBuffer.begin() + offset);
		dstFile.open(dst, std::ios::binary | std::ios::out | std::ios::trunc);
		dstFile.write(reinterpret_cast<char*>(srcBuffer.data()), srcBuffer.size());
		dstFile.close();
    }

    patchFile.close();
    srcFile.close();
}

int main(int argc, char** argv)
{
    std::string inputFile;
    std::string patchFile;
    std::string newFile;
    size_t offset = 0;

    if (argc == 4 || argc == 5)
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

        if (argc == 5)
        {
            newFile = argv[4];
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
        processFiles(inputFile, patchFile, newFile, offset);

        return 0;
    }
    catch (const std::exception& e)
    {
        std::cout << "Error: " << e.what() << std::endl;
    }

    return 1;
}
