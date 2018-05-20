#include "Student.h"
#include <iostream>
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

	Header Student::GetHeader()
	{
		return Header();
	}
	void Student::Save()
	{
		if (IsValidModel()) {
			try {
				if (isFirstTimeCreated_) {
					connection_->AddRow(newRow_, ownRow_);
					isFirstTimeCreated_ = false;
				}
				else {
					connection_->UpdateRow(newRow_, ownRow_);
				}
			}
			catch (const std::string&ex) {
				std::cout << ex << "\n";
			}
		}
		else {
			throw std::string("Some column is empty, cannot save object" + GetModelName());
		}
	}
	bool Student::Delete()
	{
		return false;
	}

	std::string Student::GetModelName()
	{
		return modelName;
	}
	void Student::SetId(int id) {
		idValue_ = id;
		values[id_.GetColumnName()] = false;
		std::string colName = id_.GetColumnName();
		void* voidVal = new int(id);

		if (newRow_->find(colName) != newRow_->end()) {
			delete (newRow_->at(colName));
			newRow_->erase(colName);
		}

		newRow_->insert({ colName, voidVal});
		voidVal = NULL;

		//std::cout << *static_cast<int*>(newRow_->at(id_.GetColumnName()));
	}

	void Student::SetFirstName(const std::string& firstName) {
		firstNameValue_ = firstName;
		values[firstName_.GetColumnName()] = false;
		newRow_->insert({firstName_.GetColumnName(), new std::string(firstNameValue_)});
	}

	void Student::SetSurName(const std::string& surName) {
		surNameValue_ = surName;
		values[surName_.GetColumnName()] = false;
		newRow_->insert({ surName_.GetColumnName(), new std::string(surNameValue_) });
	}
	void Student::SetMiddleName(const std::string& middleName) {
		middleNameValue_ = middleName;
		values[middleName_.GetColumnName()] = false;
		newRow_->insert({ middleName_.GetColumnName(), new std::string(middleNameValue_) });
	}

	vector<Student> Student::getById(int id)
	{
		auto vectorOfRows = connection_->Select(id_.GetColumnName(), id);
		vector<Student> students;

		for (auto& row : vectorOfRows) {
			//std::cout << *static_cast<int*>(row->at("StudentID"));
			students.push_back(RowToStudent(row));
		}
		
		return students;
	}

	vector<Student> Student::getByFirstName(std::string firstName)
	{
		return vector<Student>();
	}

	bool Student::IsValidModel()
	{
		for (auto& f : values) {
			if (f.second == true)
				return false;
		}

		return true;
	}

	Student Student::RowToStudent(std::shared_ptr<Row> & row)
	{
		Student student;
		student.isFirstTimeCreated_ = false;
		int id = *static_cast<int*>(row->at(id_.GetColumnName()));
		student.SetId(id);
		/*
		std::string fName = *static_cast<std::string*>(row[firstName_.GetColumnName()]);
		student.SetFirstName(fName);
		
		std::string sName = *static_cast<std::string*>(row[surName_.GetColumnName()]);
		student.SetSurName(sName);

		std::string mName = *static_cast<std::string*>(row[middleName_.GetColumnName()]);
		student.SetMiddleName(mName);
		*/
		student.ownRow_ = row;

		return student;
	}

};