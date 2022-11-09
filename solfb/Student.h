#ifndef STUDENT_H_
#define STUDENT_H_

#include <iostream>
#include <string>
#include <map>
using std::istream;
using std::ostream;
using std::string;
using std::map;

const int MAX_MODULES = 20; // should you need to use something like this
const int BSC_YEAR_CREDIT = 120;
const int MSC_YEAR_CREDIT = 180;

class Student {
public:
	// Constructor, with student's userid as argument
	Student(const string& uid);

	// If you need non-default versions of destructors, copy constructors
	// etc. please define yourself. Here I assume the default versions
	// are ok. You will not be tested on copy constructing/assigning.

	// Add this module to the student, with the given mark.
	// If moduleCode does not exist in the MCT table,
	// or if the module is of the wrong year group for this student,
	// or if the student already have this module,
	// or if adding this module exceeds the total credits of this year,
	// do nothing and return false. Otherwise return true.
	virtual bool addModule(string moduleCode, float mark) = 0;

	// Update the mark of this module.
	// If moduleCode does not appear in the MCT table,
	// or if the student have not already added this module,
	// do nothing and return false. Otherwise return true.
	bool updateMark(string moduleCode, float mark);

	// Returns the CWA of the student taking all the modules added so
	// far into account.
	// For BSc students it is a weighted average of Y2 and Y3 CWAs.
	// For MSc students it is a weighted average of all modules.
	// It should still calculate even if not a whole year worth of
	// modules have been added.
	// If no modules have been added so far, return 0.
	virtual float cwa() const = 0;

	// Returns a string which is one of the degree classification
	// results (see webpage for details).
	// If insufficient credits have been entered, return
	// "INSUFFICIENT CREDITS".
	virtual string calcDegClass() const = 0;

	// TODO: add any protected/private member variables
protected:
	string id_;
	map<string,float> marks_;

// The input stream operator, that reads module code and marks from the
// input stream and add it to the student as done by addModule().
// In situations where addModule() would have returned false, do not add
// and quietly move on to the next module.
friend istream& operator>>(istream& is, Student& student);

// The output stream operator, printing uid, CWA and degree class info
// of the student as specified in the webpage.
friend ostream& operator<<(ostream& os, const Student& student);
};

class BScStudent : public Student {
public:
	BScStudent(const string& uid);

	bool addModule(string moduleCode, float mark) override;

	// CWA for Y2 and Y3 respectively.
	// Same rules as Student::cwa() regarding not having a whole year's
	// worth of modules applies here.
	float y2cwa() const;
	float y3cwa() const;

	// TODO: add any protected/private member variables
protected:
	int y2Credits_; // number of Y2 credits currently added
	int y3Credits_; // same for Y3
};

class BScStudentOld : public BScStudent {
public:
	BScStudentOld(const string& uid);

	float cwa() const override;
	string calcDegClass() const override;

	// TODO: add any protected/private member variables
};

class BScStudentNew : public BScStudent {
public:
	BScStudentNew(const string& uid);

	float cwa() const override;
	string calcDegClass() const override;

	// TODO: add any protected/private member variables
};

class MScStudent : public Student {
public:
	MScStudent(const string& uid);

	bool addModule(string moduleCode, float mark) override;
	float cwa() const override;
	string calcDegClass() const override;

	// TODO: add any protected/private member variables
private:
	int mscCredits_;
};

#endif
