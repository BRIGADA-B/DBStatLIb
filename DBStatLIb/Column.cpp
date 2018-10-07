#include "Column.h"

namespace dbmanager {
	void Column::SetType(DBType dbtype)
	{
		dbtype_ = dbtype;
	}

	void Column::SetLength(int length)
	{
		length_ = length;
	}

	void Column::SetColumnName(const std::string & name)
	{
		columnName_ = name;
	}

	DBType Column::GetDbtype() const
	{
		return dbtype_;
	}

	int Column::GetLength() const
	{
		return length_;
	}


	std::string Column::GetColumnName() const
	{
		return columnName_;
	}

	bool Column::IsValueEmpty()
	{
		return isValueEmpty_;
	}
	void Column::SetIsValueEmpty(bool value)
	{
		isValueEmpty_ = value;
	}
}