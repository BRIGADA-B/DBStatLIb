#pragma once

#include "DBTable.h"
#include <vector>

namespace dbmanager {

	class DBTableTxt : public DBTable
	{
	public:

		DBTableTxt() : DBTable() {}
		DBTableTxt(string tabName) : DBTable(tabName) {}

		~DBTableTxt();

		// Унаследовано через DBTable
		virtual void ReadDBTable(const string&) override;
		virtual void WriteDBTable(const string&) override;
		virtual void PrintDBTable(const int) override;
		virtual void DeleteRow(size_t index) override;
		virtual void CreateRow() override;
		virtual void AddRow(const std::shared_ptr<Row>& row, int index) override;
		virtual int GetSize() const override;
		virtual Row GetRow(size_t index) override;
		virtual Row operator[](size_t index) override;
		virtual shared_ptr<DBTable> Select(std::string columnName, Condition cond, void * value) override;
		virtual void Clear() override;
		string TypeName(DBType type);
		DBType TypeByName(string name);
		void* readAnyType(string val, DBType type);
		vector<int> IndexOfRecord(void* keyValue, string keyColumnName);
		string ValueToString(void* value, string columnName);

		DBType GetType(const char* columnName);
		Row operator[](int ind);

		void CreateMaket(map <int, int> &strip, int screenWidth);

		void WriteTableBin(string fileName);
		void ReadTableBin(string fileName);

	private:
		vector<std::shared_ptr<Row>> data_;
	};

}