
#include "dbmanager.h"
#include "dbmsLib_v1.h"

namespace dbmanager {

// <----------------------------------------- DBDate class ---------------------------------->
	DBDate::DBDate(string date) {

	}

	int DBDate::GetDay()
	{
		return day_;
	}

	int DBDate::GetMonth()
	{
		return month_;
	}

	int DBDate::GetYear()
	{
		return year_;
	}


// <----------------------------------------- DBTableTxt class ---------------------------------->
	DBTableTxt::DBTableTxt(string tableName) {
		
	}

	void DBTableTxt::ReadDBTable(string tabName){

	}

	void DBTableTxt::PrintTable(int screenWidth){
	}

	void DBTableTxt::WriteDBTable(string tabName){
	}

	int DBTableTxt::GetSize()
	{
		return data_.size();
	}

	DBType DBTableTxt::GetType(char * columnName)
	{
		return columnHeaders_[columnName].colType;
	}

	void DBTableTxt::SetFileName(string path){
		fileName_ = path;
	}

	void DBTableTxt::SetTableName(string tName){
		tableName_ = tName;
	}

	void DBTableTxt::SetPrimaryKey(string key){
		primaryKey_ = key;
	}

	string DBTableTxt::GetFileName(){
		return fileName_;
	}

	string DBTableTxt::GetTableName(){
		return tableName_;
	}

	Header DBTableTxt::GetHeader()
	{
		return columnHeaders_;
	}

	void DBTableTxt::SetHeader(Header & hdr){
		columnHeaders_.clear();
		columnHeaders_.emplace(hdr.begin(), hdr.end());
	}

	Row DBTableTxt::GetRow(int index){
		return data_[index];
	}

	void DBTableTxt::AddRow(Row row, int index) {
		data_.emplace(data_.begin() + index, row);

	}

// <----------------------------------------- DBTableSet class ---------------------------------->
	DBTableSet::DBTableSet(string name) {

	}
	DBTableTxt * DBTableSet::operator[](string tableName)
	{
		return db_[tableName];
	}
}