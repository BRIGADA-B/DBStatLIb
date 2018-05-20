#include "DBTableSet.h"
#include <iostream>
#include <fstream>
#include "ObjectFactory.h"

namespace dbmanager {
	const std::string DBTableSet::setFileName = "set.txt";
	
	void DBTableSet::WriteDB() {
		for (const auto& dbTable : db_) {
			dbTable.second->WriteDBTable(dbTable.second->GetFileName());
			cout << "Table: " << dbTable.first << " was successfully written" << endl;
		}
	}

	void DBTableSet::ReadDB(const string & pathToDB)
	{

		std::string dbType;
		try {
			auto pathTokens = pathParser_->parse(pathToDB);
			auto nameTokens = tableNameParser_->parse(pathTokens[pathTokens.size() - 1]);

			// nameTokens[0] is contaain DbType
			dbType = nameTokens[0];
		}
		catch (const std::string &ex) {
			throw ex;
		}

		std::string fileName = pathToDB + setFileName;
		ifstream is(fileName.c_str(), ios_base::in);
		if (!is.is_open()) {
			throw std::string( "Cannot read " + fileName);
		}
		
		string dbName;
		getline(is, dbName);
		SetDBName(dbName);

		string dbTable;
		for (int i = 0; getline(is, dbTable); i++) {
			try {

				std::shared_ptr<DBTable> table(factory_->create(dbType));

				std::string tableFileName;
				tableFileName += pathToDB;
				tableFileName += dbTable;
				tableFileName += ".";
				tableFileName += DBTable::dbFormat;

				table->SetFileName(tableFileName);
				table->SetTableName(dbTable);

				db_[dbTable] = table;
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
			try
			{
				dbTable.second->ReadDBTable(dbTable.second->GetFileName());
			}
			catch (const std::string& ex)
			{
				std::cout << ex;
			}
		}
		return 0;
	}

	void DBTableSet::PrintDB(int numcol) {
		for (const auto& dbTable : db_) {
			if (dbTable.second)
 				dbTable.second->PrintDBTable(numcol);
			cout << "\n\n";
		}
	}

	shared_ptr<DBTable>& DBTableSet::operator[](string tableName) {
		return db_[tableName];
	}

	void DBTableSet::ClearAll() {
		for (auto& dbTable : db_) {
			dbTable.second->Clear();
		}
	}
}