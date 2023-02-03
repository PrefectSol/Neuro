#include "NetworkManager.h"

uint32_t NetworkManager::runModule(int module, int argc, const char **argv)
{
    uint32_t isRunModule;
    switch (module)
    {
    case Module::GCD:
        isRunModule = runGcdModule(argc, argv);
        break;
    
    default:
        isRunModule = ErrorCode::unavailableModule;
        break;
    }

    return isRunModule;
}