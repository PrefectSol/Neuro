#ifndef PARSINGMODULE_H
#define PARSINGMODULE_H

#include <iostream>

#include <curl/curl.h>
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>

#include "../Network.h"

uint32_t getWikiArticle(std::string searchText, std::string *article);

uint32_t parseWiki(std::string searchText, std::string *response);

uint32_t runParsingModule(const Json::Value &config);

#endif // !PARSINGMODULE_H