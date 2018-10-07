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
			values[id_.GetColumnName()] = true;
			values[firstName_.GetColumnName()] = true;
			values[surName_.GetColumnName()] = true;
			values[middleName_.GetColumnName()] = true;
		}

		~Student() {}
		static void setup(const std::shared_ptr<Connection>& connection);
		static void InitColumn();


		// Унаследовано через Model
		virtual void Save() override;
		bool Delete() override;
		std::string GetModelName() override;

		void SetId(int);
		void SetFirstName(const std::string&);
		void SetSurName(const std::string&);
		void SetMiddleName(const std::string&);
		
		int GetId() const;
		std::string GetFirstName() const;
		std::string GetSurName() const;
		std::string GetMiddleName() const;

		template<class T>
		static vector<Student> GetBy(const T& value, const std::string& columnName);

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

		static bool IsColumnNameValid(const std::string& columnName);
	};


	// TODO : full template function, for all models
	template<class T>
	inline vector<Student> Student::GetBy(const T & value, const std::string& columnName)
	{
		// Check if columnName true;
		if (!IsColumnNameValid(columnName)) {
			throw std::string("There is no such column " + columnName);
		}
		auto vectorOfRows = connection_->Select(columnName, value);
		vector<Student> students;
		for (auto& row : vectorOfRows) {
			students.push_back(RowToStudent(row));
		}
		return students;
	}


}