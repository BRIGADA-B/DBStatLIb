#pragma once

#include <string>
#include <iostream>

namespace dbmanager {
	using namespace std;

	class DBDate {
		static const int arrDays_[13];
		friend string DateToStr(DBDate& date);
		friend ostream& operator<<(ostream& out, DBDate& date);
		int day_, month_, year_;
	public:
		DBDate(string date);
		DBDate(int d, int m, int y) : day_(d), month_(m), year_(y) {}
		DBDate() :day_(0), month_(0), year_(0) {};
		DBDate(DBDate& dat) :day_(dat.day_), month_(dat.month_), year_(dat.year_) {}
		int GetDay();
		int GetMonth();
		int GetYear();
		void SetDay(int day);
		void SetMonth(int month);
		void SetYear(int year);
		void Set(int d, int m, int y);
		bool IsLeapYear(int year);
		int GetDaysInMonth(int month, int year);
		int GetDaysInYear(int year);
		bool operator==(DBDate& date);
		bool operator<(DBDate& date);
		bool operator>(DBDate& date);
		bool operator<= (DBDate& date);
		bool operator>= (DBDate& date);
		bool operator!= (DBDate& date);
		DBDate& operator+=(int days);
		DBDate& operator-=(int days);
		int operator-(DBDate& date);
	};

}