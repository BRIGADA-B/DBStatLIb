#include <dbmanager.h>
#include<iostream>

using namespace dbmanager;
int main() {
	setlocale (LC_ALL, "Russian");
	DBTableTxt table;
	table.ReadDBTable(TableChoose());
	while (true)
		{
			dbmanager::print ();
			switch (menu())
				{
					case 1: table.PrintTable(80);break;
					case 2: return 0;
					default: cout <<"please enter the numbers from 1 to 2"<<endl;break;
				}
		}
	char c;
	cin >> c;
	return 0;
}