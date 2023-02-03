#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include "AuditLog.h"
#include "GcdModule.h"

enum Module
{
    GCD = 0
};

class NetworkManager
{
public:
    static uint32_t runModule(int module, int argc, char **argv);

protected:

private:
};

#endif // !NETWORKMANAGER_H