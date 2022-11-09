#include "Module.h"
#include "Student.h"

BScStudent::BScStudent(const string& uid) :
	Student(uid), y2Credits_(0), y3Credits_(0) {}

bool BScStudent::addModule(string moduleCode, float mark) {

	if (MCT.find(moduleCode) == MCT.end()) return false;
	if (marks_.find(moduleCode) != marks_.end()) return false;

	int credits = MCT.at(moduleCode);

	if (moduleCode[2] == '2') {
		if (y2Credits_ + credits > BSC_YEAR_CREDIT) return false;
		y2Credits_ += credits;
		marks_[moduleCode] = mark;
		return true;
	}
	else if (moduleCode[2] == '3') {
		if (y3Credits_ + credits > BSC_YEAR_CREDIT) return false;
		y3Credits_ += credits;
		marks_[moduleCode] = mark;
		return true;
	}
	else return false;
}

float BScStudent::y2cwa() const {

	if (y2Credits_ == 0) return 0;

	float totalWeightedMarks = 0.0;

	for(const auto& kv : marks_) {
		if ((kv.first)[2] != '2') continue;
		totalWeightedMarks += MCT.at(kv.first) * kv.second;
	}
	return totalWeightedMarks / y2Credits_;
}

float BScStudent::y3cwa() const {

	if (y3Credits_ == 0) return 0;

	float totalWeightedMarks = 0.0;

	for(const auto& kv : marks_) {
		if ((kv.first)[2] != '3') continue;
		totalWeightedMarks += MCT.at(kv.first) * kv.second;
	}
	return totalWeightedMarks / y3Credits_;
}

