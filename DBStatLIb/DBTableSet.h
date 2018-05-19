#pragma once
#include <memory>
#include <string>
#include <map>
#include "DBTable.h"
#include "Parsers/Parser.h"

namespace dbmanager {
	using namespace std;

	class DBTableSet {
	private:
		string dbSetName_;
		map<std::string, std::shared_ptr<DBTable>> db_;
		std::unique_ptr<Parser> tableNameParser_;
		std::unique_ptr<Parser> pathParser_;
	public:
		DBTableSet(std::unique_ptr<Parser> tableNameParser, std::unique_ptr<Parser> pathParser) :
			tableNameParser_(std::move(tableNameParser)),
			pathParser_(std::move(pathParser)) { }

		DBTableSet(std::string name) : dbSetName_(name) {}

		void ReadDB(const std::string& fileName);
		void SetDBName(std::string name);
		int ReadDBTables();
		void PrintDB(int numcol);
		void WriteDB();
		std::string GetDBName() { return dbSetName_; }
		shared_ptr<DBTable>& operator[](std::string tableName);
	};
}