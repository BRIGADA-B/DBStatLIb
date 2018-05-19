#include "TableNameParser.h"
#include <iostream>

std::vector<std::string> TableNameParser::parse(const std::string & str)
{
	std::vector<std::string> res;
	for (const auto& type : tableTypesName_) {
		auto resIterator = std::search(str.rbegin(), str.rend(), type.rbegin(), type.rend());
		if (resIterator != str.rend()) {
			//std::cout << *(resIterator + std::distance(type.begin(), type.end()));
			//resIterator++;
			//std::cout << *(resIterator.base());
			//auto it = resIterator + std::distance(type.begin(), type.end());

			auto reverseBorder = resIterator + std::distance(type.begin(), type.end());
			res.emplace_back(reverseBorder.base(), resIterator.base());
			res.emplace_back(str.begin(), reverseBorder.base());

			return res;
		}
	}

	throw "Table name " + str + " has no type";

	return res;
}

TableNameParser::~TableNameParser()
{
}
