#include "DBTable.h"


namespace dbmanager {

	const string DBTable::dbFormat = "csv";
	std::vector<std::string> DBTable::tableTypesName = { "Txt", "Bin" };

	Header DBTable::GetHeader()
	{
		return header_;
	}
	void DBTable::SetHeader(Header& header)
	{
		header_.insert(header.begin(), header.end());
	}

	string DBTable::GetFileName()
	{
		return pathToTab_;
	}

	string DBTable::GetTableName()
	{
		return tabName_;
	}

	string DBTable::GetPrimaryKey()
	{
		return primaryKey_;
	}

	void DBTable::SetFileName(const string& fileName) {
		pathToTab_ = fileName;
	}
	void DBTable::SetTableName(string tName)
	{
		tabName_ = tName;
	}
	void DBTable::SetPrimaryKey(string key)
	{
		primaryKey_ = key;
	}
}