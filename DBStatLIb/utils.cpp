#include "utils.h"
#include "DBDate.h"

namespace dbmanager {
	void* GetValue(DBType colType) { //return void* with dedicated memory for a specific type

		void* res = nullptr;
		switch (colType) {
		case (1):
			res = new int;
			break;
		case (2):
			res = new double;
			break;
		case (3):
			res = new std::string;
			break;
		case (4):
			res = new DBDate;
			break;
		}

		return res;
	}

	int GetByte(DBType type) { //return number of byte for a specific type
		if (type == Int32) return 4;
		if (type == Double) return 8;
		if (type == Date) return sizeof(DBDate);
		if (type == String) return sizeof(string);
		if (type == NoType) return sizeof(bool);
	}

	int GetLength(ColumnDesc colDesc) {
		return colDesc.length;
	}
}