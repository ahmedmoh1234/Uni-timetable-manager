#pragma once
#include "Session.h"



class Course
{
private:
	int _creditHours ;
	int** _timeMatrix;

public:
	Session* _lecture;
	Session* _tutorial;

	Course();
	Course(Session* lec, Session* tut);
	
	bool AddLecture(Session* lec);
	bool AddTutorial(Session* tut);

	int GetCreditHours() const;

	int** GetTimeMatrix() const;
};

