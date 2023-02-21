#ifndef TEMPLATEMODULE_H
#define TEMPLATEMODULE_H

#include <json/json.h>

#include "../Network.h"

uint32_t runTemplateModule(const Json::Value &config);

uint32_t createPersonalData(std::vector<std::array<double, 1>> *inputData, std::vector<std::array<double, 1>> *outputData, int countEpochs, int countIterations);

uint32_t readFile(std::string filename, std::vector<std::array<double, 1>> *data);

#endif // !TEMPLATEMODULE_H