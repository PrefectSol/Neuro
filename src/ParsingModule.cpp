#include "Modules/ParsingModule.h"

uint32_t runParsingModule(const Json::Value &config)
{
    const std::string searchText = config["Creation modules"]["Parsing"]["search text"].asString();

    return ErrorCode::success;
}
