
#include "dbmanager.h"
#include<iostream>
#include<sstream>
#include<iomanip>
#include<fstream>
#include<cassert>

namespace dbmanager {

int RightTableName (string tablename)
	{
		if (tablename=="Books") 
			return 0;
		if (tablename=="Students") 
			return 0;
		if (tablename=="Abonements") 
			return 0;
		return 1;
	}

int Menu ()
	{
		cout <<endl;
		cout <<"1: Print table"<<endl;
		cout <<"2: Output table into file"<<endl;
		cout <<"3: Finish work with table"<<endl;
		int n;
		cin >>n;
		return n;
	}

string  TableChoose () //return path to table (string)
	{
			cout <<"Enter table name: \n1)Students\n2)Abonements\n3)Books\n"<<endl;
			string name;
			cin >>name;
			while (RightTableName(name)) 
				{
					cout <<"Incorrect table name, please enter again"<<endl;
					name="";
					cin >>name;
				}
			name="LibraryTxt\\"+name;
			name+=".csv";
			return name;
	}

// <----------------------------------------- DBDate class ---------------------------------->
	DBDate::DBDate(string date) {
		string buf="";
		int k=0;
		int *data=new int [3];
		for (int i=0; i<date.size(); i++){
			while (date [i]!='.' && i<date.size()){
				buf+=date[i];
				i++;
			}

			data[k]=stoi (buf);
			k++;
			buf="";
		}	

		SetDay (data [0]);
		SetMonth (data [1]);
		SetYear (data [2]);
		delete data;
	}

	DBDate::DBDate (int d, int m, int y){
		SetDay (d);
		SetMonth (m);
		SetYear (y);
	}

	bool DBDate::IsLeapYear (int y){
		if (y % 4 !=0) return 0;
			else if (y % 100 ==0 && y % 400 !=0) return 0;
				else return 1;
	}

	int DBDate::GetDaysInMonth (int m, int y) {
		switch (m){
			case 1 : return 31;
			case 3 : return 31;
			case 5 : return 31;
			case 7 : return 31;
			case 8 : return 31;
			case 10 : return 31;
			case 12 : return 31;
			case 2: 
				{
					if (IsLeapYear (y)) return 29; 
						else return 28;
				}
			default : return 30;
		}
	}

	int DBDate::DaysInCurYear (){
		if (IsLeapYear (year_)) return 366;
			else return 365;
	}

	bool DBDate::operator== (DBDate& date){
		if (day_==date.day_ && month_==date.month_ && year_==date.year_)
			return 1;
		else 
			return 0;
	}

