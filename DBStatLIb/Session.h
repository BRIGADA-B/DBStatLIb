#pragma once
#include "Model.h"
#include "Column.h"
#include "Connection.h"

namespace dbmanager {
	class Session : public Model
	{
	public:

		static const std::string modelName;
		Session() {
			values[studentId_.GetColumnName()] = true;
			values[examMark_.GetColumnName()] = true;
			values[examName_.GetColumnName()] = true;
		}

		~Session() = default;


		static void setup(const std::shared_ptr<Connection> connection);
		static void initColumn();

		// Унаследовано через Model
		virtual void Save() override;
		virtual bool Delete() override;
		virtual std::string GetModelName() override;

		void SetExamName(const std::string&);
		void SetStudentId(int);
		void SetExamMark(int);

		template<class T>
		static vector<Session> GetBy(const T& value, const std::string& columnName);

	private:
		int studentIdValue_;
		std::string examNameValue_;
		int examMarkValue_;

		static Column studentId_;
		static Column examName_;
		static Column examMark_;

		static std::shared_ptr<Connection> connection_;

		static Session RowToSession(std::shared_ptr<Row>&);
		static bool IsColumnNameValid(const std::string& columnName);
	};

	template<class T>
	inline vector<Session> Session::GetBy(const T & value, const std::string & columnName)
	{
		// Check if columnName true;
		if (!IsColumnNameValid(columnName)) {
			throw std::string("There is no such column " + columnName);
		}
		
		auto vectorOfRows = connection_->Select(columnName, value);
		vector<Session> sessions;
		for (auto& row : vectorOfRows) {
			sessions.push_back(RowToSession(row));
		}
		return sessions;
	}

}