#pragma once

#include <string>
#include <utility>
#include "json/forwards.h"

class JsonUtils
{
public:
	std::string escapeJson(const std::string& str) const;
	std::string unescapeJson(const std::string& str) const;
	std::string recursiveUnescapeJson(const std::string& str) const;

private:
	static const std::string emptyString;

	std::pair<Json::Value, bool> doRecursiveUnescape(const Json::Value& value) const;
	bool canSkip(Json::Value& value) const;
	Json::Value parse(const std::string& str, bool strictRoot) const;
};

void log(const std::string& str);