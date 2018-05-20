#include "DBTableTxt.h"
#include "utils.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <assert.h>
#include <iomanip>
#include <math.h>
#include <algorithm>
#include "DBDate.h"
#include <iterator>

namespace dbmanager {

	DBTableTxt::~DBTableTxt() {
		for (auto& rows : data_) {
			for (auto& row : *rows) {
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

	void DBTableTxt::ReadDBTable(const string& fileName)
	{
		ifstream in(fileName);

		if (!in.is_open()) {
			cout << "File cannot be opened: " << fileName << endl;
			return;
		}

		map<int, string> columnNameByIndex;

		Header header;
		std::shared_ptr<Row> row( new Row );
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
					row->operator[](columnNameByIndex[j]) = readAnyType(tmpElement, header[columnNameByIndex[j]].colType);
					
					
					if (!row->operator[](columnNameByIndex[j])) {
						cout << "cannot read column data: " << columnNameByIndex[j] << "line: " << i - 1;
					}
				}
				CreateRow();
				AddRow(row, i - 2);
			}
		}
		SetHeader(header);
		in.close();
	}

	void DBTableTxt::CreateMaket(map <int, int> &strip, int screenWidth) {  // makes form to print the table
		Header hdr = GetHeader();

		int count = 0, wide = 0, k = 1;

		for (const auto& a : hdr) {
			wide += a.second.length;
			if (wide > screenWidth) {
				strip[k] = count;
				k++;
				count = 0;
				wide = a.second.length;
			}
			count++;
		}
		strip[k] = count;
	}

	void DBTableTxt::WriteDBTable(const string& fileName)
	{
		ofstream out(fileName, ios_base::trunc);
		if (!out.is_open()) {
			cout << "Cannot open file: " << fileName << " for reading\n";
			return;
		}

		out << GetTableName() << "|" << GetPrimaryKey() << endl;

		Header header = GetHeader();

		size_t i = 0;
		for (const auto& a : header)
			out << a.second.colName << "|" << TypeName(a.second.colType) << "|" << a.second.length << (i++ < header.size() - 1 ? "|" : "\n");

		for (const auto& row : data_) {
			i = 0;
			for (const auto& a : *row) {
				out << ValueToString(a.second, a.first) << (i++ < row->size() - 1 ? "|" : "\n");
			}
		}

		out.close();
	}

