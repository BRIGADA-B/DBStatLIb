#include "DBTableSet.h"
#include <iostream>
#include <fstream>

namespace dbmanager {
	
	void DBTableSet::WriteDB() {
		for (const auto& dbTable : db_) {
			dbTable.second->WriteDBTable(dbTable.second->GetFileName());
			cout << "Table: " << dbTable.first << " was successfully written" << endl;
		}
	}

	void DBTableSet::ReadDB(const string & fileName)
	{
		ifstream is(fileName.c_str(), ios_base::in);
		if (!is.is_open()) {
			std::cout << "Cannot read " << fileName << endl;
			return;
		}
		
		string dbName;
		getline(is, dbName);
		SetDBName(dbName);

		string dbTable;
		for (int i = 0; getline(is, dbTable); i++) {
			try {
				// first is Type, second is TableName
				auto nameTokens = tableNameParser_->parse(dbTable);
				const string& name = nameTokens[1];
//				db_[name] = DBTable::createByStringType(tokens[0]);
				auto& refToTab = db_[name];

				auto pathTokens = pathParser_->parse(fileName);

				string tableFileName;
				// Если путь указан, до файла, то последний токен в векторе, это название файла
				// А нам нужен путь до файла
				for (auto i = pathTokens.begin(); i != (pathTokens.begin() + pathTokens.size() - 1); i++) {
					tableFileName += *i;
				}

				tableFileName += OS_DELEMITER + '.';
				tableFileName += DBTable::dbFormat;

				refToTab->SetFileName(tableFileName);
			}
			catch (const std::string& ex) {
				std::cout << ex;
			}
		}

	}

	void DBTableSet::SetDBName(string name) {
		dbSetName_ = name;
	}

	int DBTableSet::ReadDBTables() {

		for (const auto& dbTable : db_) {
			dbTable.second->ReadDBTable(dbTable.second->GetFileName());
			cout << "Table: " << dbTable.first << " was successfully read" << endl;
		}
		return 0;
	}

	void DBTableSet::PrintDB(int numcol) {
		for (const auto& dbTable : db_) {
			dbTable.second->PrintDBTable(numcol);
			cout << "\n\n";
		}
	}

	shared_ptr<DBTable>& DBTableSet::operator[](string tableName) {
		return db_[tableName];
	}
}