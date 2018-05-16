#pragma once
#include <memory>
#include "utils.h"
using namespace std;

namespace dbmanager {
	class DBTable {
	public:
		DBTable() { }
		DBTable(string tabName) : tabName_(tabName) { }
		DBTable(string tabname, string pathto, string primaryKey) : 
			pathToTab_(pathto), tabName_(tabname),  primaryKey_(primaryKey){ }

		virtual void ReadDBTable(const string&) = 0;
		virtual void WriteDBTable(const string&) = 0;
		virtual void PrintDBTable(const int) = 0;
		virtual void DeleteRow(size_t index) = 0;
		virtual void CreateRow() = 0;
		virtual void AddRow() = 0;
		virtual Row GetRow(size_t index) = 0;
		virtual Header GetHeader();
		virtual void SetHeader(Header& header);
		virtual Row operator[](size_t index) = 0;
		virtual shared_ptr<DBTable> Select(std::string columnName, Condition cond, void* value) = 0;

		virtual string GetFileName();
		virtual void SetFileName(const string& fileName);

	protected:
		Header header_;
		string tabName_;
		string pathToTab_;
		string primaryKey_;
	};
}