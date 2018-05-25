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
		std::vector<std::shared_ptr<Row>> Select(const std::string columnName, const T& value);
		void Connect(const std::string& modelName);
		virtual ~Connection() = default;

	private:
		std::shared_ptr<DBTable> table_;
		std::string connectedModel_;
		bool isConnected_;
	};

	template<class T>
	inline std::vector<std::shared_ptr<Row>> Connection::Select(const std::string columnName, const T & value)
	{
		if (isConnected_) {
			void * voidValue = new T(value);

			// For now we can select only if equal
			auto rows = table_->Select(columnName, Condition::Equal, voidValue);

			delete voidValue;
			return rows;
		}
		else {
			std::cout << "There is no connection with DB\n";
		}
	}

}