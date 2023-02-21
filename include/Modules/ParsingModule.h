#ifndef PARSINGMODULE_H
#define PARSINGMODULE_H

#include <json/json.h>
#include <iostream>
#include <string>
#include <vector>
#include <curl/curl.h>

#include "../Network.h"

using namespace std;

uint32_t runParsingModule(const Json::Value &config);

#endif // !PARSINGMODULE_H