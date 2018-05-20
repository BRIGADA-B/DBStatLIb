#pragma once

#include "utils.h"

namespace dbmanager {
	
	class Column
	{
	public:
		Column() : dbtype_(DBType::NoType), isValueEmpty_(true) { }
		
		Column(DBType type, int length, std::string name) :
			dbtype_(type), length_(length), columnName_(name) {}

		~Column() {}

		void SetType(DBType dbtype);
		void SetLength(int length);
		void SetColumnName(const std::string& name);

		DBType GetDbtype() const;
		int GetLength() const;
		std::string GetColumnName() const;

		bool IsValueEmpty();
		void SetIsValueEmpty(bool value);
	private:
		DBType dbtype_;
		bool isValueEmpty_;
		int length_;
		std::string columnName_;
	};
};