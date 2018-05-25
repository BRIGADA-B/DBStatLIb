#pragma once
#include<map>
#include<string>
#include<cassert>

namespace dbmanager {

	// –азделитель в операционной системе. Windows: \ ; Linux: / ;
	const char OS_DELEMITER = '\\';

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

	template<class T>
	void* toVoidPtr(const T& val) {
		void* to = static_cast<void*>(new T(val));
	
		assert( *static_cast<T*>(to) == val);

		return to;
	}

}