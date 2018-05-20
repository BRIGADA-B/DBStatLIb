#pragma once

#include "DBTable.h"

namespace dbmanager {
	class Connection
	{
	public:
		Connection(const std::shared_ptr<DBTable>& table) : table_(table), isConnected_(false) {}

		void AddRow(const std::shared_ptr<Row>&, std::shared_ptr<Row>&);
		void UpdateRow(const std::shared_ptr<Row>&, std::shared_ptr<Row>&);
		template<class T>
		std::vector<Row> Select(const std::string columnName, const T& value);
		void Connect(const std::string& modelName);
		virtual ~Connection() = default;

	private:
		std::shared_ptr<DBTable> table_;
		std::string connectedModel_;
		bool isConnected_;
	};

	template<class T>
	inline std::vector<Row> Connection::Select(const std::string columnName, const T & value)
	{

		void * voidValue = new T(value);

		// For now we can select only if equal
		std::shared_ptr<DBTable> tmpTable = table_->Select(columnName, Condition::Equal, voidValue);
		std::vector<Row> rows;
		for (decltype (tmpTable->GetSize()) i = 0; i < tmpTable->GetSize(); i++) {
			rows.push_back(tmpTable->GetRow(i));
		}

		return rows;
	}

}