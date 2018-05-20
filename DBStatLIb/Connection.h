#pragma once

#include "DBTable.h"

namespace dbmanager {
	class Connection
	{
	public:
		Connection(const std::shared_ptr<DBTable>& table) : table_(table), isConnected_(false) {}

		void AddRow(const std::shared_ptr<Row>&, std::shared_ptr<Row>&);
		void UpdateRow(const std::shared_ptr<Row>&, std::shared_ptr<Row>&);

		void Connect(const std::string& modelName);
		virtual ~Connection() = default;

	private:
		std::shared_ptr<DBTable> table_;
		std::string connectedModel_;
		bool isConnected_;
	};

}