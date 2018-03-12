
#include "dbmanager.h"
#include<iostream>
#include<sstream>
#include<iomanip>
#include<fstream>
#include<cassert>

namespace dbmanager {

// <----------------------------------------- DBDate class ---------------------------------->
	DBDate::DBDate(string date) {

	}

	int DBDate::GetDay()
	{
		return day_;
	}

	int DBDate::GetMonth()
	{
		return month_;
	}

	int DBDate::GetYear()
	{
		return year_;
	}

// <----------------------------------------- DBTableTxt class ---------------------------------->
	DBTableTxt::DBTableTxt(string tableName) {
		
	}

	string DBTableTxt::TypeName(DBType type)
	{
		if (type == String)
			return "String";
		else if (type == Double)
			return "Double";
		else if (type == Int32)
			return "Int32";
		else if (type == Date)
			return "Date";
		else if (type == NoType)
			return "NoType";

		return "";
	}

	DBType DBTableTxt::TypeByName(string name)
	{
		if (name == "String")
			return String;
		else if (name == "Double")
			return Double;
		else if (name == "Int32")
			return Int32;
		else if (name == "Date")
			return Date;
		else if (name == "NoType")
			return NoType;

	}

	void DBTableTxt::ReadDBTable(string tabName){

		ifstream in(tabName);

		if (!in.is_open()) {
			cout << "Ќе удалось прочитать таблицу из пути: " << tabName << endl;
			return;
		}

		SetFileName(tabName);
			
		map<int, string> columnNameByIndex;

		Header header;
		Row row;
		string tmp;

		//tableName first
		getline(in, tmp, '|');

		// Table name length have to <= 24
		assert(tmp.length() <= 24);
		SetTableName(tmp);

		//Primary key second
		getline(in, tmp);
		SetPrimaryKey(tmp);

		cout << GetTableName() << " " << GetPrimaryKey() << endl;

		size_t i = 0;
		int colCount = 0;
		while (getline(in, tmp) && ++i) {
			stringstream ss(tmp);
			string tmpElement;
			if (i == 1)
				for (; getline(ss, tmpElement, '|'); colCount++) {

					ColumnDesc columnDesc;

					// Column name length have to <= 24
					assert(tmpElement.length() <= 24);

					strcpy_s(columnDesc.colName, tmpElement.c_str());

					//Column type
					getline(ss, tmpElement, '|');


					if (stringDBType.find(tmpElement) != stringDBType.end())
						columnDesc.colType = stringDBType[tmpElement];
					else
						columnDesc.colType = NoType;

					//Column  length

					// Do read int instead of string
					getline(ss, tmpElement, '|');
					columnDesc.length = stoi(tmpElement);

					header[string(columnDesc.colName)] = columnDesc;
					columnNameByIndex[colCount] = string(columnDesc.colName);

				}
			else {
				for (int j = 0; j < colCount; j++) {

					getline(ss, tmpElement, '|');

					row[columnNameByIndex[j]] = readAnyType(tmpElement,
						header[columnNameByIndex[j]].colType);
				}

				AddRow(row, i - 2);
			}
		}

		SetHeader(header);


	}

	void DBTableTxt::PrintTable(int screenWidth){
	}

	void DBTableTxt::WriteDBTable(string tabName){
	}

	int DBTableTxt::GetSize()
	{
		return data_.size();
	}

	DBType DBTableTxt::GetType(char * columnName)
	{
		return columnHeaders_[columnName].colType;
	}

	void DBTableTxt::SetFileName(string path){
		fileName_ = path;
	}

	void DBTableTxt::SetTableName(string tName){
		tableName_ = tName;
	}

	void DBTableTxt::SetPrimaryKey(string key){
		primaryKey_ = key;
	}

	string DBTableTxt::GetFileName(){
		return fileName_;
	}

	string DBTableTxt::GetTableName(){
		return tableName_;
	}

	Header DBTableTxt::GetHeader()
	{
		return columnHeaders_;
	}

	void DBTableTxt::SetHeader(Header & hdr){
		columnHeaders_.clear();
		columnHeaders_.insert(hdr.begin(), hdr.end());
	}

	Row DBTableTxt::GetRow(int index){
		return data_[index];
	}

	void DBTableTxt::AddRow(Row row, int index) {
		data_.emplace(data_.begin() + index, row);

	}
// <----------------------------------------- DBTableSet class ---------------------------------->
	DBTableSet::DBTableSet(string name) {

	}
	DBTableTxt * DBTableSet::operator[](string tableName)
	{
		return db_[tableName];
	}

}