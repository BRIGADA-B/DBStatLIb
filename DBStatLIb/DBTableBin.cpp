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
	void DBTableBin::AddRow(const Row& row, int index)
	{
	}
	Row DBTableBin::GetRow(size_t index)
	{
		return Row();
	}
	Row DBTableBin::operator[](size_t index)
	{
		return Row();
	}
	shared_ptr<DBTable> DBTableBin::Select(std::string columnName, Condition cond, void * value)
	{
		return shared_ptr<DBTable>();
	}
	int DBTableBin::GetSize() const
	{
		return 0;
	}
}