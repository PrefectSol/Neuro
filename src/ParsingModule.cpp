#include "Modules/ParsingModule.h"

uint32_t getWikiArticle(std::string searchText, std::string *article) {
    std::string url = "https://en.wikipedia.org/w/api.php?action=query&format=json&prop=extracts&exintro=&explaintext=&titles=" + searchText;

    CURL *curl = curl_easy_init();
    if(curl) 
    {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

        std::string response;
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

        CURLcode result = curl_easy_perform(curl);

        if(result == CURLE_OK) 
        {
            rapidjson::Document document;
            document.Parse(response.c_str());

            const rapidjson::Value& pages = document["query"]["pages"];
            for (rapidjson::Value::ConstMemberIterator itr = pages.MemberBegin(); itr != pages.MemberEnd(); ++itr) 
            {
                if (itr->value["extract"].IsString()) 
                {
                    *article = itr->value["extract"].GetString();

                    return ErrorCode::success;
                }
            }
        }

        curl_easy_cleanup(curl);
    }

    return ErrorCode::cannotFindWikiArticle;
}

uint32_t parseWiki(std::string searchText, std::string *response)
{
    std::string article;
    uint32_t isParseArticleCode = getWikiArticle(searchText, &article);
    if (isParseArticleCode != ErrorCode::success)
    {
        return isParseArticleCode;
    }

    *response = article;

    return ErrorCode::success;
}

uint32_t runParsingModule(const Json::Value &config)
{
    std::string searchText = config["Creation modules"]["Parsing"]["search text"].asString();

    std::string response;
    uint32_t isParseWikiCode = parseWiki(searchText, &response);
    if (isParseWikiCode == ErrorCode::success)
    {
        std::cout << response << std::endl;
    }

    return ErrorCode::unavailableModule;
}
