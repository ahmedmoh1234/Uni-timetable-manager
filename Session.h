#pragma once

#include "string"
#include "ENUM.h"
#include "Functions.h"
#include <iostream>

const int ROW_COUNT = 6;
const int COL_COUNT = 14;
using namespace std;

class Session 
{
private:
	string course_code;				//Code of the course ex. MTHN102
	char code;						//Code to link the lecture with the tutorial ( tutorial of the lecture will have the same code as the lecture)
	//int count_lectures;			//Count of the number of lectures of the course, used later on for arranging the timetable
	int start_time;					//Start time of class
	int end_time;					//End time of class
	bool is_lecture;
	bool is_tutorial;
	Day day;						//Day of course
	int ** matrix_of_time;			//matrix which represent the timetable of a certain session of the course. if cell == 1, then the session uses this time. cells represent timeslots (ex. cell[0][0] represent time slot 8-->9 on Sunday)
	bool isOpen;					//true if the session is open, false otherwise
	bool isGENN;					//true if Course is GENN or equivalent (no tutorial)
	//int _creditHours;				//No. of credit hours of the course.
public:
	Session(void);

	Session(std::string s, char c, int st, int et, char b, Day d);
	//char b is used to know if the class is either lecture or tutorial
	//ex. the user will enter "MTHN102a l 8 11 sun" (a is the code to link the lecture with the tutorial, l is for lecture, t is for tutorial)

	Session(std::string user_input);

	const void print();
	const void print_matrix();

	string getCourseCode() const;

	char getLinker() const;

	//int getCountLectures();

	bool isLecture() const;
	bool isTutorial() const;

	int getStartTime() const;
	int getEndTime() const;

	Day getDay() const;

	int** getMatrix() const;

	bool getIsOpen() const;

	bool getIsGENN() const;

	friend ostream & operator << (ostream &out, const Session &c);

	friend ostream & operator << (ostream &out, const Session* &c);

	friend bool operator < (Session c1,Session c2);

	int SessionDuration() const;

	//bool operator== (Course* c2);

	~Session(void);
};

