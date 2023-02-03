#include "Algorithm.h"

bool isPathExists(std::string filename)
{
    std::filesystem::path directory = filename;
    directory.remove_filename();

    bool isDirectoryExists = std::filesystem::exists(directory);

    return isDirectoryExists;
}

bool str2int(std::string str, int *num)
{
    try
    {
        *num = std::stoi(str);
    }
    catch(...)
    {
        return 0;
    }

    return 1;
}

int getGcd(int a, int b)
{
    while (a && b)
    {
        a > b ? a %= b : b %= a;
    }
    
    return a + b; 
}
