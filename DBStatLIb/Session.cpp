#include "Session.h"
#include <iostream>

namespace dbmanager {

	const std::string Session::modelName = "Sessions";

	Column Session::studentId_;
	Column Session::examName_;
	Column Session::examMark_;

	std::shared_ptr<Connection> Session::connection_;

	void Session::setup(const std::shared_ptr<Connection> connection)
	{
		connection->Connect(modelName);
		connection_ = connection;
	}

	void Session::initColumn()
	{
		studentId_.SetColumnName("StudentID");
		studentId_.SetType(DBType::Int32);
		studentId_.SetLength(10);

		examName_.SetColumnName("Examination");
		examName_.SetType(DBType::String);
		examName_.SetLength(20);

		examMark_.SetColumnName("Mark");
		examMark_.SetType(DBType::Int32);
		examMark_.SetLength(10);

	}

	void Session::Save()
	{
		Model::Save(connection_);
	}

	bool Session::Delete()
	{
		return false;
	}

	std::string Session::GetModelName()
	{
		return std::string();
	}
	void Session::SetExamName(const std::string& examName)
	{
		examNameValue_ = examName;
		values[examName_.GetColumnName()] = false;

		std::string colName = examName_.GetColumnName();
		void* voidVal = toVoidPtr(examName);

		SetValidation(colName);

		newRow_->insert({ colName, voidVal });
	}
	void Session::SetStudentId(int id)
	{
		studentIdValue_ = id;

		std::string colName = studentId_.GetColumnName();
		values[colName] = false;

		void* voidVal = toVoidPtr(id);

		SetValidation(colName);
		newRow_->insert({ colName, voidVal });

	}
	void Session::SetExamMark(int mark)
	{
		examMarkValue_ = mark;

		std::string colName = examMark_.GetColumnName();
		values[colName] = false;

		void* voidVal = toVoidPtr(mark);

		SetValidation(colName);
		newRow_->insert({ colName, voidVal });

	}
	std::string Session::GetExamName() const
	{
		return examNameValue_;
	}
	int Session::GetStudentId() const
	{
		return studentIdValue_;
	}
	int Session::GetExamMark() const
	{
		return examMarkValue_;
	}
	Session Session::RowToSession(std::shared_ptr<Row>& row)
	{
		Session session;

		try {
			session.isFirstTimeCreated_ = false;
			
			std::string examName = *static_cast<std::string*>(row->at(examName_.GetColumnName()));
			session.SetExamName(examName);

			int studentId = *static_cast<int*>(row->at(studentId_.GetColumnName()));
			session.SetStudentId(studentId);

			int examMark = *static_cast<int*>(row->at(examMark_.GetColumnName()));
			session.SetExamMark(examMark);

		} catch (const std::out_of_range& oor) {
			std::cerr << "Out of range error Exam::RowToExam " << oor.what() << "\n";
		}

		return session;
	}
	bool Session::IsColumnNameValid(const std::string & columnName)
	{
		return columnName == studentId_.GetColumnName() 
			|| columnName == examName_.GetColumnName() || columnName == examMark_.GetColumnName();
	}
}