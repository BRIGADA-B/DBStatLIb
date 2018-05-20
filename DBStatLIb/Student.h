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

			values[id_.GetColumnName()] = true;

			//values[firstName_.GetColumnName()] = true;
			//values[surName_.GetColumnName()] = true;
			//values[middleName_.GetColumnName()] = true;
		}

		~Student() {}
		static void setup(const std::shared_ptr<Connection>& connection);

		static void InitColumn();

		Header GetHeader() override;
		void Save() override;
		bool Delete() override;
		std::string GetModelName() override;

		void SetId(int);
		void SetFirstName(const std::string&);
		void SetSurName(const std::string&);
		void SetMiddleName(const std::string&);

		static vector<Student> getById(int id);
		static vector<Student> getByFirstName(std::string firstName);

		bool IsValidModel();
	private:
		static Column id_;
		static Column firstName_;
		static Column surName_;
		static Column middleName_;

		int idValue_;
		std::string firstNameValue_;
		std::string surNameValue_;
		std::string middleNameValue_;

		static std::shared_ptr<Connection> connection_;

		static Student RowToStudent(std::shared_ptr<Row>&);
	};

}