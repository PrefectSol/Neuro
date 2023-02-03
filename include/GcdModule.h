#ifndef GCDMODULE_H
#define GCDMODULE_H

#include <iostream>
#include <filesystem>
#include <fstream>

#include "Network.h"
#include "Algorithm.h"

uint32_t runGcdModule(int argc, char **argv);

uint32_t createGcdData(int countData, std::string filename);

#endif // !GCDMODULE_H