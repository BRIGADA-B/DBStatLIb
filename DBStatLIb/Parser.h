#pragma once

#include <string>
#include <vector>

// ����������� ��������� ��� �������.
class Parser {
public:
	virtual ~Parser() = default;
	
	//���������� ������(�����) ��������� ����� ��������
	virtual std::vector<std::string> parse(const std::string& str) = 0;
};