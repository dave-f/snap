#include <cstddef>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <memory>

// Build on g++ with -std=c++11
static constexpr char versionString[] = "0.1";

void displayTitle()
{
    std::cout << "snap (version " << versionString << ")" << std::endl;
}

void displayUsage()
{
    std::cout << "A utility to patch one binary file into another" << std::endl << std::endl;
    std::cout << "Usage: " << std::endl;
    std::cout << "        snap <file> <patchfile> <offset>" << std::endl << std::endl;
}

void processFiles(const std::string& in, const std::string& patch, size_t offset)
{

}

int main(int argc, char** argv)
{
    std::string inputFile;
    std::string patchFile;
    size_t offset = 0;

    if (argc == 3)
    {
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

    processFiles(inputFile,patchFile,offset);

    return 1;
}
