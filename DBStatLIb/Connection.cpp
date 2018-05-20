#include "Connection.h"
#include "iostream"
#include "Column.h"

namespace dbmanager {
	void Connection::AddRow(const std::shared_ptr<Row>& newRow, std::shared_ptr<Row>& ownRow)
	{
		ownRow->clear();
		for (const auto& col : *newRow) {
			std::cout << col.first;
			ownRow->insert({col.first, col.second});
		}

		table_->CreateRow();
		table_->AddRow(ownRow, table_->GetSize() - 1);
		table_->WriteDBTable(table_->GetFileName());
	}

	void Connection::UpdateRow(const std::shared_ptr<Row>& newRow, std::shared_ptr<Row>& ownRow)
	{
		ownRow->clear();
		for (const auto& col : *newRow) {
			ownRow->insert({ col.first, col.second });
		}
		table_->WriteDBTable(table_->GetFileName());
	}

	void dbmanager::Connection::Connect(const std::string & modelName) {
		if (modelName == table_->GetTableName()) {
			connectedModel_ = modelName;
			isConnected_ = true;
		}
		else {
			throw "Cannot connect \"" + modelName + "\" and \"" + table_->GetTableName() + "\" ";
		}
	}

}