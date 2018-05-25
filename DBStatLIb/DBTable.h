#pragma once
#include <memory>
#include "utils.h"
#include <vector>
using namespace std;

namespace dbmanager {
	class DBTable {
	public:
		// Так делать не надо, но это лучше чем везде таскать за собой формат таблицы.
		// В данном случае формат таблицы, это расширение файлов.
		static const string dbFormat;
		static std::vector<std::string> tableTypesName;

		DBTable() { }
		DBTable(string tabName) : tabName_(tabName) { }
		DBTable(string tabname, string pathto, string primaryKey) : 
			pathToTab_(pathto), tabName_(tabname),  primaryKey_(primaryKey){ }

		virtual ~DBTable() = default;

		virtual void ReadDBTable(const string&) = 0;
		virtual void WriteDBTable(const string&) = 0;
		virtual void PrintDBTable(const int) = 0;
		virtual void DeleteRow(size_t index) = 0;
		virtual void CreateRow() = 0;
		virtual void AddRow(const std::shared_ptr<Row>& row, int index) = 0;
		virtual std::shared_ptr<Row> GetRow(size_t index) = 0;
		virtual Header GetHeader();
		virtual void SetHeader(Header& header);
		virtual Row& operator[](size_t index) = 0;
		virtual vector<std::shared_ptr<Row>> Select(std::string columnName, Condition cond, void* value) = 0;
		virtual void Clear() = 0;
		virtual string GetFileName();
		virtual string GetTableName();
		virtual string GetPrimaryKey();

		virtual void SetFileName(const string& fileName);
		virtual void SetTableName(string tName);
		virtual void SetPrimaryKey(string key);

		virtual int GetSize() const = 0;
	protected:
		Header header_;
		string tabName_;
		string pathToTab_;
		string primaryKey_;
	};
}