#pragma once
#include "Model.h"
#include "Column.h"
#include "Connection.h"

namespace dbmanager {
	class Group : public Model
	{
	public:

		// »м€ модели совпадает с именем таблицы
		static const std::string modelName;

		Group() {

			values[studentId_.GetColumnName()] = true;
			values[groupName_.GetColumnName()] = true;
		}

		~Group() = default;

		// ”наследовано через Model
		virtual bool Delete() override;
		virtual std::string GetModelName() override;
		virtual void Save() override;

		static void setup(const std::shared_ptr<Connection>& connection);
		static void InitColumn();

		void SetStudentId(int);
		void SetGroupName(const std::string&);


		template<class T>
		static vector<Group> GetBy(const T& value, const std::string& columnName);

	private:
		int studentIdValue_;
		std::string groupNameValue_;

		static Column studentId_;
		static Column groupName_;
				
		static std::shared_ptr<Connection> connection_;

		static Group RowToGroup(std::shared_ptr<Row>&);
		static bool IsColumnNameValid(const std::string& columnName);
	};

	template<class T>
	inline vector<Group> Group::GetBy(const T & value, const std::string & columnName)
	{
		// Check if columnName true;
		if (!IsColumnNameValid(columnName)) {
			throw std::string("There is no such column " + columnName);
		}
		auto vectorOfRows = connection_->Select(columnName, value);
		vector<Group> groups;
		for (auto& row : vectorOfRows) {
			groups.push_back(RowToGroup(row));
		}
		return groups;
	}

};