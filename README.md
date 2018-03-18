# СУБД DBStatlib

## Прогресс разработки

Завершенность классов:

- DBDate - 0%
- DBTableTxt - 80%
- DBTableSet - 0%

Незаконченные / неизвестные глобальные функции:

- `string ignoreBlanc(const string str);`
- `void* GetValue(string value, string columnName, Header hdr);`
- `void* SetValue(string value, string columnName, Header hdr);`
- `bool comparator(DBType type, void *obj1, Condition condition, void *obj);`
- `int GetLength(ColumnDesc colDesc);`
- `string GetTabNameFromPath(string path);`


Внедренные функции в DBTableTxt:

1.  ReadTable
2.  WriteTable (Вывод таблицы в файл)
3.  PrintTable ( Выводит таблицы в stdout)
4.  Меню для выбора с какой DBTable работать
5.  Создание макета DBTable на основе ширины экрана

Незаконченные/неизвестные функции в DBTableTxt:

- `DBTableTxt(string tabName, Header hdr, string primKey);`
- `DBTableTxt(string tabName);`
- `DBTableTxt() {}`
- `Row operator[](int ind);`
- `vector<int> IndexOfRecord(void* keyValue, string keyColumnName);`
- `Row CreateRow();` 
