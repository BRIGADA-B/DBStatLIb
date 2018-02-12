#include<dbmsLib_v1.h>
#include<iostream>

using namespace dbmsLib;
int main() {
	setlocale(LC_ALL, "Russian");	
	DBTableTxt table;
	string nul;
	ReadDBTable1(table,nul);
	table.ReadDBTable("C:\\Users\\Влад\\source\\repos\\DBStatLIb\\LibraryTxt\\Students.csv");
	table.PrintTable(80);

	char c;
	cin >> c;
	return 0;
}