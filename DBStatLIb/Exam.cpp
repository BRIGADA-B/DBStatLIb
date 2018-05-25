#include "Exam.h"
#include <stdexcept>
namespace dbmanager {

	const std::string Exam::modelName = "Exams";
	std::shared_ptr<Connection> Exam::connection_ = nullptr;


	Column Exam::groupName_;
	Column Exam::examName_;
	Column Exam::examDate_;

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
	void Exam::SetGroupName(const std::string & groupName)
	{
		groupNameValue_ = groupName;
		values[groupName_.GetColumnName()] = false;

		std::string colName = groupName_.GetColumnName();
		void* voidVal = toVoidPtr(groupName);

		SetValidation(colName);

		newRow_->insert({ colName, voidVal });
	}
	void Exam::SetExamName(const std::string & examName)
	{
		examNameValue_ = examName;
		values[examName_.GetColumnName()] = false;

		std::string colName = examName_.GetColumnName();
		void* voidVal = toVoidPtr(examName);

		SetValidation(colName);

		newRow_->insert({ colName, voidVal });
	}
	void Exam::SetExamDate(const DBDate & date)
	{
		examDateValue_ = date;
		values[examDate_.GetColumnName()] = false;

		std::string colName = examDate_.GetColumnName();
		void* voidVal = toVoidPtr(date);

		SetValidation(colName);

		newRow_->insert({ colName, voidVal });
	}
	void Exam::setup(const std::shared_ptr<Connection>& connection)
	{
		connection->Connect(modelName);
		connection_ = connection;
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
	Exam Exam::RowToExam(std::shared_ptr<Row>& row)
	{
		Exam exam;

		try {
			exam.isFirstTimeCreated_ = false;
			std::string groupName = *static_cast<std::string*>(row->at(groupName_.GetColumnName()));
			exam.SetGroupName(groupName);

			std::string examName = *static_cast<std::string*>(row->at(examName_.GetColumnName()));
			exam.SetExamName(examName);

			DBDate examDate = *static_cast<DBDate*>(row->at(examDate_.GetColumnName()));
			exam.SetExamDate(examDate);
		}
		catch (const std::out_of_range& oor) {
			std::cerr << "Out of range error Exam::RowToExam " << oor.what() << "\n" ;
		}

		exam.ownRow_ = row;

		return exam;
	}
	bool Exam::IsColumnNameValid(const std::string & columnName)
	{
		return columnName == groupName_.GetColumnName() || columnName == examName_.GetColumnName()
			|| columnName == examDate_.GetColumnName();
	}
}