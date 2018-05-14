#pragma once

#include "utils.h"

using namespace std;

namespace dbmanager {
	class DBTable {
	public:
		virtual void ReadDBTable() = 0;
		virtual void WriteDBTable() = 0;
		virtual void PrintDBTable() = 0;
		virtual void DeleteRow(size_t index) = 0;
		virtual void CreateRow() = 0;
		virtual void AddRow() = 0;
		virtual Row GetRow(size_t index) = 0;
		virtual Header GetHeader();
		virtual void SetHeader(Header& header);
		virtual Row operator[](size_t index) = 0;
	private:
		Header header_;
		string tabName_;
		string pathToTab_;
		string primaryKey_;
	};
}