#pragma once
#include "DBTable.h"

namespace dbmanager {

	class DBTableBin : public DBTable
	{
	public:
		DBTableBin() {}
		~DBTableBin() {}

		// Унаследовано через DBTable
		virtual void ReadDBTable(const string &) override;

		virtual void WriteDBTable(const string &) override;

		virtual void PrintDBTable(const int) override;

		virtual void DeleteRow(size_t index) override;

		virtual void CreateRow() override;

		virtual void AddRow(const std::shared_ptr<Row>& row, int index) override;

		virtual std::shared_ptr<Row> GetRow(size_t index) override;

		virtual Row& operator[](size_t index) override;

		virtual std::vector<std::shared_ptr<Row>> Select(std::string columnName, Condition cond, void * value) override;

		virtual int GetSize() const override;
		virtual void Clear() override;

	};
}