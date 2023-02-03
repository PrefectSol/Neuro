#include "GcdModule.h"

uint32_t runGcdModule(int argc, char **argv)
{
    if (argc != 4)
    {
        return ErrorCode::notEnoughArguments;
    }

    int countData;
    bool isInt = str2int(argv[2], &countData);
    if (!isInt)
    {
        return ErrorCode::cannotConvertStrToInt;
    }

    uint32_t isCreateGcdData = createGcdData(countData, argv[3]);
    if (isCreateGcdData != ErrorCode::success)
    {
        return isCreateGcdData;
    }

    return ErrorCode::success;
}

uint32_t createGcdData(int countData, std::string filename)
{
    std::ofstream writer(filename);
    
    if(!writer.is_open())
    {
        return ErrorCode::cannotOpenFile;
    }

    srand(time(NULL));
    const int numLimit = 10000;

    for(int i = 0; i < countData; i++)
    {
        int num1 = rand() % numLimit;
        int num2 = rand() % numLimit;

        int gcd = getGcd(num1, num2);
        
        writer << num1 << " " << num2 << " " << gcd << '\n';
    }   

    return ErrorCode::success;
}
