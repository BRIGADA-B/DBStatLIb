#include "DBDate.h"
#include <vector>
#include <sstream>

namespace dbmanager {
	
	string DateToStr(DBDate & date) {  // turns it all into a beatiful string
		string res;
		res += to_string(date.GetDay());
		res += ".";
		res += to_string(date.GetMonth());
		res += ".";
		res += to_string(date.GetYear());
		return res;
	}

	ostream & operator<<(ostream & out, DBDate & date) {  // makes "<<" work fot DBDate
		cout << date.day_ << "." << date.month_ << "." << date.year_;
		return out;
	}

	DBDate::DBDate(string date) {  // constructor
		string buf;
		vector<int> data(3);
		stringstream ss(date);
		int i = 0;
		while (getline(ss, buf, '.')) {
			data[i++] = stoi(buf);  // stoi = string to int
		}
		SetDay(data[0]);  //
		SetMonth(data[1]);
		SetYear(data[2]);
	}

	bool DBDate::IsLeapYear(int y) {  // if the year is leap
		if ((y % 4 == 0 && y % 100 != 0) || (y % 400 == 0)) return 1;
		return 0;
	}

	int DBDate::GetDaysInMonth(int m, int y) {  // amount of days in the month
		switch (m) {
		case 1: case 3: case 5: case 7: case 8: case 10: case 12: return 31;
		case 2:
			return 28 + IsLeapYear(y);
			break;
		default: return 30;
		}
	}

	int DBDate::GetDaysInYear(int year) {  // amount of days in the year
		return 365 + IsLeapYear(year);
	}

	void DBDate::Set(int d, int m, int y) {
		SetDay(d);
		SetMonth(m);
		SetYear(y);
	}

	int DBDate::operator- (DBDate& date) {  // substract one date from another in days
		DBDate buf(day_, month_, year_);

		if (buf == date) return 0;

		DBDate dateL, dateR;

		if (buf > date) {
			dateL.Set(date.day_, date.month_, date.year_);
			dateR.Set(day_, month_, year_);
		}
		else {
			dateR.Set(date.day_, date.month_, date.year_);
			dateL.Set(day_, month_, year_);
		}

		int countDays = 0;

		if (dateL.year_ != dateR.year_) {
			for (int i = dateL.year_ + 1; i < dateR.year_; i++) {
				countDays += GetDaysInYear(i);
			}
			for (int i = dateL.month_ + 1; i <= 12; i++) {
				countDays += GetDaysInMonth(i, dateL.year_);
			}

			countDays += GetDaysInMonth(dateL.month_, dateL.year_) - dateL.day_;

			for (int i = 1; i < dateR.month_; i++) {
				countDays += GetDaysInMonth(i, dateR.year_);
			}

			countDays += dateR.day_;
		}
		else {
			if (dateL.month_ == dateR.month_) {
				if (dateL.day_ != dateR.day_)
					countDays = dateR.day_ - dateL.day_ - 1;
			}
			else {
				for (int i = dateL.month_ + 1; i < dateR.month_; i++) {
					countDays += GetDaysInMonth(i, dateL.year_);
				}

				countDays += GetDaysInMonth(dateL.month_, dateL.year_) - dateL.day_;

				countDays += dateR.day_;
			}
		}
		return countDays;
	}

	bool DBDate::operator== (DBDate& date) {  // if dates are the same
		if (day_ == date.day_ && month_ == date.month_ && year_ == date.year_)
			return true;
		else
			return false;
	}

	bool DBDate::operator!= (DBDate& date) {  // if dates are not the same
		if (day_ != date.day_ || month_ != date.month_ || year_ != date.year_)
			return true;
		else
			return false;
	}

	bool DBDate::operator< (DBDate& date) {  // one date is earlier than the other
		if (year_ < date.year_)
			return true;
		else {
			if (year_ > date.year_)
				return false;
			else {
				if (month_ < date.month_)
					return true;
				else {
					if (month_ > date.month_)
						return false;
					else {
						if (day_ < date.day_)
							return true;
						else
							return false;
					}
				}
			}
		}
	}

	bool DBDate::operator<= (DBDate& date) {  // one date is earlier than the other or the same
		if (year_ < date.year_)
			return true;
		else {
			if (year_ > date.year_)
				return false;
			else {
				if (month_ < date.month_)
					return true;
				else {
					if (month_ > date.month_)
						return false;
					else {
						if (day_ <= date.day_)
							return true;
						else
							return false;
					}
				}
			}
		}
	}

	bool DBDate::operator> (DBDate& date) {  // one date is later than the other
		if (year_ > date.year_)
			return true;
		else {
			if (year_ < date.year_)
				return false;
			else {
				if (month_ > date.month_)
					return true;
				else {
					if (month_ < date.month_)
						return false;
					else {
						if (day_ > date.day_)
							return true;
						else
							return false;
					}
				}
			}
		}
	}

	bool DBDate::operator>= (DBDate& date) {  // one date is later than the other or the same
		if (year_ > date.year_)
			return true;
		else {
			if (year_ < date.year_)
				return false;
			else {
				if (month_ > date.month_)
					return true;
				else {
					if (month_ < date.month_)
						return false;
					else {
						if (day_ >= date.day_)
							return true;
						else
							return false;
					}
				}
			}
		}
	}

	DBDate& DBDate::operator+= (int days) {  // adds days to the date
		while (days != 0) {
			if (day_ + days < GetDaysInMonth(month_, year_)) {
				day_ += days;
				days = 0;
			}
			else {
				days -= GetDaysInMonth(month_, year_) - day_ + 1;
				day_ = 1;
				month_ += 1;

				if (month_ > 12) {
					month_ = 1;
					year_ += 1;
				}
			}
		}
		return *this;
	}

	DBDate& DBDate::operator-= (int days) {  // substract days from the date
		while (days != 0) {
			if (day_ - days > 0) {
				day_ -= days;
				days = 0;
			}
			else {
				days -= day_;
				month_--;
				if (month_ <= 0) {
					month_ = 12;
					year_--;
				}
				day_ = GetDaysInMonth(month_, year_);
			}
		}
		return *this;
	}

	int DBDate::GetDay() {
		return day_;
	}

	int DBDate::GetMonth() {
		return month_;
	}

	int DBDate::GetYear() {
		return year_;
	}

	void DBDate::SetDay(int d) {
		day_ = d;
	}

	void DBDate::SetMonth(int m) {
		month_ = m;
	}

	void DBDate::SetYear(int y) {
		year_ = y;
	}

}