#pragma once
#include <string>

namespace dbmanager {

	class Progress
	{
	public:
		Progress() = default;
		~Progress() = default;

		double StudentAvgMark(const std::string& name, const std::string& sname, const std::string& mname);
		int GroupAvgMark(const std::string& groupName);
		int ExamAvgMark(const std::string& examName);

		void AddStudent();

	};

}