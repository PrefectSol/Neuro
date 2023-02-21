#include "NetworkManager.h"

uint32_t NetworkManager::runModule(const Json::Value &config, ErrorCode modulesResult[2])
{
    uint32_t runTestingModuleCode;
    const int runTestingModule = config["Creation modules"]["Run the module"].asInt();
    switch (runTestingModule)
    {
    case 0:
        runTestingModuleCode = ErrorCode::moduleNotSelected;
        break;

    case 1:
        runTestingModuleCode = runGcdModule(config);
        break;

    case 2:
        runTestingModuleCode = runTemplateModule(config);
        break;

    case 3:
        runTestingModuleCode = runParsingModule(config);
        break;

    default:
        runTestingModuleCode = ErrorCode::cannotFindModule;
        break;
    }

    uint32_t runImplementationModuleCode;
    const int runImplementationModule = config["Implementation modules"]["Run the module"].asInt();
    switch (runImplementationModule)
    {
    case 0:
        runImplementationModuleCode = ErrorCode::moduleNotSelected;
        break;
        
    case 1:
        runImplementationModuleCode =  ErrorCode::unavailableModule;
        break;

    case 2:
        runImplementationModuleCode = ErrorCode::unavailableModule;
        break;

    default:
        runImplementationModuleCode = ErrorCode::cannotFindModule;
        break;
    }

    modulesResult[0] = (ErrorCode)runTestingModuleCode;
    modulesResult[1] = (ErrorCode)runImplementationModuleCode;

    return runTestingModuleCode && runImplementationModuleCode;
}