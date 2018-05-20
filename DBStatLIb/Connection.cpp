#include "Connection.h"
#include "iostream"
#include "Column.h"

namespace dbmanager {
	void Connection::AddRow(const std::shared_ptr<Row>& newRow, std::shared_ptr<Row>& ownRow)
	{
	
		ownRow->clear();
		for (const auto& col : *newRow) {
			DBType tmpType = table_->GetHeader()[col.first].colType;
			void* tmp = GetValue(tmpType);
			memcpy(tmp, col.second, GetByte(tmpType));
			std::cout << *static_cast<int*>(tmp);
			ownRow->insert({col.first, tmp});
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