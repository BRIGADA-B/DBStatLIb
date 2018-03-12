#include <dbmanager.h>
#include<iostream>

using namespace dbmanager;
int main() {
	setlocale (LC_ALL, "Russian");
	DBTableTxt table;
	string pathTo = "D:\\Учеба\\второй семестр\\программирование\\repository\\Project\\LibraryTxt\\Students.csv";
	table.ReadDBTable(pathTo);
	table.PrintTable(120);
	char c;
	cin >> c;
	return 0;
}