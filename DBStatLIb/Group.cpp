#include "Group.h"
#include <iostream>

namespace dbmanager {
	const std::string Group::modelName = "Groups";
	std::shared_ptr<Connection> Group::connection_ = nullptr;

	Column Group::studentId_;
	Column Group::groupName_;

	void Group::setup(const std::shared_ptr<Connection>& connection)
	{
		connection->Connect(modelName);
		connection_ = connection;
	}

	void Group::InitColumn()
	{
		studentId_.SetType(DBType::Int32);
		studentId_.SetColumnName("StudentID");
		studentId_.SetLength(10);

		groupName_.SetType(DBType::String);
		groupName_.SetColumnName("Group");
		groupName_.SetLength(16);

	}

	bool Group::Delete()
	{
		return false;
	}

	std::string Group::GetModelName()
	{
		return modelName;
	}

	void Group::Save()
	{
		Model::Save(connection_);
	}

	void Group::SetStudentId(int id) {
		studentIdValue_ = id;

		std::string colName = studentId_.GetColumnName();
		values[colName] = false;

		void* voidVal = toVoidPtr(id);

		SetValidation(colName);
		newRow_->insert({ colName, voidVal });
	}

	void Group::SetGroupName(const std::string& groupName) {
		groupNameValue_ = groupName;

		std::string colName = groupName_.GetColumnName();
		values[colName] = false;

		void* voidVal = toVoidPtr(groupName);

		SetValidation(colName);
		newRow_->insert({ colName, voidVal });
	}

};
