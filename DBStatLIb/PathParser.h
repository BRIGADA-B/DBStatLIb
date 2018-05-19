#pragma once
#include "Parser.h"


// Парсит пути до файлов
class PathParser : public Parser
{
public:
	PathParser(const char del) : del_(del) {}

	~PathParser() = default;
	PathParser(const PathParser&) = delete;
	PathParser(PathParser&&) = delete;
	PathParser&operator=(const PathParser&) = delete;
	PathParser&operator=(PathParser&&) = delete;

	// Унаследовано через Parser
	// Первым всегда лежит изначальный путь. Пример
	// @param /url/kek/
	// @return vec {/url/kek/, url, kek}
	virtual std::vector<std::string> parse(const std::string & str) override;

private:
	const char del_;
};