	bool DBDate::operator!= (DBDate& date){
		if (day_!=date.day_ || month_!=date.month_ || year_!=date.year_)
			return 1;
		else 
			return 0;
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

	void DBDate::SetDay (int d){
		day_=d;
	}

	void DBDate::SetMonth (int m){
		month_=m;
	}

	void DBDate::SetYear (int y){
		year_=y;
	}

// <----------------------------------------- DBTableTxt class ---------------------------------->
	DBTableTxt::DBTableTxt(string tableName) {
		
	}

	string DBTableTxt::TypeName(DBType type)
	{
		if (type == String)
			return "String";
		else if (type == Double)
			return "Double";
		else if (type == Int32)
			return "Int32";
		else if (type == Date)
			return "Date";
		else if (type == NoType)
			return "NoType";

		return "";
	}

	DBType DBTableTxt::TypeByName(string name)
	{
		if (name == "String")
			return String;
		else if (name == "Double")
			return Double;
		else if (name == "Int32")
			return Int32;
		else if (name == "Date")
			return Date;
		else if (name == "NoType")
			return NoType;

		return DBType();
	}

	void * DBTableTxt::readAnyType(string val, DBType type)
	{
		void* res = NULL;
		switch (type) {
		case Int32:
			res = new int(stoi(val));
			break;
		case Double:
			res = new double(stod(val));
			break;
		case String:
			res = new string(val);
			break;
		case Date:
			res = new DBDate(val);
			break;
		case NoType:
			res = new bool(stoi(val));  // Undefiden behavior
		}

		return res;
	}



	string DBTableTxt::ValueToString(void* value, string columnName)
	{
		Header header = GetHeader();
		switch (header[columnName].colType) {
		case String:
			return *static_cast<string*>(value);
		case Int32:
			return to_string(*static_cast<int*>(value)); // TODO: Add check for errors
		case Double:
			return to_string(*static_cast<double*>(value));
		case Date:
			return "Data"; // TODO: add cast from DBDate -> string
		case NoType:
			return "NoType"; // NoType ????????/
		default:
			return "ERROR";
		}
	}

	void DBTableTxt::ReadDBTable(string tabName){

		ifstream in(tabName);

		if (!in.is_open()) {
			cout << "File cannot be opened: " << tabName << endl;
			return;
		}

		SetFileName(tabName);
			
		map<int, string> columnNameByIndex;

		Header header;
		Row row;
		string tmp;

		//tableName first
		getline(in, tmp, '|');
		// Table name length have to <= 24
		assert(tmp.length() <= 24);
		SetTableName(tmp);

		//Primary key second
		getline(in, tmp);
		SetPrimaryKey(tmp);

		size_t i = 0;
		int colCount = 0;
		while (getline(in, tmp) && ++i) {
			stringstream ss(tmp);
			string tmpElement;
			if (i == 1)
				for (; getline(ss, tmpElement, '|'); colCount++) {

					ColumnDesc columnDesc;

					// Column name length have to <= 24
					assert(tmpElement.length() <= 24);

					strcpy_s(columnDesc.colName, tmpElement.c_str());

					//Column type
					getline(ss, tmpElement, '|');


					columnDesc.colType = TypeByName(tmpElement);

					//Column  length

					// Do read int instead of string
					getline(ss, tmpElement, '|');
					columnDesc.length = stoi(tmpElement);

					header[string(columnDesc.colName)] = columnDesc;
					columnNameByIndex[colCount] = string(columnDesc.colName);

				}
			else {
				for (int j = 0; j < colCount; j++) {

					getline(ss, tmpElement, '|');

					row[columnNameByIndex[j]] = readAnyType(tmpElement,
						header[columnNameByIndex[j]].colType);
					
					if (!row[columnNameByIndex[j]]) {
						cout << "cannot read column data: " << columnNameByIndex[j]
							<< "line: " << i - 1;
					}
				}

				AddRow(row, i - 2);
			}
		}

		SetHeader(header);

	}

	void DBTableTxt::CreateMaket (map <int, int> &strip, int screenWidth){
		Header hdr=GetHeader();

		int count=0, wide=0, k=1;

		for (const auto& a : hdr){
			wide+=a.second.length;
			if (wide>screenWidth){
				strip[k]=count;
				k++;
				count=0;
				wide=a.second.length;
			}
			count++;
		}

		strip[k]=count;

	}

	void DBTableTxt::PrintTable(int screenWidth){
		if (screenWidth <= 0) {
			cout << "Error cannot printTable due to small screenWidth" << screenWidth << endl;
		}
		Header header = GetHeader();

		for (const auto& a : header) //check for possibility of print table
			if (a.second.length>screenWidth){
				cout <<"Column width is too big"<<endl;
				return;
			}

		cout << "Table " << GetTableName() << endl;

		for ( int i = 0; i < screenWidth; i++)
			cout << "=";
		cout <<endl;

		map <int,int> strip;
		CreateMaket (strip, screenWidth);

		auto iterHeaderMain = header.begin ();
		auto iterHeader = iterHeaderMain;
		int iterData=0;

		for (int i=1; i<=strip.size(); i++){
			//PRINT COLUMN HEADER
			iterHeader=iterHeaderMain;

			for (int count=0; count<strip[i]; count++){ //print column name
				cout <<setw (iterHeader->second.length+1)<<iterHeader->second.colName;
				iterHeader++;			
			}
			cout <<endl;

			iterHeader=iterHeaderMain;

			for (int count=0; count<strip[i]; count++){ //print data type of column 
				cout <<setw (iterHeader->second.length+1)<<TypeName (iterHeader->second.colType);
				iterHeader++;			
			}
			cout <<endl;

			iterHeader=iterHeaderMain;

			for (int count=0; count<strip[i]; count++)
				iterHeaderMain++;

			//PRINT DATA OF COLUMN

			for (int z=0; z<GetSize(); z++){
				auto iter=data_[z].begin();
				for (int k=0; k<iterData; k++)
					iter++;
				for (int count=0; count<strip[i]; count++){
					cout << setw(max(header[iter->first].length, static_cast<int>(iter->first.length())) +1) << ValueToString (iter->second,iter->first);
					iter++;
				}
				cout <<endl;
			}
			iterData+=strip[i];	
			cout <<endl;
		}

	}

	void DBTableTxt::WriteDBTable(string tabName){
		ofstream out(tabName);

		if (!out.is_open()) {
			cout << "Cannot open file: " << tabName << " for reading\n";
			return;
		}

		out << GetTableName() << "|" << GetPrimaryKey() << endl;

		Header header = GetHeader();

		size_t i = 0;
		for (const auto& a : header) 
			out << a.second.colName << "|" << TypeName(a.second.colType) << "|" 
				 << a.second.length << (i++ < header.size() - 1 ? "|":"\n");

		for (const auto& row : data_) {
			i = 0;
			for (const auto& a : row)
				out << ValueToString(a.second, a.first) << (i++ < row.size() - 1 ? "|":"\n");
		}
		
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
		columnHeaders_.insert(hdr.begin(), hdr.end());
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