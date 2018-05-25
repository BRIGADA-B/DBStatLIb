#pragma once
#include "Parser.h"
#include <algorithm>

// �� ���������� ( ������ ������ ), ��� ������� ��������� � ����� �������� �������
// ������ VladTxt, Vlad - �������� �������, Txt - ��� �������.

class TableNameParser : public Parser
{
	// ���� ������, ������� ������
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

