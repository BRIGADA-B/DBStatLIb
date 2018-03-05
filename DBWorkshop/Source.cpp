#include<dbmanager.h>
#include<iostream>

using namespace dbmanager;
int main() {
<<<<<<< HEAD
	setlocale(LC_ALL, "Russian");
	string pathToDb = "C:\\Users\\����\\source\\repos\\DBStatLIb\\LibraryTxt\\Students.csv";	
	DBTableTxt table, tableTest;

	ReadDBTable1(table, pathToDb);

	table.PrintTable(29);
	
	PrintTable1(table, 80);
=======
>>>>>>> Добавил разделение на классы в искодниках изменение

	setlocale(LC_ALL, "Russian");	
	DBTableTxt table;
	string nul;
	//added line for example
	char c;
	cin >> c;
	return 0;
}