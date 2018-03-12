
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

		return DBType();
	}

	void * DBTableTxt::readAnyType(string val, DBType type)
	{
		void* res = NULL;
		switch (type) {
		case Int32:
			res = new int(stoi(val));
			break;
		case Double:
			res = new double(stod(val));
			break;
		case String:
			res = new string(val);
			break;
		case Date:
			res = new DBDate(val);
			break;
		case NoType:
			res = new bool(stoi(val));  // Undefiden behavior
		}

		return res;
	}


	string DBTableTxt::ValueToString(void* value, string columnName)
	{
		Header header = GetHeader();
		switch (header[columnName].colType) {
		case String:
			return *static_cast<string*>(value);
		case Int32:
			return to_string(*static_cast<int*>(value)); // TODO: Add check for errors
		case Double:
			return to_string(*static_cast<double*>(value));
		case Date:
			return "Data"; // TODO: add cast from DBDate -> string
		case NoType:
			return "NoType"; // NoType ????????/
		default:
			return "ERROR";
		}
	}

	void DBTableTxt::ReadDBTable(string tabName){

		ifstream in(tabName);

		if (!in.is_open()) {
			cout << "Не удалось прочитать таблицу из пути: " << tabName << endl;
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


					columnDesc.colType = TypeByName(tmpElement);

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
					
					if (!row[columnNameByIndex[j]]) {
						cout << "Не удалось считать данные из колонки: " << columnNameByIndex[j]
							<< "В строке: " << i - 1;
					}
				}

				AddRow(row, i - 2);
			}
		}

		SetHeader(header);


	}

	void DBTableTxt::PrintTable(int screenWidth){
		cout << "Таблица " << GetTableName() << endl;



		for ( int i = 0; i < screenWidth; i++)
			cout << "=";

		Header header = GetHeader();

		// size_t -> int Undefined behavior!!!!!
		for (const auto& a : header)
			cout << setw(max(a.second.length, static_cast<int> (a.first.length())) + 2) << a.first;

		cout << endl;

		for (const auto& a : header)
			cout << setw(max(a.second.length, static_cast<int> (a.first.length())) + 2) << TypeName(a.second.colType);

		cout << endl;

		for ( int i = 0; i < screenWidth; i++)
			cout << "-";

		for (int i = 0; i < GetSize(); i++) {
			for (const auto& a : data_[i]) {
				cout << setw(max(header[a.first].length, static_cast<int>(a.first.length())) + 2) << ValueToString(a.second, a.first);
			}
			cout << endl;
		}

		for ( int i = 0; i < screenWidth; i++)
			cout << "=";
	}

	void DBTableTxt::WriteDBTable(string tabName){
		ofstream out(tabName);

		if (!out.is_open()) {
			cout << "Cannot open file: " << tabName << " for reading\n";
			return;
		}

		out << GetTableName() << "|" << GetPrimaryKey() << endl;

		Header header = GetHeader();

		size_t i = 0;
		for (const auto& a : header) 
			cout << a.second.colName << "|" << TypeName(a.second.colType) << "|" 
				 << a.second.length << (i++ < header.size() - 1 ? "|":"\n");

		for (const auto& row : data_) {
			i = 0;
			for (const auto& a : row)
				cout << ValueToString(a.second, a.first) << (i++ < row.size() - 1 ? "|":"\n");
		}
		
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