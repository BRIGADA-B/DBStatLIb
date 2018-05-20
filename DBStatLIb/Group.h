#pragma once
#include "Model.h"
#include "Column.h"
#include "Connection.h"

namespace dbmanager {
	class Group : public Model
	{
	public:

		// »м€ модели совпадает с именем таблицы
		static std::string modelName;

		Group() {
			ownRow_ = std::make_shared<Row>();
			newRow_ = std::make_shared<Row>();

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

	private:
		int studentIdValue_;
		std::string groupNameValue_;

		static Column studentId_;
		static Column groupName_;
				
		static std::shared_ptr<Connection> connection_;

	};

};