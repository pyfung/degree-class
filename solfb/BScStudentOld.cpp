#include "Module.h"
#include "Student.h"

BScStudentOld::BScStudentOld(const string& uid) : BScStudent(uid) {}

float BScStudentOld::cwa() const {
	return y2cwa()*0.4 + y3cwa()*0.6;
}

string BScStudentOld::calcDegClass() const {

	if (y2Credits_ != BSC_YEAR_CREDIT) return "INSUFFICIENT CREDITS";
	if (y3Credits_ != BSC_YEAR_CREDIT) return "INSUFFICIENT CREDITS";

	float ocwa = cwa(); // local var to save computation

	int credits70 = 0, credits60 = 0, credits50 = 0;
	int credits68 = 0, credits58 = 0, credits48 = 0;
	int creditsFail = 0;

	// number of credits in each range
	for(const auto& kv : marks_) {

		string moduleCode = kv.first;
		int cred = MCT.at(moduleCode);
		float mark = kv.second;
		if (mark >= 69.5) credits70 += cred;
		if (mark >= 67.5) credits68 += cred;
		if (mark >= 59.5) credits60 += cred;
		if (mark >= 57.5) credits58 += cred;
		if (mark >= 49.5) credits50 += cred;
		if (mark >= 47.5) credits48 += cred;

		// note: depends on cwa re compensation
		if (mark < 34.5) creditsFail += cred;
		else if (mark < 39.5 && moduleCode[2] == '2'
			&& y2cwa() < 39.5) creditsFail += cred;
		else if (mark < 39.5 && moduleCode[2] == '3'
			&& y3cwa() < 39.5) creditsFail += cred;
	}

	// deg class
	if (ocwa < 34.5) return "FAIL";
	else if (creditsFail >= 50) return "FAIL";
	else if (ocwa >= 69.5)
		return "FIRST CLASS";
	else if (ocwa >= 66.5 && credits70 >= 120 && creditsFail < 40)
		return "FIRST CLASS";
	else if (ocwa >= 66.5 && credits70 >= 90 && credits68 >= 120 && creditsFail < 40)
		return "BORDERLINE FIRST CLASS";
	else if (ocwa >= 66.5 && credits70 >= 120 && creditsFail >= 40)
		return "UPPER SECOND CLASS";
	else if (ocwa >= 59.5)
		return "UPPER SECOND CLASS";
	else if (ocwa >= 56.5 && credits60 >= 120 && creditsFail < 40)
		return "UPPER SECOND CLASS";
	else if (ocwa >= 56.5 && credits60 >= 90 && credits58 >= 120 && creditsFail < 40)
		return "BORDERLINE UPPER SECOND CLASS";
	else if (ocwa >= 56.5 && credits60 >= 120 && creditsFail >= 40)
		return "LOWER SECOND CLASS";
	else if (ocwa >= 49.5)
		return "LOWER SECOND CLASS";
	else if (ocwa >= 46.5 && credits50 >= 120 && creditsFail < 40)
		return "LOWER SECOND CLASS";
	else if (ocwa >= 46.5 && credits50 >= 90 && credits48 >= 120 && creditsFail < 40)
		return "BORDERLINE LOWER SECOND CLASS";
	else if (ocwa >= 46.5 && credits50 >= 120 && creditsFail >= 40)
		return "THIRD CLASS";
	else if (ocwa >= 39.5)
		return "THIRD CLASS";
	else return "PASS";
}
