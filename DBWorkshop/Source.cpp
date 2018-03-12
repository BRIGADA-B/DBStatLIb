#include<dbmanager.h>
#include<iostream>

using namespace dbmanager;
int main() {
	setlocale(LC_ALL, "Russian");	
	DBTableTxt table;
	string pathTo = "C:\\Users\\Влад\\source\\repos\\DBStatLIb\\LibraryTxt\\Students.csv";
	
	table.ReadDBTable(pathTo);
	table.PrintTable(80);
	char c;
	cin >> c;
	return 0;
}