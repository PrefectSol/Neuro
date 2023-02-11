#ifndef GCDMODULE_H
#define GCDMODULE_H

#include <iostream>
#include <vector>
#include <filesystem>
#include <fstream>
#include <cmath>

#include <json/json.h>

#include "../Network.h"
#include "../Algorithm.h" 

uint32_t runGcdModule(const Json::Value &config);

uint32_t initData(const Json::Value config, int countIterations, int countData, std::vector<std::pair<double, double>> *inputData, std::vector<double> *outputData);

uint32_t readGcdDataFile(std::string filename, std::vector<std::pair<double, double>> *inputData, std::vector<double> *outputData);

uint32_t createGcdData(int countIterations, int countData, int numLimit, std::string filename);

void createGcdData(int countIterations, int countData, int numLimit, std::vector<std::pair<double, double>> *inputData, std::vector<double> *outputData);

#endif // !GCDMODULE_H