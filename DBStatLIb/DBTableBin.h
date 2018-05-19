#pragma once
#include "DBTable.h"

namespace dbmanager {

	class DBTableBin : public DBTable
	{
	public:
		DBTableBin() {}
		~DBTableBin() {}

		// ������������ ����� DBTable
		virtual void ReadDBTable(const string &) override;

		virtual void WriteDBTable(const string &) override;

		virtual void PrintDBTable(const int) override;

		virtual void DeleteRow(size_t index) override;

		virtual void CreateRow() override;

		virtual void AddRow(const Row& row, int index) override;

		virtual Row GetRow(size_t index) override;

		virtual Row operator[](size_t index) override;

		virtual shared_ptr<DBTable> Select(std::string columnName, Condition cond, void * value) override;

		virtual int GetSize() const override;

	};
}