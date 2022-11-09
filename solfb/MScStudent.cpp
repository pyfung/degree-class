#include "Module.h"
#include "Student.h"

MScStudent::MScStudent(const string& uid) : Student(uid), mscCredits_(0) {}

bool MScStudent::addModule(string moduleCode, float mark) {

	if (MCT.find(moduleCode) == MCT.end()) return false;
	if (marks_.find(moduleCode) != marks_.end()) return false;
	if (moduleCode[2] != '7') return false;

	int credits = MCT.at(moduleCode);
	if (mscCredits_ + credits > MSC_YEAR_CREDIT) return false;

	mscCredits_ += credits;
	marks_[moduleCode] = mark;
	return true;
}

float MScStudent::cwa() const {

	if (mscCredits_ == 0) return 0;

	float totalWeightedMarks = 0.0;

	for(const auto& kv : marks_)
		totalWeightedMarks += MCT.at(kv.first) * kv.second;

	return totalWeightedMarks / mscCredits_;
}

string MScStudent::calcDegClass() const {

	if (mscCredits_ != MSC_YEAR_CREDIT) return "INSUFFICIENT CREDITS";

	int creditsA = 0, creditsAB = 0, creditsABC = 0; // taught part only
	int creditsD = 0, creditsF = 0; // incl. project (doesn't matter actually)
	float projMark = 0; // project mark

	for(const auto& kv : marks_) {

		string moduleCode = kv.first;
		int cred = MCT.at(moduleCode);
		float mark = kv.second;

		// 60-credit module is proj, everything else is taught
		if (cred == 60) projMark = mark;
		else {
			if (mark >= 69.5) creditsA += cred;
			if (mark >= 59.5) creditsAB += cred;
			if (mark >= 49.5) creditsABC += cred;
			else if (mark >= 39.5) creditsD += cred;
		}
		if (mark < 39.5) creditsF += cred;
	}

	float ocwa = cwa();

	if (creditsF > 0) return "FAIL";
	else if (projMark >= 69.5 && ( ocwa >= 69.5 || creditsA >= 60 )
		&& creditsD == 0) return "DISTINCTION";
	else if (projMark >= 59.5 && ( ocwa >= 59.5 || creditsAB >= 60 )
		&& creditsD <= 15) return "MERIT";
	else if (projMark >= 49.5 && ( ocwa >= 49.5 || creditsABC >= 90 )
		&& creditsD <= 30) return "PASS";
	else return "FAIL";
}
