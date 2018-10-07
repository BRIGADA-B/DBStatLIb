#include "Progress.h"
#include "Session.h"
#include "Student.h"
#include "Exam.h"
#include "Group.h"

int dbmanager::Progress::GroupAvgMark(const std::string & groupName)
{
	return 0;
}

int dbmanager::Progress::ExamAvgMark(const std::string & examName)
{
	return 0;
}

void dbmanager::Progress::AddStudent()
{
	std::cout << "Enter student Name, Surname, Middlename:" << std::endl;

}

double dbmanager::Progress::StudentAvgMark(const std::string & name, const std::string & sname, const std::string & mname)
{
	const auto studentsByName = Student::GetBy(name, "Firstname");

	if (studentsByName.empty()) {
		std::cout << "There is no such Student with Name: " << name;
		return 0;
	}

	Student specificStudent;
	bool studentIsFind = false;
	for (const auto& student : studentsByName) {
		if (student.GetSurName() == sname && student.GetMiddleName() == mname) {
			specificStudent = student;
			studentIsFind = true;
		}
	}

	if (!studentIsFind) {
		std::cout << "There is no such Student with Name: " << name
			<< " Surname: " << sname << " Middlename: " << mname << "\n";
		return 0;
	}

	auto sessionByStudentId = Session::GetBy(specificStudent.GetId(), "StudentID");
	if (!sessionByStudentId.empty()) {

		double avg;
		int count = 0;
		int sum = 0;
		for (const auto& el : sessionByStudentId) {
			sum += el.GetExamMark();
			count++;
		}
		return (sum * (1.0) / count);
	}

	std::cout << "Student doesn't pass with Name: " << name
		<< " Surname: " << sname << " Middlename: " << mname << "\n";

	return 0;
}
