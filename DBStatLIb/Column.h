#pragma once
#include "utils.h"

namespace dbmanager {
	
	template<class T>
	class Column
	{
	public:
		Column() : dbtype_(DBType::NoType), isValueEmpty_(true) { }
		~Column() {}

		void SetType(DBType dbtype);
		void SetValue(const T& value);
		void SetLength(int length);
		void SetColumnName(const std::string& name);

		DBType dbtype() const;
		T GetValue() const;
		int GetLength() const;
		std::string GetColumnName() const;

		bool IsValueEmpty();

		operator void*() {
			return static_cast<void*>(new T(value_));
		}

	private:
		DBType dbtype_;
		T value_;
		bool isValueEmpty_;
		int length_;
		std::string columnName_;
	};

	template<class T>
	void Column<T>::SetType(DBType dbtype)
	{
		dbtype_ = dbtype;
	}

	template<class T>
	void Column<T>::SetValue(const T & value)
	{
		value_ = value;
		isValueEmpty_ = false;
	}

	template<class T>
	void Column<T>::SetLength(int length)
	{
		length_ = length;
	}

	template<class T>
	void Column<T>::SetColumnName(const std::string & name)
	{
		columnName_ = name;
	}

	template<class T>
	DBType Column<T>::dbtype() const
	{
		return dbType_;
	}

	template<class T>
	T Column<T>::GetValue() const
	{
		return value_;
	}

	template<class T>
	int Column<T>::GetLength() const
	{
		return length_;
	}

	template<class T>
	std::string Column<T>::GetColumnName() const
	{
		return columnName_;
	}
	template<class T>
	inline bool Column<T>::IsValueEmpty()
	{
		return isValueEmpty_;
	}
};