#include "Module.h"
#include "Student.h"

Student::Student(const string& uid) : id_(uid) {}

bool Student::updateMark(string moduleCode, float mark) {

	// actually redundant...
	//if (MCT.find(moduleCode) == MCT.end()) return false;

	if (marks_.find(moduleCode) == marks_.end()) return false;
	marks_[moduleCode] = mark;
	return true;
}

istream& operator>>(istream& is, Student& student) {

	string mc; float m;
	while(!is.eof()) {
		is >> mc >> m;
		if (is.eof()) break;
		student.addModule(mc, m);
	}
	return is;
}

ostream& operator<<(ostream& os, const Student& student) {

	os << student.id_ << "\t" << student.calcDegClass();
	return os;
}
