#include "PathParser.h"
#include <sstream>
#include <algorithm>

std::vector<std::string> PathParser::parse(const std::string & str)
{

	std::vector<std::string> res;
	res.push_back(str);
	std::stringstream ss(str);
	std::string token;
	while (std::getline(ss, token, del_)) {

		if (!token.empty()) {
			res.push_back(token);
		}
	}

	return res;
}
