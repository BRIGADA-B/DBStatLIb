# СУБД DBStatlib

## Прогресс разработки

Завершенность классов:

- DBDate - 100%
- DBTableTxt - 99%
- DBTableSet - 100%

Незаконченные / неизвестные глобальные функции:

- `string ignoreBlanc(const string str);`
- `void* GetValue(string value, string columnName, Header hdr);`
- `void* SetValue(string value, string columnName, Header hdr);`
- `bool comparator(DBType type, void *obj1, Condition condition, void *obj);`
- `string GetTabNameFromPath(string path);`

Неизвестные функции в DBTableTxt:

- `vector<int> IndexOfRecord(void* keyValue, string keyColumnName);`
- `Row CreateRow();` 
