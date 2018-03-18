#include <dbmanager.h>
#include<iostream>

using namespace dbmanager;
int main() {
	setlocale (LC_ALL, "Russian");
	DBTableTxt table;
	table.ReadDBTable(TableChoose());
	while (true)
		{
			switch (Menu())
				{
					case 1: table.PrintTable(80);break;
					case 2: table.WriteDBTable (table.GetFileName ()); break;
					case 3: return 0;
					default: cout <<"please enter the numbers from 1 to 3"<<endl;break;
				}
		}
	char c;
	cin >> c;
	return 0;
}