	void DBTableTxt::PrintDBTable(const int screenWidth)
	{
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

		map <int, int> strip;
		CreateMaket(strip, screenWidth);

		auto iterHeaderMain = header.begin();
		auto iterHeader = iterHeaderMain;
		int iterData = 0;

		for (int i = 1; i <= strip.size(); i++) {
			// prints column header
			iterHeader = iterHeaderMain;

			for (int count = 0; count<strip[i]; count++) {  // prints column name
				cout << setw(iterHeader->second.length + 1) << iterHeader->second.colName;
				iterHeader++;
			}
			cout << endl;

			iterHeader = iterHeaderMain;

			for (int count = 0; count < strip[i]; count++) {  // prints data types of column 
				cout << setw(iterHeader->second.length + 1) << TypeName(iterHeader->second.colType);
				iterHeader++;
			}
			cout << endl;

			iterHeader = iterHeaderMain;

			for (int count = 0; count < strip[i]; count++) {
				iterHeaderMain++;
			}

			// prints column data

			for (int z = 0; z < GetSize(); z++) {
				auto iter = data_[z]->begin();
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

	void DBTableTxt::DeleteRow(size_t index)
	{

	}

	void DBTableTxt::CreateRow()
	{	
		// Empty row
		data_.emplace_back();
	}

	void DBTableTxt::AddRow(const std::shared_ptr<Row>& row, int index)
	{
		data_[index] = row;
	}

	std::shared_ptr<Row> DBTableTxt::GetRow(size_t index)
	{
		return data_[index];
	}

	Row& DBTableTxt::operator[](size_t index)
	{
		return *data_[index];
	}

	vector<std::shared_ptr<Row>> DBTableTxt::Select(std::string columnName, Condition cond, void * value)
	{

		vector<std::shared_ptr<Row>> rows;
		for (const auto& row : data_) {

			auto first = ValueToString(value, columnName);
			auto second = ValueToString(row->operator[](columnName), columnName);

			if (first == second)
				rows.push_back(row);
		}

		return rows;
	}

	void DBTableTxt::Clear()
	{
		if (!data_.empty()) {
			data_.clear();
			WriteDBTable(GetFileName());
		}
	}

	void DBTableTxt::WriteTableBin(string fileName) { //write into binary file from DBTableTxt
		ofstream fout;
		fout.open(fileName.c_str(), ios::binary | ios::out);
		if (!fout.is_open()) {
			cout << "File cannot be opened" << fileName << endl;
			system("pause");
			return;
		}

		Header::iterator iterHeader;
		Row::iterator iterRow;

		char buf[80];

		strcpy_s(buf, 80, tabName_.c_str());
		int len = LENGTH;
		fout.write((char*)&len, 4); //write the maximum length of the table name
		fout.write(buf, len); //write the table name

		strcpy_s(buf, 80, primaryKey_.c_str());
		fout.write((char*)&len, 4); //write the maximum length of the primary key
		fout.write(buf, len); //write the primary key

		int nHeaders = header_.size();
		fout.write((char*)&nHeaders, 4); //write the number of headers

		int size = sizeof(ColumnDesc);
		for (iterHeader = header_.begin(); iterHeader != header_.end(); iterHeader++) {
			fout.write((char*)&(iterHeader->second), size); //write the struct "columnDesc" for each header
		}

		int nRows = data_.size();
		fout.write((char*)&nRows, 4); //write the number of data row
		for (int i = 0; i<nRows; i++) {

			for (iterRow = data_[i]->begin(); iterRow != data_[i]->end(); iterRow++) {
				size = GetByte(header_[iterRow->first].colType);
				fout.write((char*)(iterRow->second), size); //write void* for each data
			}

		}
	}

	void DBTableTxt::ReadTableBin(string fileName) { //read from binary file
		ifstream fin;
		fin.open(fileName.c_str(), ios::binary | ios::in);
		if (!fin.is_open()) {
			cout << "File cannot be opened\n";
			system("pause");
			return;
		}

		int len;
		char buf[80];
		fin.read((char*)&len, 4); //read 4 bite = the number of bytes to read for the table name
		fin.read((char*)buf, len); //read table name
		if (len>79) {
			cout << "Error: length of table name " << fileName << endl;
			return;
		}
		buf[len] = '\0';
		tabName_ = buf;

		fin.read((char*)&len, 4); //read 4 bite = the number of bytes to read for the the primaty key
		fin.read((char*)buf, len);
		if (len>79) {
			cout << "Error: length of primary key " << fileName << endl;
			return;
		}
		buf[len] = '\0';
		primaryKey_ = buf;

		fin.read((char*)&len, 4); //read 4 bite = the number of headers
		ColumnDesc bufHeader;
		for (int i = 0; i<len; i++) {
			fin.read((char*)&bufHeader, sizeof(ColumnDesc)); //read struct "columnDesc" for each header
			header_[bufHeader.colName] = bufHeader;
		}

		fin.read((char*)&len, 4); //read 4 bite = the number of data row
		auto iter = header_.begin();
		Row* bufRow;
		for (int i = 0; i<len; i++) {

			for (iter = header_.begin(); iter != header_.end(); iter++) {
				void* tmp = GetValue(iter->second.colType);
				fin.read((char*)tmp, GetByte(iter->second.colType)); //read void* for each data
				bufRow->operator[](iter->first) = tmp;
			}

			data_.emplace_back(bufRow);
		}
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

	int DBTableTxt::GetSize() const{
		return data_.size();
	}

	DBType DBTableTxt::GetType(const char* columnName) {
		return header_[columnName].colType;
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
			res = new string(val);
			break;
		case Date:
			res = new DBDate(val);
			break;
		case NoType:
			res = new bool(stoi(val));  // undefined behavior
		}

		return res;
	}


}