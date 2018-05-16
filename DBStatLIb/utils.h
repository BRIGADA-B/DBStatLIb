#pragma once
#include<map>
#include<string>

namespace dbmanager {

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
	typedef std::map<std::string, void*> Row;
	typedef std::map<std::string, ColumnDesc> Header;

	void* GetValue(DBType colType);
	int GetByte(DBType type);
	int GetLength(ColumnDesc colDesc);

}