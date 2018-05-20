#include "Connection.h"
#include "iostream"

namespace dbmanager {
	void Connection::AddRow(const std::shared_ptr<Row>& newRow, std::shared_ptr<Row>& ownRow)
	{
		ownRow->clear();
		for (const auto& col : *newRow) {
			std::cout << col.first;
			ownRow->insert({col.first, col.second});
		}

		table_->CreateRow();
		table_->AddRow(*ownRow, table_->GetSize() - 1);
	}

	void Connection::UpdateRow(const std::shared_ptr<Row>& newRow, std::shared_ptr<Row>& ownRow)
	{
		ownRow->clear();
		for (const auto& col : *newRow) {
			ownRow->insert({ col.first, col.second });
		}
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