#pragma once
#include "Parser.h"
#include <algorithm>

// По соглашению ( Папшев сказал ), тип таблицы находится в конце названия таблицы
// Пример VladTxt, Vlad - название таблицы, Txt - тип таблицы.

class TableNameParser : public Parser
{
	// Типы таблиц, которые бывают
	std::vector<std::string> tableTypesName_;
public:
	TableNameParser(const std::vector<std::string>& tableTypeName) : tableTypesName_(tableTypeName) { }
	TableNameParser(const TableNameParser&) = delete;
	TableNameParser(TableNameParser&&) = delete;
	TableNameParser&operator=(const TableNameParser&) = delete;
	TableNameParser&operator=(TableNameParser&&) = delete;

	std::vector<std::string> parse(const std::string& str) override;
	~TableNameParser();
};

