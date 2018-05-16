#include "DBTable.h"


namespace dbmanager {

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

	void DBTable::SetFileName(const string& fileName) {
		pathToTab_ = fileName;
	}
}