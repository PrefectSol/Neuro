#include "GcdModule.h"

uint32_t runGcdModule(int argc, const char **argv)
{
    if (argc < 3)
    {
        return ErrorCode::notEnoughArguments;
    }

    int countData;
    bool isInt = str2int(argv[2], &countData);
    if (!isInt)
    {
        return ErrorCode::cannotConvertStrToInt;
    }

    std::vector<std::pair<int, int>> inputData;
    std::vector<int> outputData;
    
    uint32_t isInitData = initData(argc, argv, countData, &inputData, &outputData);
    if (isInitData != ErrorCode::success)
    {
        return isInitData;
    }


    // run nn training...
    // ...


    return ErrorCode::success;
}

uint32_t initData(int argc, const char **argv, int countData, std::vector<std::pair<int, int>> *inputData, std::vector<int> *outputData)
{
    if (argc > 3 && isPathExists(argv[3]))
    {
        uint32_t isCreateGcdData = createGcdData(countData, argv[3]);
        if (isCreateGcdData != ErrorCode::success)
        {
            return isCreateGcdData;
        }

        uint32_t isReadGcdDataFile = readGcdDataFile(argv[3], inputData, outputData);
        
        return isReadGcdDataFile;
    }   

    createGcdData(countData, inputData, outputData);

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
    for(int i = 0; i < countData; i++)
    {
        int num1 = rand() % numLimit;
        int num2 = rand() % numLimit;

        int gcd = getGcd(num1, num2);
        
        writer << num1 << " " << num2 << " " << gcd << '\n';
    }   

    writer.close();

    return ErrorCode::success;
}

void createGcdData(int countData, std::vector<std::pair<int, int>> *inputData, std::vector<int> *outputData)
{
    srand(time(NULL));
    for(int i = 0; i < countData; i++)
    {
        int num1 = rand() % numLimit;
        int num2 = rand() % numLimit;
        
        int gcd = getGcd(num1, num2);
        
        inputData->push_back(std::make_pair(num1, num2));
        outputData->push_back(gcd);
    }   
}

uint32_t readGcdDataFile(std::string filename, std::vector<std::pair<int, int>> *inputData, std::vector<int> *outputData)
{
    std::ifstream reader(filename);

    if(!reader.is_open())
    {
        return ErrorCode::cannotOpenFile;
    }

    int num1, num2, gcd;
    while(!reader.eof())
    {
        reader >> num1 >> num2 >> gcd;

        inputData->push_back(std::make_pair(num1, num2));
        outputData->push_back(gcd);
    }

    reader.close();

    return ErrorCode::success;
}