#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include <fstream>

#include <json/json.h>

#include "AuditLog.h"

#include "Modules/GcdModule.h"
#include "Modules/ParsingModule.h"

class NetworkManager
{
public:
    static uint32_t runModule(const Json::Value &config, ErrorCode modulesResult[2] = {});

protected:

private:
};

#endif // !NETWORKMANAGER_H