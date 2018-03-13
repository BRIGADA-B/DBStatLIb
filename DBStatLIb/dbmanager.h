#pragma once
#ifndef _DB_MANAGER_H_
#define _DB_MANAGER_H_

#include<string>
#include<iostream>
#include<map>
#include<vector>

using namespace std;

namespace dbmanager {
	class DBDate
	{

		static const int arrDays_[13];
		friend string DateToStr(DBDate& date);
		friend ostream& operator<<(ostream& out, DBDate& date);
		int day_, month_, year_;
	public:
		DBDate(string date);
		DBDate(int d, int m, int y);
		DBDate() :day_(0), month_(0), year_(0) {};
		DBDate(DBDate& dat) :day_(dat.day_), month_(dat.month_), year_(dat.year_) {}
		int GetDay();
		int GetMonth();
		int GetYear();
		bool IsLeapYear(int year); 
		int GetDaysInMonth(int month, int year);
		int DaysInCurYear();
		bool operator==(DBDate& date);
		bool operator<(DBDate& date);
		bool operator>(DBDate& date);
		bool operator<= (DBDate& date);
		bool operator>= (DBDate& date);
		bool operator!= (DBDate& date);
		DBDate& operator+=(int days);
		DBDate& operator-=(int days);
		int operator-(DBDate& date);
	};
  
	enum DBType {
		NoType,
		Int32,
		Double,
		String,
		Date
	};
	enum Condition { Undefined, Equal, NotEqual, Less, Greater, LessOrEqual, GreaterOrEqual };
	const int LENGTH = 24;
	
	struct ColumnDesc {
		char colName[LENGTH];
		DBType colType;
		int length; 
	};
	struct Strip {
		int nField;
		int* fieldWidth;
	};
	typedef map<string, void*> Row;
	typedef map<string, ColumnDesc> Header;

	string GetTabNameFromPath(string path);
	string ignoreBlanc(const string str);

	void* GetValue(string value, string columnName, Header hdr);
	void* SetValue(string value, string columnName, Header hdr);
	bool comparator(DBType type, void *obj1, Condition condition, void *obj);
	int GetLength(ColumnDesc colDesc);

	class DBTableTxt {

		Header columnHeaders_;
		string tableName_;
		string primaryKey_;
		vector<Row> data_;
		string fileName_;
	public:
		DBTableTxt() {}
		DBTableTxt(string tabName);
		DBTableTxt(string tabName, Header hdr, string primKey);
		string TypeName(DBType type);
		DBType TypeByName(string name);
		void* readAnyType(string val, DBType type);
		~DBTableTxt() {}
		vector<int> IndexOfRecord(void* keyValue, string keyColumnName);
		string ValueToString(void* value, string columnName);
		void ReadDBTable(string tabName);//tabName=path+tableName
		void PrintTable(int screenWidth);
		void WriteDBTable(string tabName);//tabName=path+tableName	
		int GetSize();
		DBType GetType(char* columnName);
		Row operator[](int ind);
		void SetFileName(string path);
		void SetTableName(string tName);
		void SetPrimaryKey(string key);
		string GetFileName();
		string GetTableName();
		string GetPrimaryKey() { return primaryKey_; }
		Header GetHeader();
		void SetHeader(Header& hdr);
		void CreateMaket (map <int, int> &strip, int screenWidth);
		Row CreateRow();
		Row GetRow(int index);
		void AddRow(Row row, int index);
	};
	
	class DBTableSet
	{
	private:
		string dbName_;
		map<string, DBTableTxt*> db_;
	public:
		DBTableSet() {};
		DBTableSet(string name);
		int ReadDB();
		void PrintDB(int numcol);
		void WriteDB();
		string GetDBName() { return dbName_; }
		DBTableTxt* operator[](string tableName);
	};

}

#endif


