#ifndef PARSINGMODULE_H
#define PARSINGMODULE_H

#include <iostream>
#include <string>
#include <vector>

#include <json/json.h>
#include <curl/curl.h>

#include "../Network.h"

uint32_t runParsingModule(const Json::Value &config);

#endif // !PARSINGMODULE_H