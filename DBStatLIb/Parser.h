#pragma once

#include <string>
#include <vector>

// Минимальный интерфейс для парсера.
class Parser {
public:
	virtual ~Parser() = default;
	
	//Возвращает токены(слова) полученые после парсинга
	virtual std::vector<std::string> parse(const std::string& str) = 0;
};