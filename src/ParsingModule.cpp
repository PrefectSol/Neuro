#include "Modules/ParsingModule.h"

size_t write_to_string(void *ptr, size_t size, size_t count, void *stream) {
    ((std::string*)stream)->append((char*)ptr, 0, size * count);

    return size * count;
}

uint32_t runParsingModule(const Json::Value &config)
{
    return ErrorCode::unavailableModule;
}

vector<string> parseYandex(string query) {
    vector<string> urls;
    CURL *curl;
    CURLcode res;
    curl = curl_easy_init();
    if (curl) {
        string url = "https://yandex.ru/search/?text=" + query;
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        res = curl_easy_perform(curl);
        if (res == CURLE_OK) {

        }
        curl_easy_cleanup(curl);
    } return urls;
}

int parse() {
    vector<string> urls = parseYandex("prefect");
    cout << "results: " << urls.size() << endl;

    for (int i = 0; i < urls.size(); i++) 
    {
        cout << urls[i] << endl;
    }
    return 0;
} 