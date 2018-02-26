#include<dbmsLib_v1.h>
#include<iostream>

using namespace dbmsLib;
int main() {
	setlocale(LC_ALL, "Russian");
	string pathToDb = "C:\\Users\\Влад\\source\\repos\\DBStatLIb\\LibraryTxt\\Students.csv";	
	DBTableTxt table, tableTest;

	ReadDBTable1(table, pathToDb);

	table.PrintTable(29);
	
	PrintTable1(table, 80);

	char c;
	cin >> c;
	return 0;
}