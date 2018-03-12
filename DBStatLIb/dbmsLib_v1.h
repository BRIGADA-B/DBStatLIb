#pragma once
#ifndef _dbmsLib_
#define _dbmsLib_
#include <iostream>
#include <fstream>
#include <strstream>
#include <iomanip>
#include <string>
#include <vector>
#include <map>

using namespace std;
namespace dbmsLib
{

	class DBDate
  {	
	  
		static const int arrDays[13];
		friend string DateToStr(DBDate& date);
		friend ostream& operator<<(ostream& out,DBDate& date);
		int day, month, year;
	public:
		DBDate(string date);
		DBDate(int d,int m,int y);
		DBDate():day(0),month(0),year(0){};
		DBDate(DBDate& dat):day(dat.day),month(dat.month),year(dat.year){}
		int GetDay();
		int GetMonth();
		int GetYear();
		bool IsLeapYear (int year);
		int GetDaysInMonth(int month,int year);
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

enum Condition{Undefined,Equal,NotEqual,Less,Greater,LessOrEqual,GreaterOrEqual};
const int LENGTH = 24;

struct ColumnDesc { 
	char colName[LENGTH];
	DBType colType;
	int length;
}; 
struct Strip{
	int nField;
	int* fieldWidth;
};

  typedef map<string, void*> Row;
  typedef map<string, ColumnDesc> Header;

void* readAnyType(string, DBType);
void initStringDBTypeMap();
void initDBTypeToStringMap();
string GetTabNameFromPath(string path);
string ignoreBlanc(const string str);
void* GetValue(string value, string columnName,Header hdr);
void* SetValue(string value, string columnName,Header hdr);
bool comparator(DBType type,void *obj1,Condition condition,void *obj);
int GetLength(ColumnDesc colDesc);


class DBTableTxt{
	
		Header columnHeaders;
		string tableName;
		string primaryKey; 	
		vector<Row> data;
		string fileName;
  	public:
		DBTableTxt(){}
		DBTableTxt(string tabName);
		DBTableTxt(string tabName,Header hdr,string primKey);
		const char* TypeName(DBType type);
		~DBTableTxt(){}
		vector<int> IndexOfRecord(void* keyValue,string keyColumnName);
 		string valueToString(Row& row,string columnName);
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
		string GetPrimaryKey(){return primaryKey;}
		Header GetHeader();
		void SetHeader(Header& hdr);
		Row CreateRow();
		Row GetRow(int index);
		void AddRow(Row row,int index);
		void CreateTableMaket(Strip* &strips,int &nStrip,int screenWidth);
		friend void ReadDBTable1(DBTableTxt& tab,string tabName);//tabName=path+tableName
		friend void PrintTable1(DBTableTxt& tab, int screenWidth);
  };
class DBTableSet
{
private:
	string dbName;
	map<string, DBTableTxt*> db;
public: 
	DBTableSet(){};
	DBTableSet(string name);
	int ReadDB();
	void PrintDB(int numcol);
	void WriteDB();
	string GetDBName(){return dbName;}
	DBTableTxt* operator[](string tableName); 
};

}
#endif
