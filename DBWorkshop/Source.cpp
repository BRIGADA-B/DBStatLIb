#include<dbmsLib_v1.h>
#include<iostream>

using namespace dbmsLib;
int main() {
	setlocale(LC_ALL, "Russian");
	string pathToDb = "C:\\Users\\Влад\\source\\repos\\DBStatLIb\\LibraryTxt\\Students.csv";	
	DBTableTxt table, tableTest;

	ReadDBTable1(table, pathToDb);

	tableTest.ReadDBTable(pathToDb);

	table.PrintTable(80);
	tableTest.PrintTable(80);

	char c;
	cin >> c;
	return 0;
}