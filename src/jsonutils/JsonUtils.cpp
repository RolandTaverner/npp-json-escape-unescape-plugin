#include "JsonUtils.h"

#include <fstream>
#include "json/json.h"

const std::string JsonUtils::emptyString = std::string();

std::string JsonUtils::escapeJson(const std::string& str) const
{
	if (str.empty()) {
		return emptyString;
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
		return emptyString;
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
		return emptyString; // TODO: return errors too
	}

	if (!value.isString()) {
		return emptyString;
	}

	return value.asString();
}

std::string JsonUtils::recursiveUnescapeJson(const std::string& str) const
{
	if (str.size() < 2) {
		return emptyString;
	}

	Json::Value value;
	bool unescapeDone = false;
	// Try parse as is
	value = parse(str, true);
	if (value.isNull()) {
		// Try unescape and parse
		const std::string unescapedStr = unescapeJson(str);
		value = parse(unescapedStr, false);
		if (value.isString()) {
			return unescapedStr;
		}
		unescapeDone = true;
	}

	const auto unescaped = doRecursiveUnescape(value);
	if (unescaped.first.isNull()) {
		return emptyString;
	}
	if (!unescaped.second && !unescapeDone) {
		return emptyString;
	}

	Json::StreamWriterBuilder writerBuilder;
	writerBuilder["emitUTF8"] = true;
	writerBuilder["indentation"] = ""; // If you want whitespace-less output

	return Json::writeString(writerBuilder, unescaped.first);
}

std::pair<Json::Value, bool> JsonUtils::doRecursiveUnescape(const Json::Value& value) const
{
	if (value.isObject() || value.isArray()) {
		Json::Value valueCopy{value};
		bool updated = false;
		for (Json::Value::iterator it = valueCopy.begin(); it != valueCopy.end(); ++it) {
			if (canSkip(*it)) {
				continue;
			}
			const auto unescaped = doRecursiveUnescape(*it);
			if (unescaped.second) {
				*it = unescaped.first;
				updated = true;
			}
		}
		return std::make_pair<>(valueCopy, updated);
	}
	else if (value.isString()) {
		Json::Value parsedValue = parse(value.asString(), true);
		if (parsedValue.isNull()) {
			return std::make_pair<>(value, false);
		}
		return std::make_pair<>(doRecursiveUnescape(parsedValue).first, true);
	}

	return std::make_pair<>(value, false);
}

bool JsonUtils::canSkip(Json::Value& value) const {
	return !(value.isArray() || value.isObject() || value.isString());
}

Json::Value JsonUtils::parse(const std::string& str, bool strictRoot) const {
	Json::CharReaderBuilder builder;
	builder["collectComments"] = false;
	builder["strictRoot"] = strictRoot;
	builder["failIfExtra"] = true;
	std::unique_ptr<Json::CharReader> reader(builder.newCharReader());

	Json::Value value;
	Json::String errs;
	if (!reader->parse(str.c_str(), str.c_str() + str.size(), &value, &errs)) {
		return Json::Value::nullSingleton(); // TODO: return errors too
	}
	return value;
}
