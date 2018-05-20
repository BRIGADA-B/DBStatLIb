#include "Exam.h"

namespace dbmanager {

	const std::string Exam::modelName = "Exams";
	std::shared_ptr<Connection> Exam::connection_ = nullptr;

	void Exam::Save()
	{
		Model::Save(connection_);
	}
	bool Exam::Delete()
	{
		return false;
	}
	std::string Exam::GetModelName()
	{
		return modelName;
	}
	void Exam::SetGroupName(const std::string &)
	{

	}
	void Exam::SetExamName(const std::string &)
	{
	}
	void Exam::SetExamDate(const DBDate &)
	{
	}
	void Exam::setup(const std::shared_ptr<Connection>& connection)
	{

	}
	void Exam::initColumn()
	{
		groupName_.SetType(DBType::String);
		groupName_.SetColumnName("Group");
		groupName_.SetLength(20);

		examName_.SetType(DBType::String);
		examName_.SetColumnName("Examination");
		examName_.SetLength(20);

		examDate_.SetType(DBType::Date);
		examDate_.SetColumnName("Date");
		examDate_.SetLength(20);
		
	}
	Exam Exam::RowToExam(std::shared_ptr<Row>&)
	{
		
	}
	bool Exam::IsColumnNameValid(const std::string & columnName)
	{
		return columnName == groupName_.GetColumnName() || columnName == examName_.GetColumnName()
			|| columnName == examDate_.GetColumnName();
	}
}