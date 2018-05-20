#pragma once
#include <string>
#include "Model.h"
#include "Column.h"

// Возможно сделать Header статическим
namespace dbmanager {
	class Student : public Model
	{
	public:
		// Имя модели совпадает с именем таблицы
		static std::string modelName;

		Student() {
			ownRow_ = std::make_shared<Row>();
			newRow_ = std::make_shared<Row>();

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
		~Student() {}

		static void setup(const std::shared_ptr<Connection>& connection) {
			connection->Connect(modelName);
			connection_ = connection;
		}

		Header GetHeader() override;
		void Save() override;
		bool Delete() override;
		std::string GetModelName() override;

		void SetId(int);
		void SetFirstName(const std::string&);
		void SetSurName(const std::string&);
		void SetMiddleName(const std::string&);

		bool IsValidModel();
	private:
		Column<int> id_;
		Column<std::string> firstName_;
		Column<std::string> surName_;
		Column<std::string> middleName_;

		static std::shared_ptr<Connection> connection_;
	};

}