#pragma once

#include "Model.h"
#include "DBDate.h"
#include "Column.h"

namespace dbmanager {
	class Exam : public Model
	{
	public:
		static const std::string modelName;
		Exam() {
			values[groupName_.GetColumnName()] = true;
			values[examName_.GetColumnName()] = true;
			values[examDate_.GetColumnName()] = true;
		}
		~Exam() = default;

		// Унаследовано через Model
		virtual void Save() override;
		virtual bool Delete() override;
		virtual std::string GetModelName() override;

		void SetGroupName(const std::string&);
		void SetExamName(const std::string&);
		void SetExamDate(const DBDate&);

		static void setup(const std::shared_ptr<Connection>& connection);
		static void initColumn();

		template<class T>
		static vector<Exam> GetBy(const T& value, const std::string& columnName);

	private:
		std::string groupNameValue_;
		std::string examNameValue_;
		DBDate examDateValue_;

		static Column groupName_;
		static Column examName_;
		static Column examDate_;

		static std::shared_ptr<Connection> connection_;

		static Exam RowToExam(std::shared_ptr<Row>&);
		static bool IsColumnNameValid(const std::string& columnName);
	};

	template<class T>
	inline vector<Exam> Exam::GetBy(const T & value, const std::string & columnName)
	{
		// Check if columnName true;
		if (!IsColumnNameValid(columnName)) {
			throw std::string("Exam: There is no such column " + columnName);
		}
		auto vectorOfRows = connection_->Select(columnName, value);
		vector<Exam> exams;
		for (auto& row : vectorOfRows) {
			exams.push_back(RowToExam(row));
		}
		return exams;
	}

};