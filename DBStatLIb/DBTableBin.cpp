#include "DBTableBin.h"


namespace dbmanager {
	void DBTableBin::ReadDBTable(const string &)
	{
	}
	void DBTableBin::WriteDBTable(const string &)
	{
	}
	void DBTableBin::PrintDBTable(const int)
	{
	}
	void DBTableBin::DeleteRow(size_t index)
	{
	}
	void DBTableBin::CreateRow()
	{
	}
	void DBTableBin::AddRow(const std::shared_ptr<Row>& row, int index)
	{
	}
	std::shared_ptr<Row> DBTableBin::GetRow(size_t index)
	{
		return nullptr;
	}
	Row& DBTableBin::operator[](size_t index)
	{
		return Row();
	}
	std::vector<std::shared_ptr<Row>> DBTableBin::Select(std::string columnName, Condition cond, void * value)
	{
		return {};
	}
	int DBTableBin::GetSize() const
	{
		return 0;
	}
	void DBTableBin::Clear()
	{
	}
}