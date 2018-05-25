#include <iostream>
#include "Student.h"

namespace dbmanager {

	std::string Student::modelName = "Students";
	std::shared_ptr<Connection> Student::connection_ = nullptr;

	Column Student::id_;
	Column Student::firstName_;
	Column Student::surName_;
	Column Student::middleName_;

	void Student::setup(const std::shared_ptr<Connection>& connection)
	{
		connection->Connect(modelName);
		connection_ = connection;
	}

	void Student::InitColumn()
	{
		id_.SetType(DBType::Int32);
		id_.SetColumnName("StudentID");
		id_.SetLength(10);

		firstName_.SetType(DBType::String);
		firstName_.SetColumnName("Firstname");
		firstName_.SetLength(16);

		surName_.SetType(DBType::String);
		surName_.SetColumnName("Surname");
		surName_.SetLength(16);

		middleName_.SetType(DBType::String);
		middleName_.SetColumnName("Middlename");
		middleName_.SetLength(16);
	}

	bool Student::Delete()
	{
		return false;
	}

	std::string Student::GetModelName()
	{
		return modelName;
	}

	bool Student::IsColumnNameValid(const std::string & columnName)
	{
		return columnName == id_.GetColumnName() || columnName == firstName_.GetColumnName()
			|| columnName == surName_.GetColumnName() || columnName == middleName_.GetColumnName();
	}

	void Student::Save()
	{
		Model::Save(connection_);
	}

	void Student::SetId(int id) {
		idValue_ = id;
		values[id_.GetColumnName()] = false;

		std::string colName = id_.GetColumnName();
		void* voidVal = toVoidPtr(id);

		SetValidation(colName);

		newRow_->insert({ colName, voidVal});
	}

	void Student::SetFirstName(const std::string& firstName) {
		firstNameValue_ = firstName;
		values[firstName_.GetColumnName()] = false;
		
		std::string colName = firstName_.GetColumnName();
		void* voidVal = toVoidPtr(firstName);

		SetValidation(colName);

		newRow_->insert({colName, voidVal});
	}

	void Student::SetSurName(const std::string& surName) {
		surNameValue_ = surName;
		values[surName_.GetColumnName()] = false;
		
		std::string colName = surName_.GetColumnName();
		void* voidVal = new std::string(surName);

		SetValidation(colName);

		newRow_->insert({ colName, voidVal });
	}
	void Student::SetMiddleName(const std::string& middleName) {
		middleNameValue_ = middleName;
		values[middleName_.GetColumnName()] = false;
		
		std::string colName = middleName_.GetColumnName();
		void* voidVal = new std::string(middleName);

		SetValidation(colName);
		newRow_->insert({ colName, voidVal });
	}

	Student Student::RowToStudent(std::shared_ptr<Row> & row)
	{
		Student student;
		student.isFirstTimeCreated_ = false;
		int id = *static_cast<int*>(row->at(id_.GetColumnName()));
		student.SetId(id);
		
		std::string fName = *static_cast<std::string*>(row->at(firstName_.GetColumnName()));
		student.SetFirstName(fName);
		
		std::string sName = *static_cast<std::string*>(row->at(surName_.GetColumnName()));
		student.SetSurName(sName);

		std::string mName = *static_cast<std::string*>(row->at(middleName_.GetColumnName()));
		student.SetMiddleName(mName);
		
		student.ownRow_ = row;

		return student;
	}

};