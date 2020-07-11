#pragma once
#include "string"
#include "ENUM.h"
#include "Functions.h"
#include <iostream>
using namespace std;

class Course 
{
private:
	string course_code;				//Code of the course ex. MTHN102
	char code;					//Code to link the lecture with the tutorial ( tutorial of the lecture will have the same code as the lecture)
	//int count_lectures;				//Count of the number of lectures of the course, used later on for arranging the timetable
	int start_time;				//Start time of class
	int end_time;					//End time of class
	bool is_lecture;
	bool is_tutorial;
	Day day;						//Day of course
	int ** matrix_of_time;			//matrix which represent the timetable of a certain session of the course. if cell == 1, then the session uses this time. cells represent timeslots (ex. cell[0][0] represent time slot 8-->9 on Sunday)
public:
	Course(void);

	Course(std::string s, char c, int st, int et, char b, Day d);
	//char b is used to know if the class is either lecture or tutorial
	//ex. the user will enter "MTHN102a l 8 11 sun" (a is the code to link the lecture with the tutorial, l is for lecture, t is for tutorial)

	Course(std::string user_input);

	const void print();
	const void print_matrix();

	string getCourse() const;

	char getLinker() const;

	//int getCountLectures();

	bool isLecture() const;
	bool isTutorial() const;

	int getStartTime() const;
	int getEndTime() const;

	Day getDay() const;

	int** getMatrix() const;

	friend ostream & operator << (ostream &out, const Course &c);

	friend ostream & operator << (ostream &out, const Course* &c);

	~Course(void);
};

