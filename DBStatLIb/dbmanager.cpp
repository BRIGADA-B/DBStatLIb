#include "dbmanager.h"
#include <iostream>
#include <sstream>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <cassert>

namespace dbmanager {

	void* GetValue (DBType colType){ //return void* with dedicated memory for a specific type

	void* res=nullptr;
	switch (colType){
		case (1) : 
			res = new int;
			break;
		case (2) :
			res = new double;
			break;
		case (3) :
			res = new string;
			break;
		case (4) :
			res = new DBDate;
			break;
	}

	return res;
}

int GetByte (DBType type){ //return number of byte for a specific type
	if (type==Int32) return 4;
	if (type==Double) return 8;
	if (type==Date) return sizeof (DBDate);
	if (type==String) return sizeof (string);
	if (type==NoType) return sizeof (bool);
}

int RightTableName(string tablename) {  // choosing a table for test
		if (tablename == "Books") 
			return 0;
		if (tablename == "Students") 
			return 0;
		if (tablename == "Abonements") 
			return 0;
		return 1;
	}

int Menu() {
		cout << "\n1 - Print table\n" << "2 - Output table into file\n" << "3 - Finish work with table" << endl;
		int n; cin >> n;
		return n;
	}

int GetLength(ColumnDesc colDesc) {
	return colDesc.length;
}

string TableChoose() { // returns path to the table (makes it easier)
	cout << "Enter the table name:\n1)Students\n2)Abonements\n3)Books\n" << endl;
	string name; cin >> name;
	while (RightTableName(name)) {
		cout << "Incorrect table name, please try again" << endl;
		cin >> name;
	}
	name = "LibraryTxt\\" + name;
	name += ".csv";
	return name;
}

int SizeOfTypeByColumnDesc(ColumnDesc desc) {
	int len;
	switch (desc.colType) {
	case DBType::Int32:
		len = 4;
		break;
	case DBType::Double:
		len = 8;
		break;
	case DBType::Date:
		len = 12;
		break;
	case DBType::String:
		len = desc.length * sizeof(char);
		break;
	default:
		cerr << __FUNCTION__ << " " << __LINE__ << "Error: no such type";
		return 0;
	}

	return len;
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

string DateToStr(DBDate & date) {  // turns it all into a beatiful string
	string res;
	res += to_string(date.GetDay());
	res += ".";
	res += to_string(date.GetMonth());
	res += ".";
	res += to_string(date.GetYear());
	return res;
}

ostream & operator<<(ostream & out, DBDate & date) {  // makes "<<" work fot DBDate
	cout << date.day_ << "." << date.month_ << "." << date.year_;
	return out;
}

DBDate::DBDate(string date) {  // constructor
	string buf;
	vector<int> data(3);
	stringstream ss(date);
	int i = 0;
	while (getline(ss, buf, '.')) {
		data[i++] = stoi(buf);  // stoi = string to int
	}
	SetDay(data[0]);  //
	SetMonth(data[1]);
	SetYear(data[2]);
}

bool DBDate::IsLeapYear (int y) {  // if the year is leap
	if ((y % 4 == 0 && y % 100 != 0) || (y % 400 == 0)) return 1;
	return 0;
}

int DBDate::GetDaysInMonth (int m, int y) {  // amount of days in the month
	switch (m) {
		case 1: case 3: case 5: case 7: case 8: case 10: case 12: return 31;
		case 2: 
			return 28 + IsLeapYear(y);
			break;
		default: return 30;
	}
}

int DBDate::GetDaysInYear (int year) {  // amount of days in the year
	return 365 + IsLeapYear(year);
}

void DBDate::Set (int d, int m, int y) {
	SetDay (d);
	SetMonth (m);
	SetYear (y);
}

int DBDate::operator- (DBDate& date) {  // substract one date from another in days
	DBDate buf (day_, month_, year_);

	if (buf == date) return 0;

	DBDate dateL, dateR;

	if (buf > date) {
		dateL.Set(date.day_, date.month_, date.year_);
		dateR.Set(day_, month_, year_);
	}
	else {
		dateR.Set(date.day_, date.month_, date.year_);
		dateL.Set(day_, month_, year_);
	}
	
	int countDays = 0;

	if (dateL.year_!=dateR.year_) {
		for (int i = dateL.year_ + 1; i < dateR.year_; i++) {
			countDays += GetDaysInYear(i);
		}
		for (int i = dateL.month_ + 1; i <= 12; i++) {
			countDays += GetDaysInMonth(i, dateL.year_);
		}

		countDays+=GetDaysInMonth (dateL.month_, dateL.year_)-dateL.day_;

		for (int i = 1; i < dateR.month_; i++) {
			countDays += GetDaysInMonth(i, dateR.year_);
		}

		countDays += dateR.day_;
	}
	else {
		if (dateL.month_==dateR.month_)	{
			if (dateL.day_!=dateR.day_) 
				countDays=dateR.day_-dateL.day_-1;
			}
			else {
				for (int i = dateL.month_ + 1; i < dateR.month_; i++) {
					countDays += GetDaysInMonth(i, dateL.year_);
				}

				countDays+=GetDaysInMonth (dateL.month_, dateL.year_)-dateL.day_;
				
				countDays+=dateR.day_;
			}
		}
	return countDays;
}

bool DBDate::operator== (DBDate& date) {  // if dates are the same
	if (day_ == date.day_ && month_ == date.month_ && year_ == date.year_)
		return true;
	else 
		return false;
}

bool DBDate::operator!= (DBDate& date) {  // if dates are not the same
	if (day_ != date.day_ || month_ != date.month_ || year_ != date.year_)
		return true;
	else 
		return false;
}

bool DBDate::operator< (DBDate& date) {  // one date is earlier than the other
	if (year_ < date.year_)
		return true;
	else {
		if (year_ > date.year_)
			return false;
		else {
			if (month_ < date.month_)
				return true;
			else {
				if (month_ > date.month_)
					return false;
				else {
					if (day_ < date.day_)
						return true;
					else
						return false;
				}
			}
		}
	}
}

bool DBDate::operator<= (DBDate& date) {  // one date is earlier than the other or the same
	if (year_ < date.year_) 
		return true;
	else {
		if (year_ > date.year_)
			return false;
		else {
			if (month_ < date.month_)
				return true;
			else {
				if (month_ > date.month_)
					return false;
				else {
					if (day_ <= date.day_)
						return true;
					else
						return false;
				}
			}
		}
	}
}

bool DBDate::operator> (DBDate& date) {  // one date is later than the other
	if (year_ > date.year_) 
		return true;
	else {
		if (year_ < date.year_)
			return false;
		else {
			if (month_ > date.month_)
				return true;
			else {
				if (month_ < date.month_)
					return false;
				else {
					if (day_ > date.day_)
						return true;
					else
						return false;
				}
			}
		}
	}
}

bool DBDate::operator>= (DBDate& date) {  // one date is later than the other or the same
	if (year_ > date.year_) 
		return true;
	else {
		if (year_ < date.year_)
			return false;
		else {
			if (month_ > date.month_)
				return true;
			else {
				if (month_ < date.month_)
					return false;
				else {
					if (day_ >= date.day_)
						return true;
					else
						return false;
				}
			}
		}
	}
}

DBDate& DBDate::operator+= (int days) {  // adds days to the date
	while (days != 0) {
		if (day_ + days < GetDaysInMonth(month_, year_)) {
			day_ += days;
			days = 0;
		}
		else {
			days -= GetDaysInMonth(month_, year_) - day_ + 1;
			day_ = 1;
			month_ += 1;

			if (month_ > 12) {
				month_ = 1;
				year_ += 1;
			}
		}
	}
	return *this;
}

DBDate& DBDate::operator-= (int days) {  // substract days from the date
	while (days!=0) {
		if (day_-days > 0) {
				day_ -= days;
				days = 0;
			}
		else {
				days -= day_;
				month_--;
					if (month_ <= 0) {
						month_ = 12;
						year_--;
					}
				day_ = GetDaysInMonth (month_, year_);
		}
	}
	return *this;
}

int DBDate::GetDay() {
	return day_;
}

int DBDate::GetMonth() {
	return month_;
}

int DBDate::GetYear() {
	return year_;
}

void DBDate::SetDay (int d) {
	day_ = d;
}

void DBDate::SetMonth (int m) {
	month_ = m;
}

void DBDate::SetYear (int y) {
	year_= y;
}

// <----------------------------------------- DBTableTxt class ---------------------------------->

DBTableTxt::DBTableTxt(string fileName) : fileName_(fileName) {}

DBTableTxt::DBTableTxt(string tabName, Header hdr, string primKey): tableName_(tabName), columnHeaders_(hdr), primaryKey_(primKey) {}
	
DBTableTxt::~DBTableTxt() {
	for (auto& rows : data_) {
		for (auto& row : rows) {
			delete row.second;
		}
	}
}

string DBTableTxt::TypeName(DBType type) {  // enum to string
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

DBType DBTableTxt::TypeByName(string name) {  // string to enum
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

void * DBTableTxt::readAnyType(string val, DBType type) {  // memory allocation for any type
	void* res = NULL;
	switch (type) {
		case Int32:
			res = new int(stoi(val));  // string to int
			break;
		case Double:
			res = new double(stod(val));  // string to double
			break;
		case String:
			val += '\0';
			res = new char[val.size()];
			memcpy(res, val.c_str(), val.size());

			break;
		case Date:
			res = new DBDate(val);
			break;
		case NoType:
			res = new bool(stoi(val));  // undefined behavior
		}

	return res;
}

string DBTableTxt::ValueToString(void* value, string columnName) {  // fills allocated memory
	Header header = GetHeader();
	switch (header[columnName].colType) {
	case String:
		return *static_cast<string*>(value);
	case Int32:
		return to_string(*static_cast<int*>(value)); // TODO: Add check for errors
	case Double:
		return to_string(*static_cast<double*>(value));
	case Date:
		return DateToStr(*static_cast<DBDate*>(value)); // TODO: add cast from DBDate -> string
	case NoType:
		return "NoType"; // NoType ????????/
	default:
		return "ERROR";
	}
}


void DBTableTxt::ReadDBTable(string tabName) {
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

	// reading table name
	getline(in, tmp, '|');
	// tmp length is <= 24
	assert(tmp.length() <= 24);
	SetTableName(tmp);

	// reading primary key second
	getline(in, tmp);
	SetPrimaryKey(tmp);

	size_t i = 0;
	int colCount = 0;
	while (getline(in, tmp) && ++i) {
		stringstream ss(tmp);
		string tmpElement;
		if (i == 1)  // first row is the header
			for (; getline(ss, tmpElement, '|'); colCount++) {  // reading fields of the header
				ColumnDesc columnDesc;

				// column name length has to be <= 24
				assert(tmpElement.length() <= 24);

				strcpy_s(columnDesc.colName, tmpElement.c_str());  // reading column name

				// reading column type
				getline(ss, tmpElement, '|');
				columnDesc.colType = TypeByName(tmpElement);

				// reading column  length
				getline(ss, tmpElement, '|');
				columnDesc.length = stoi(tmpElement);

				header[string(columnDesc.colName)] = columnDesc;
				columnNameByIndex[colCount] = string(columnDesc.colName);
			}
		else {  // reading other rows of the table
			for (int j = 0; j < colCount; j++) {
				getline(ss, tmpElement, '|');
				row[columnNameByIndex[j]] = readAnyType(tmpElement, header[columnNameByIndex[j]].colType);
				if (!row[columnNameByIndex[j]]) {
					cout << "cannot read column data: " << columnNameByIndex[j] << "line: " << i - 1;
				}
			}
			AddRow(row, i - 2);
		}
	}
	SetHeader(header);
}

void DBTableTxt::CreateMaket(map <int, int> &strip, int screenWidth) {  // makes form to print the table
	Header hdr = GetHeader();

	int count = 0, wide = 0, k = 1;

	for (const auto& a : hdr) {
		wide += a.second.length;
		if (wide > screenWidth){
			strip[k] = count;
			k++;
			count = 0;
			wide = a.second.length;
		}
		count++;
	}
	strip[k] = count;
}

void DBTableTxt::PrintTable(int screenWidth) {
	if (screenWidth <= 0) {
		cout << "Error: cannot printTable due to small screenWidth" << screenWidth << endl;
	}
	Header header = GetHeader();

	for (const auto& a : header) // checks for possibility of print table
		if (a.second.length > screenWidth) {
			cout << "Column width is too big" << endl;
			return;
		}

	cout << "Table " << GetTableName() << endl;

	for (int i = 0; i < screenWidth; i++) {
		cout << "=";
	}
	cout << endl;

	map <int,int> strip;
	CreateMaket (strip, screenWidth);

	auto iterHeaderMain = header.begin();
	auto iterHeader = iterHeaderMain;
	int iterData = 0;

	for (int i = 1; i <= strip.size(); i++){
		// prints column header
		iterHeader = iterHeaderMain;

		for (int count=0; count<strip[i]; count++){  // prints column name
			cout << setw(iterHeader->second.length+1) << iterHeader->second.colName;
			iterHeader++;			
		}
		cout << endl;

		iterHeader = iterHeaderMain;

		for (int count=0; count < strip[i]; count++) {  // prints data types of column 
			cout << setw(iterHeader->second.length+1) << TypeName(iterHeader->second.colType);
			iterHeader++;			
		}
		cout << endl;

		iterHeader = iterHeaderMain;

		for (int count = 0; count < strip[i]; count++) {
			iterHeaderMain++;
		}

		// prints column data

		for (int z = 0; z < GetSize(); z++) {
			auto iter = data_[z].begin();
			for (int k = 0; k < iterData; k++)
				iter++;
			for (int count = 0; count < strip[i]; count++) {
				cout << setw(max(header[iter->first].length, static_cast<int>(iter->first.length())) + 1) << ValueToString(iter->second, iter->first);
				iter++;
			}
			cout << endl;
		}
		iterData += strip[i];	
		cout << endl;
	}
}

void DBTableTxt::WriteDBTable(string tabName) {
	ofstream out(tabName);

	if (!out.is_open()) {
		cout << "Cannot open file: " << tabName << " for reading\n";
		return;
	}

	out << GetTableName() << "|" << GetPrimaryKey() << endl;
	
	Header header = GetHeader();

	size_t i = 0;
	for (const auto& a : header) 
		out << a.second.colName << "|" << TypeName(a.second.colType) << "|" << a.second.length << (i++ < header.size() - 1 ? "|":"\n");

	for (const auto& row : data_) {
		i = 0;
		for (const auto& a : row) {
			out << ValueToString(a.second, a.first) << (i++ < row.size() - 1 ? "|" : "\n");
		}
	}	
}

int DBTableTxt::GetSize() {
	return data_.size();
}

DBType DBTableTxt::GetType(const char* columnName) {
	return columnHeaders_[columnName].colType;
}

Row DBTableTxt::operator[](int ind) {
	return data_[ind];
}

void DBTableTxt::SetFileName(string path) {
	fileName_ = path;
}

void DBTableTxt::SetTableName(string tName) {
	tableName_ = tName;
}

void DBTableTxt::SetPrimaryKey(string key) {
	primaryKey_ = key;
}

string DBTableTxt::GetFileName() {
	return fileName_;
}

string DBTableTxt::GetTableName() {
	return tableName_;
}

Header DBTableTxt::GetHeader() {
	return columnHeaders_;
}

void DBTableTxt::SetHeader(Header & hdr) {
	columnHeaders_.clear();
	columnHeaders_.insert(hdr.begin(), hdr.end());
}

Row DBTableTxt::GetRow(int index) {
	return data_[index];
}

void DBTableTxt::AddRow(Row row, int index) {
	data_.emplace(data_.begin() + index, row);
}

void DBTableTxt::WriteTableBin (string fileName){ //write into binary file from DBTableTxt
	ofstream fout;
	fout.open (fileName.c_str(), ios::binary|ios::out);
	if (!fout.is_open()){
		cout <<"File cannot be opened"<<fileName<<endl;
		system ("pause");
		return;
	}

	Header::iterator iterHeader;
	Row::iterator iterRow;
	char buf [80];

	strcpy_s (buf, 80, tableName_.c_str());
	int len = LENGTH;
	fout.write ((char*)&len, 4); //write the maximum length of the table name
	fout.write (buf, len); //write the table name

	strcpy_s (buf, 80, primaryKey_.c_str());
	fout.write ((char*)&len, 4); //write the maximum length of the primary key
	fout.write (buf, len); //write the primary key

	int nHeaders = columnHeaders_.size ();
	fout.write ((char*)&nHeaders, 4); //write the number of headers
	int size = sizeof (ColumnDesc);
	for (iterHeader = columnHeaders_.begin(); iterHeader != columnHeaders_.end(); iterHeader++){
		fout.write ((char*)&(iterHeader->second), size); //write the struct "columnDesc" for each header
	}

	int nRows = data_.size();
	fout.write ((char*)&nRows, 4); //write the number of data row
	for (int i=0; i<nRows; i++){

		for (iterRow = data_[i].begin(); iterRow != data_[i].end(); iterRow++){
			size = GetByte (columnHeaders_[iterRow->first].colType); 
			fout.write ((char*)(iterRow->second), size); //write void* for each data
		}

	}
}

void DBTableTxt::ReadTableBin (string fileName){ //read from binary file
	ifstream fin;
	fin.open (fileName.c_str(), ios::binary|ios::in);
	if (!fin.is_open()){
		cout <<"File cannot be opened\n";
		system ("pause");
		return;
	}

	int len;
	char buf[80];
	fin.read ((char*)&len, 4); //read 4 bite = the number of bytes to read for the table name
	fin.read ((char*)buf, len); //read table name
	if(len>79){
		cout<<"Error: length of table name "<<fileName<<endl;
		return;
	}
	buf[len]='\0';
	tableName_=buf;

	fin.read ((char*)&len, 4); //read 4 bite = the number of bytes to read for the the primaty key
	fin.read ((char*)buf, len);
	if(len>79){
		cout<<"Error: length of primary key "<<fileName<<endl;
		return;
	}
	buf[len]='\0';
	primaryKey_=buf;
	
	fin.read ((char*)&len, 4); //read 4 bite = the number of headers
	ColumnDesc bufHeader;
	for (int i=0; i<len; i++){
		fin.read ((char*)&bufHeader, sizeof (ColumnDesc)); //read struct "columnDesc" for each header
		columnHeaders_[bufHeader.colName] = bufHeader;
	}

	fin.read ((char*)&len, 4); //read 4 bite = the number of data row
	auto iter = columnHeaders_.begin();
	Row bufRow;
	for (int i=0; i<len; i++){

		for (iter=columnHeaders_.begin(); iter!=columnHeaders_.end(); iter++){
			void* tmp = GetValue (iter->second.colType);
			fin.read ((char*)tmp, GetByte (iter->second.colType)); //read void* for each data
			bufRow[iter->first] = tmp;
		}

		data_.push_back (bufRow);
	}
}

// <----------------------------------------- DBTableSet class ---------------------------------->

void DBTableSet::WriteDB() {
	for (const auto& dbTable : db_) {
		dbTable.second->WriteDBTable(dbTable.second->GetFileName());
		cout << "Table: " << dbTable.first << " was successfully written" << endl;
	}
}

void DBTableSet::SetDBName(string name) {
	dbSetName_ = name;
}

int DBTableSet::ReadDB() {
	for (const auto& dbTable : db_) {
		dbTable.second->ReadDBTable(dbTable.second->GetFileName());
		cout << "Table: " << dbTable.first << " was successfully read" << endl;
	}
	return 0;
}
	
void DBTableSet::PrintDB(int numcol) {
	for (const auto& dbTable : db_) {
		dbTable.second->PrintTable(numcol);
		cout << "\n\n";
	}
}

unique_ptr<DBTableTxt>& DBTableSet::operator[](string tableName) {
	return db_[tableName];
}
}