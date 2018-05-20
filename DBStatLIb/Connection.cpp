#include "Connection.h"
#include "iostream"
#include "Column.h"

namespace dbmanager {
	void Connection::AddRow(const std::shared_ptr<Row>& newRow, std::shared_ptr<Row>& ownRow)
	{
		if (isConnected_) {
			ownRow->clear();
			for (const auto& col : *newRow) {
				DBType tmpType = table_->GetHeader()[col.first].colType;
				void* tmp = GetValue(tmpType);
				memcpy(tmp, col.second, GetByte(tmpType));
				ownRow->insert({ col.first, tmp });
			}

			table_->CreateRow();
			table_->AddRow(ownRow, table_->GetSize() - 1);
			table_->WriteDBTable(table_->GetFileName());
		}
		else {
			std::cout << "There is no connection with DB\n";
		}
	}

	void Connection::UpdateRow(const std::shared_ptr<Row>& newRow, std::shared_ptr<Row>& ownRow)
	{
		if (isConnected_) {
			ownRow->clear();
			for (const auto& col : *newRow) {
				ownRow->insert({ col.first, col.second });
			}
			table_->WriteDBTable(table_->GetFileName());
		}
		else {
			std::cout << "There is no connection with DB\n";
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