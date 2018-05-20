#pragma once
#include <memory>
#include <string>
#include <map>
#include "DBTable.h"
#include "Parser.h"
#include "ObjectFactory.h"

namespace dbmanager {
	using namespace std;

	class DBTableSet {
	private:
		static const std::string setFileName;
		string dbSetName_;
		map<std::string, std::shared_ptr<DBTable>> db_;
		std::unique_ptr<Parser> tableNameParser_;
		std::unique_ptr<Parser> pathParser_;
		std::shared_ptr<TableFactory> factory_;
	public:
		DBTableSet(
			std::unique_ptr<Parser> tableNameParser,
			std::unique_ptr<Parser> pathParser,
			const std::shared_ptr<TableFactory>& factory,
			const std::string& dbSetName) :
			tableNameParser_(std::move(tableNameParser)),
			pathParser_(std::move(pathParser)),
			factory_(factory),
			dbSetName_(dbSetName){}

		DBTableSet(std::string name) : dbSetName_(name) {}
		void ReadDB(const std::string& pathTo);
		void SetDBName(std::string name);
		int ReadDBTables();
		void PrintDB(int numcol);
		void WriteDB();
		std::string GetDBName() { return dbSetName_; }
		shared_ptr<DBTable>& operator[](std::string tableName);
	};
}