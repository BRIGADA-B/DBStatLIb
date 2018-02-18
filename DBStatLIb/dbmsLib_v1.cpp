#include <sstream>
#include <cstring>
#include <cassert>
#include "dbmsLib_v1.h"

// Need to consider. Where to store this map.
map<string, dbmsLib::DBType> stringDBType;

inline void dbmsLib::initStringDBTypeMap() {
	stringDBType["Int32"] = Int32;
	stringDBType["Double"] = Double;
	stringDBType["String"] = String;
	stringDBType["Date"] = Date;
}

void* dbmsLib::readAnyType(string val, DBType type) {
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


void dbmsLib::ReadDBTable1(DBTableTxt & tab, string tabName)
{
	ifstream in(tabName);

	if (!in.is_open()) {
		cout << "Ќе удалось прочитать таблицу из пути: " << tabName << endl;
		return;
	}


	tab.SetFileName(tabName);

	initStringDBTypeMap();

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

				getline(ss, tmpElement, '|');
				columnDesc.length = stoi(tmpElement);

				header[string(columnDesc.colName)] = columnDesc;
				columnNameByIndex[colCount] = string(columnDesc.colName);

			}
		else {
			for (int j = 0; j < colCount; j++) {
				if (j - 1 != colCount)
					getline(ss, tmpElement, '|');
				else
					getline(ss, tmpElement);

				row[columnNameByIndex[j]] = readAnyType(tmpElement,
					header[columnNameByIndex[j]].colType);
			}

			tab.AddRow(row, i - 2);
		}
	}

	tab.SetHeader(header);


	std::cout << __FUNCTION__ << std::endl;
}
