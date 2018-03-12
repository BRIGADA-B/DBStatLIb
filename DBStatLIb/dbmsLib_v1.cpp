#include <sstream>
#include <cstring>
#include <cassert>
#include "dbmsLib_v1.h"

// Need to consider. Where to store this map.
map<string, dbmsLib::DBType> stringDBType;
map<dbmsLib::DBType, string> DBTypeToString;

inline void dbmsLib::initStringDBTypeMap() {
	stringDBType["Int32"] = Int32;
	stringDBType["Double"] = Double;
	stringDBType["String"] = String;
	stringDBType["Date"] = Date;
}

inline void dbmsLib::initDBTypeToStringMap() {
	DBTypeToString[Int32] = "Int32";
	DBTypeToString[Double] = "Double";
	DBTypeToString[String] = "String";
	DBTypeToString[Date] = "Date";
}


//Change to stringstream conversion
//rename to GetValue

void* dbmsLib::readAnyType(string val, DBType type){
	void* res;
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
	default:
		res = NULL;
	}

	return res;
}

//------------------------- DBTableText --------------------------------------

void dbmsLib::PrintTable1(DBTableTxt& tab, int screenWidth) {
	cout << "Таблица " << tab.GetTableName() << endl;



	for (unsigned int i = 0; i < screenWidth; i++)
		cout << "=";

	Header header = tab.GetHeader();

	// size_t -> int Undefined behavior!!!!!
	for (const auto& a : header) 
		cout << setw(max(a.second.length, static_cast<int> (a.first.length())) + 2) << a.first;
	
	cout << endl;

	for(const auto& a : header)
		cout << setw(max(a.second.length, static_cast<int> (a.first.length())) + 2) << DBTypeToString[a.second.colType];

	cout << endl;
	
	for (unsigned int i = 0; i < screenWidth; i++)
		cout << "-";

	for (int i = 0; i < tab.GetSize(); i++) {
		for (const auto& a : tab[i]) {
			switch (header[a.first].colType) {
			case Int32:
				cout << setw(max(header[a.first].length, static_cast<int>(a.first.length())) + 2)  << *static_cast<int*>(a.second);
				break;
			case String:
				cout << setw(max(header[a.first].length, static_cast<int>(a.first.length())) + 2) << *static_cast<string*>(a.second);
				break;
			case Double:
				cout << setw(max(header[a.first].length, static_cast<int>(a.first.length())) + 2) << *static_cast<double*>(a.second);
				break;
			case Date:
				cout << setw(max(header[a.first].length, static_cast<int>(a.first.length())) + 2) << *static_cast<DBDate*>(a.second);
				break;
			}	
		}
		cout << endl;
	}

	for (unsigned int i = 0; i < screenWidth; i++)
		cout << "=";
}

void dbmsLib::ReadDBTable1(DBTableTxt & tab, string tabName)
{
	ifstream in(tabName);

	if (!in.is_open()) {
		cout << "Не удалось прочитать таблицу из пути: " << tabName << endl;
		return;
	}


	tab.SetFileName(tabName);

	initStringDBTypeMap();
	initDBTypeToStringMap();

	map<int, string> columnNameByIndex;

	Header header;
	Row row;
	string tmp;

	//tableName first
	getline(in, tmp, '|');

	// Table name length have to <= 24
	assert(tmp.length() <= 24);
	tab.SetTableName(tmp);

	//Primary key second
	getline(in, tmp);
	tab.SetPrimaryKey(tmp);

	cout << tab.GetTableName() << " " << tab.GetPrimaryKey() << endl;

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

			tab.AddRow(row, i - 2);
		}
	}

	tab.SetHeader(header);


	std::cout << __FUNCTION__ << std::endl;
}


