#include "JsonUtils.h"

#include "json/json.h"

std::string JsonUtils::escapeJson(const std::string &str) const
{
    if (str.empty()) {
        return str;
    }

    const Json::Value value(str);

    Json::StreamWriterBuilder builder;
    builder["emitUTF8"] = true;
    builder["indentation"] = ""; // If you want whitespace-less output

    return Json::writeString(builder, value);
}

std::string JsonUtils::unescapeJson(const std::string& str) const
{
    if (str.size() < 2) {
        return str;
    }

    const bool hasQuotes = str.front() == '\"' && str.back() == '\"';

    const std::string quotedStr = hasQuotes ? str : ("\"" + str + "\"");

    Json::CharReaderBuilder builder;
    builder["collectComments"] = false;
    builder["strictRoot"] = false;
    builder["failIfExtra"] = true;

    std::unique_ptr<Json::CharReader> reader(builder.newCharReader());
    
    Json::Value value;
    Json::String errs;
    if (!reader->parse(quotedStr.c_str(), quotedStr.c_str() + quotedStr.size(), &value, &errs)) {
        return std::string(); // TODO: return errors too
    }

    if (!value.isString()) {
        return std::string();
    }

    return value.asString();
}
