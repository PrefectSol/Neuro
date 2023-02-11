#include "Modules/ParsingModule.h"

size_t write_to_string(void *ptr, size_t size, size_t count, void *stream) {
    ((std::string*)stream)->append((char*)ptr, 0, size * count);

    return size * count;
}

int ParsingModule::parse(int argc, char **argv)
{
    
//     std::string html;
//     size_t found;
//     CURL* curl = curl_easy_init();
//     if (curl)
//     {
//         string response;
//         curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_to_string);
//         curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

//         curl_easy_setopt(curl, CURLOPT_URL, "https://www.google.com/search?q=население+земли");
//         curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION,write_to_string);

//         CURLcode res = curl_easy_perform(curl);
//         curl_easy_cleanup(curl);

//        html = response;
//     }

//     HTML::ParserDom parser;
//     tree<HTML::Node> dom = parser.parseTree(html);
    
//     tree<HTML::Node>::iterator it = dom.begin();
//     tree<HTML::Node>::iterator end = dom.end();
//     for (; it != end; ++it)
//     {
//         if (it->tagName() == "A")
//         {
//             it->parseAttributes();
//         }
//     }
    
//     it = dom.begin();
//     end = dom.end();
//     for (; it != end; ++it)
//     {
//         if ((!it->isTag()) && (!it->isComment()))
//         {
//             it->tagName("h3");

//             cout << it->text();
//         }
//     }

    return 1;
}