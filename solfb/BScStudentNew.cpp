#include "Module.h"
#include "Student.h"

BScStudentNew::BScStudentNew(const string& uid) : BScStudent(uid) {}

float BScStudentNew::cwa() const {
	return y2cwa()*0.33 + y3cwa()*0.67;
}

string BScStudentNew::calcDegClass() const {

	if (y2Credits_ != BSC_YEAR_CREDIT) return "INSUFFICIENT CREDITS";
	if (y3Credits_ != BSC_YEAR_CREDIT) return "INSUFFICIENT CREDITS";

	int credits70 = 0, credits60 = 0, credits50 = 0, credits40 = 0;
	int credits68 = 0, credits58 = 0, credits48 = 0;
	int creditsFail = 0;
	int credits70Y3 = 0, credits60Y3 = 0, credits50Y3 = 0, credits40Y3 = 0;

	float ocwa = cwa();

	// num credits in each range
	for(const auto& kv : marks_) {
		string moduleCode = kv.first;
		int cred = MCT.at(moduleCode);
		float mark = kv.second;
		if (mark >= 70.0) {
			credits70 += cred;
			if (moduleCode[2] =='3') credits70Y3 += cred;
		}
		if (mark >= 68.0) credits68 += cred;
		if (mark >= 60.0) {
			credits60 += cred;
			if (moduleCode[2] =='3') credits60Y3 += cred;
		}
		if (mark >= 58.0) credits58 += cred;
		if (mark >= 50.0) {
			credits50 += cred;
			if (moduleCode[2] =='3') credits50Y3 += cred;
		}
		if (mark >= 48.0) credits48 += cred;
		if (mark >= 40.0) {
			credits40 += cred;
			if (moduleCode[2] =='3') credits40Y3 += cred;
		}
		else creditsFail += cred;
	}

	// calc deg class
	if (creditsFail > 45)
		return "FAIL";
	else if (ocwa < 35.0)
		return "FAIL";
	else if (ocwa >= 70.0 && creditsFail <= 30)
		return "FIRST CLASS";
	else if (ocwa >= 68.0 && credits70 >= 120 && credits70Y3 >= 30)
		return "FIRST CLASS";
	else if (ocwa >= 68.0 && credits70 >= 90 && credits68 >= 120 && credits70Y3 >= 30)
		return "BORDERLINE FIRST CLASS";
	else if (ocwa >= 60.0)
		return "UPPER SECOND CLASS";
	else if (ocwa >= 58.0 && credits60 >= 120 && credits60Y3 >= 30)
		return "UPPER SECOND CLASS";
	else if (ocwa >= 58.0 && credits60 >= 90 && credits58 >= 120 && credits60Y3 >= 30)
		return "BORDERLINE UPPER SECOND CLASS";
	else if (ocwa >= 50.0)
		return "LOWER SECOND CLASS";
	else if (ocwa >= 48.0 && credits50 >= 120 && credits50Y3 >= 30)
		return "LOWER SECOND CLASS";
	else if (ocwa >= 48.0 && credits50 >= 90 && credits48 >= 120 && credits50Y3 >= 30)
		return "BORDERLINE LOWER SECOND CLASS";
	else if (ocwa >= 40.0)
		return "THIRD CLASS";
	else if (ocwa >= 38.0 && credits40 >= 120 && credits40Y3 >= 30)
		return "THIRD CLASS";
	else return "PASS";
}
