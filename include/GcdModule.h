#ifndef GCDMODULE_H
#define GCDMODULE_H

#include <iostream>
#include <vector>
#include <filesystem>
#include <fstream>

#include "Network.h"
#include "Algorithm.h" 

const int numLimit = 100000;

uint32_t runGcdModule(int argc, const char **argv);

uint32_t initData(int argc, const char **argv, int countData, std::vector<std::pair<double, double>> *inputData, std::vector<double> *outputData);

void createGcdData(int countData, std::vector<std::pair<double, double>> *inputData, std::vector<double> *outputData);

uint32_t createGcdData(int countData, std::string filename);

uint32_t readGcdDataFile(std::string filename, std::vector<std::pair<double, double>> *inputData, std::vector<double> *outputData);

#endif // !GCDMODULE_H