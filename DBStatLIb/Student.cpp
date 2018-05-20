#include "Student.h"
#include <iostream>
namespace dbmanager {

	std::string Student::modelName = "Students";
	std::shared_ptr<Connection> Student::connection_ = nullptr;

	Header Student::GetHeader()
	{
		return Header();
	}
	void Student::Save()
	{
		if (IsValidModel()) {
			try {
				if (isFirstTimeCreated_)
					connection_->AddRow(newRow_, ownRow_);
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
		id_.SetValue(id);
		newRow_->insert({id_.GetColumnName(), (void*)id_});
	}

	void Student::SetFirstName(const std::string& firstName) {
		firstName_.SetValue(firstName);
		newRow_->insert({ firstName_.GetColumnName(), (void*)firstName_ });
	}

	void Student::SetSurName(const std::string& surName) {
		surName_.SetValue(surName);
		newRow_->insert({ surName_.GetColumnName(), (void*)surName_ });
	}
	void Student::SetMiddleName(const std::string& middleName) {
		middleName_.SetValue(middleName);
		newRow_->insert({ middleName_.GetColumnName(), (void*)middleName_ });
	}

	bool Student::IsValidModel()
	{
		return !id_.IsValueEmpty() && !firstName_.IsValueEmpty()
			&& !surName_.IsValueEmpty() && !middleName_.IsValueEmpty();
	}

};