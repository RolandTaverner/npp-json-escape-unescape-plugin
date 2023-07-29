#pragma once

#include <string>

class JsonUtils
{
public:
	std::string escapeJson(const std::string& str) const;
	std::string unescapeJson(const std::string& str) const;
	std::string recursiveUnescapeJson(const std::string& str) const;
};

