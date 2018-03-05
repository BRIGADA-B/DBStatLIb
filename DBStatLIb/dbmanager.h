#pragma once
#ifndef _DB_MANAGER_H_
#define _DB_MANAGER_H_

#include<string>
#include<iostream>
#include<map>
#include<vector>

using namespace std;

namespace dbmanager {
	class DBDate
	{

		static const int arrDays_[13];
		friend string DateToStr(DBDate& date);
		friend ostream& operator<<(ostream& out, DBDate& date);
		int day_, month_, year_;
	public:
		DBDate(string date);//формат строки: dd.mm.yyyy
		DBDate(int d, int m, int y);
		DBDate() :day_(0), month_(0), year_(0) {};//конструктор по умолчанию
		DBDate(DBDate& dat) :day_(dat.day_), month_(dat.month_), year_(dat.year_) {}
		int GetDay();
		int GetMonth();
		int GetYear();
		bool IsLeapYear(int year); //год высокосный?
		int GetDaysInMonth(int month, int year);//Количество дней в месяце
		int DaysInCurYear();//Количество дней от начала года до текущей даты
		bool operator==(DBDate& date);
		bool operator<(DBDate& date);
		bool operator>(DBDate& date);
		bool operator<= (DBDate& date);
		bool operator>= (DBDate& date);
		bool operator!= (DBDate& date);
		DBDate& operator+=(int days);//Прибавляет к текущей дате days дней
		DBDate& operator-=(int days);//Вычитает из текущей даты days дней
		int operator-(DBDate& date);	//Количество дней между текущей датой и date
										//Если текущая дата > date, результат < 0.
	};
	//==================== Класс "Таблица макета СУБД" ===========================
	//--------DBType-перечисление типов полей таблиц БД------ 
	enum DBType {
		NoType,
		Int32,
		Double,
		String,
		Date
	};
	enum Condition { Undefined, Equal, NotEqual, Less, Greater, LessOrEqual, GreaterOrEqual };
	const int LENGTH = 24;//длина имени таблицы и имени столбца.
						  //ColumnDesc - описание данных в столбце таблицы 
						  //данные типа string имеют одинаковую длину (length) внутри одного столбца, 
						  //но в разных столбцах их максимальный размер может отличаться
	struct ColumnDesc {
		char colName[LENGTH];//имя столбца
		DBType colType;//тип данных в столбце таблицы
		int length; //максимальное число символов, допустимое 
					//для представления данных в столбце
	};
	struct Strip {//полоса распечатки таблицы
		int nField;//число полей 
		int* fieldWidth;//ширина полей в полосе (массив)
	};
	typedef map<string, void*> Row;
	typedef map<string, ColumnDesc> Header;

	string GetTabNameFromPath(string path);
	string ignoreBlanc(const string str);
	void* GetValue(string value, string columnName, Header hdr);
	void* SetValue(string value, string columnName, Header hdr);
	bool comparator(DBType type, void *obj1, Condition condition, void *obj);
	int GetLength(ColumnDesc colDesc);

	//------------------- класс DBTableTxt ----------------------
	class DBTableTxt {

		Header columnHeaders_;
		string tableName_;
		string primaryKey_;
		vector<Row> data_;
		string fileName_;
	public:
		DBTableTxt() {}
		DBTableTxt(string tabName);
		DBTableTxt(string tabName, Header hdr, string primKey);
		const char* TypeName(DBType type);
		~DBTableTxt() {}
		vector<int> IndexOfRecord(void* keyValue, string keyColumnName);
		string valueToString(Row& row, string columnName);
		void ReadDBTable(string tabName);//tabName=path+tableName
		void PrintTable(int screenWidth);
		void WriteDBTable(string tabName);//tabName=path+tableName	
		int GetSize();
		DBType GetType(char* columnName);
		Row operator[](int ind);
		void SetFileName(string path);
		void SetTableName(string tName);
		void SetPrimaryKey(string key);
		string GetFileName();
		string GetTableName();
		string GetPrimaryKey() { return primaryKey_; }
		Header GetHeader();
		void SetHeader(Header& hdr);
		Row CreateRow();
		Row GetRow(int index);
		void AddRow(Row row, int index);
		//Макет распечатки таблицы:
		//screenWidth - ширина экрана (входной параметр)
		//nStrip - число полос в распечатке (выходной параметр)
		//strips[nStrip] - описание полос таблицы: 
		//число столбцов и ширина каждого столбца в полосе (выходной параметр)
	};
	//======================== класс DBTableSet =====================
	class DBTableSet
	{
	private:
		string dbName_;
		map<string, DBTableTxt*> db_;
	public:
		DBTableSet() {};
		DBTableSet(string name);
		int ReadDB();
		void PrintDB(int numcol);
		void WriteDB();
		string GetDBName() { return dbName_; }
		DBTableTxt* operator[](string tableName);
	};

}

#endif // !