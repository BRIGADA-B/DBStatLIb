
#include "dbmanager.h"
#include "dbmsLib_v1.h"

namespace dbmanager {

// <----------------------------------------- DBDate class ---------------------------------->
	DBDate::DBDate(string date) {

	}


// <----------------------------------------- DBTableTxt class ---------------------------------->
	DBTableTxt::DBTableTxt(string tableName) {
		
	}

<<<<<<< HEAD
	void DBTableTxt::ReadDBTable(string tabName){

	}

	void DBTableTxt::PrintTable(int screenWidth){
	}

	void DBTableTxt::WriteDBTable(string tabName){
	}

=======
	int DBTableTxt::GetSize()
	{
		return 0;
	}

	DBType DBTableTxt::GetType(char * columnName)
	{
		return DBType();
	}

	void DBTableTxt::SetFileName(string path){
	}

	void DBTableTxt::SetTableName(string tName){
	}

	void DBTableTxt::SetPrimaryKey(string key){
	}

	string DBTableTxt::GetFileName(){
		return string();
	}

	string DBTableTxt::GetTableName(){
		return string();
	}

	Header DBTableTxt::GetHeader()
	{
		return Header();
	}

	void DBTableTxt::SetHeader(Header & hdr){
	
	}

	Row DBTableTxt::GetRow(int index){
		return Row();
	}



>>>>>>> Добавил пустышки для set и get
// <----------------------------------------- DBTableSet class ---------------------------------->
	DBTableSet::DBTableSet(string name) {

	}
}