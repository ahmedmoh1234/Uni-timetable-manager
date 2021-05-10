#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <time.h>

#include "ENUM.h"
#include "Functions.h"
#include "Course.h"
#include "DynamicArray.h"
#include "TimeTable.h"

using namespace std;


template<class T>
ostream& operator << (ostream& out, const DynArr<T>& D)
{

	for (int i = 0; i < D.size; i++)
	{
		out << D.darr[i] << " ";
	}
	out << "\n";


	return out;
}

template<class T>
ostream& operator << (ostream& out, const DynArr<T*>& D)
{

	for (int i = 0; i < D.size; i++)
	{
		out << *(D.darr[i]);
	}
	out << "\n";


	return out;
}

ostream& operator << (ostream& out, const TimeTable& t)
{
	for (int i = 0; i < t.table.Size(); i++)
	{
		if (i > 0 && !(t.table.Get(i)->getDay() == t.table.Get(i - 1)->getDay()) && t.table.Size() > 2)
			out << "\n";
		out << *(t.table.Get(i));
	}
	out << "\n";
	return out;
}

ostream& operator << (ostream& out, const Course& c)		//Working
{
	out << "Course code: " << c.course_code << "  ";

	if (c.is_lecture == true)
		cout << "Lecture\t";
	else if (c.is_tutorial == true)
		cout << "Tutorial\t";

	Print_Day_From_Day(c.day);

	cout << "\tStart time : " << c.start_time << "\t\t";
	cout << "End time: " << c.end_time << " \t";
	cout << "Linker to tutorial: " << c.code;
	cout << "\n";
	return out;
}

ostream& operator << (ostream& out, const Course*& c)		//Working
{
	out << "Course code: " << c->course_code << "  ";

	if (c->is_lecture == true)
		cout << "Lecture\t";
	else if (c->is_tutorial == true)
		cout << "Tutorial\t";

	Print_Day_From_Day(c->day);

	cout << "\tStart time : " << c->start_time << "\t\t";
	cout << "End time: " << c->end_time << " \t";
	cout << "Linker to tutorial: " << c->code;
	cout << "\n";
	return out;
}

DynArr<string> FileReader();

DynArr<string> fileReadProcess( const DynArr<string>& read );

void resetIndex(int v, DynArr<int>& indices, const DynArr< DynArr<TimeTable*> >& subjects, bool& end);

int main()
{
	system("title University Timetable Manager");
	//----------------------------------------a few messages for the user
	/*
	cout << "This program is used to create for you the University timetable" << endl;
	cout << "THIS PROGRAM IS NOT GUARANTEED!!!, YOU MUST VERIFY THE TIMETABLE ON THE WEBSITE " << endl;
	cout << "USE IT AT YOUR OWN RISK " << endl;
	cout << "\n";
	cout << "\n";
	cout << "Please read the instructions carefully" << endl;
	cout << "\n";
	*/
	///-----------------------------Getting inputs and adding them to an array
	cout << "Please enter: " << endl;
	cout << "1. lecture code + a unique letter to link it with a tutorial. " << endl;
	cout << "2. 'l' for lecture OR 't' for tutorial " << endl;
	cout << "3. Start time + End time (Both in 24-hour format)" << endl;
	cout << "4. Day (sat/sun/mon/tue/wed/thu)" << endl;
	cout << "ex. MTHN102a l 08 11 sun	(REMEMBER, use the letter 'a' with the same tutorial. 'a' can be any letter EXCEPT z). If the Course has no tutorial, enter letter z" << endl;
	//			 01234567890123456789
	cout << "YOU NEED TO WRITE A LETTER EVEN IF THERE IS NO TUTORIAL (like GENNs)" << endl;
	cout << "\n";

	DynArr<string> input_courses;

	input_courses = FileReader();
	//fileReadProcess(input_courses);
	/*
	string user_input;
	getline(cin, user_input,';');
	*/

	/*
	bool wantFreeDay;
	char ans;
	cout << "Do you want a freeday ? (y/n) : ";
	cin >> ans;
	if (ans == 'y' || ans == 'Y')
		wantFreeDay = true;
	else
		wantFreeDay = false;

	int minHoursPerDay;
	cout << "Enter the minimum amount of hours per day : ";
	cin >> minHoursPerDay;

	int maxNoOfGapHours;
	cout << "Enter the maximum amount of gap hours per day : ";
	cin >> maxNoOfGapHours;
	*/
	Course* courses[200];
	int no_of_courses = 0;

	for (int i = 0; i < input_courses.Size(); i++)
	{
		courses[no_of_courses] = new Course(input_courses.Get(i));
		no_of_courses++;
	}
	//Sorting the courses
	for (int i = 0; i < no_of_courses; i++)
	{
		for (int j = i; j < no_of_courses; j++)
		{
			if ( courses[j]->getDay() < courses[i]->getDay() )
			{
				Course* temp;
				temp = courses[i];
				courses[i] = courses[j];
				courses[j] = temp;
			}
			else if ( courses[j]->getDay() == courses[i]->getDay() ) 
			{
				if ( courses[j]->getStartTime() < courses[i]->getStartTime() )
				{
					Course* temp;
					temp = courses[i];
					courses[i] = courses[j];
					courses[j] = temp;
				}
			}
		}
	}
	//courses[no_of_courses]->print_matrix(); //////testing

	/*
	string code = user_input.substr(0,7);
	while ( code.length() == 7  )
	{
	cout << "\n" ;
	cout << "Please enter another session or enter 0 to end " << endl;

	getline(cin, user_input,';');

	code				= user_input.substr(0,7);
	if (code == "0")
	{break;}

	courses[no_of_courses] = new Course (user_input);
	///courses[no_of_courses]->print_matrix(); //////testing
	no_of_courses++;


	}
	*/
	//------------------------------Printing inputs
	for (int i = 0; i < no_of_courses; i++)
	{
		courses[i]->print();
		//courses[i]->print_matrix();////////////////////////////////////////
	}

	cout << "\n";

	//-----------------Getting the courses the user want to enroll at
	int no_of_user_courses;
	cout << "Please enter the number of courses you want: ";
	cin >> no_of_user_courses;

	string* p_user_courses = new string[no_of_user_courses];

	cout << "Please enter the courses you want ";
	cout << "\n";
	cout << "enter each course then press enter";
	cout << "\n";

	for (int i = 0; i < no_of_user_courses; i++)
	{
		string temp1;
		cout << i + 1 << " ";
		cin >> temp1;
		Convert_String_To_Uppercase(temp1);
		p_user_courses[i] = temp1;

	}


	//------------------Printing the courses the user want to enroll at
	cout << "\n";
	cout << "The courses you entered are: ";
	cout << "\n";

	for (int i = 0; i < no_of_user_courses; i++)
	{
		cout << i + 1 << " " << p_user_courses[i];
		cout << "\n";

	}

	//-------------Organising courses into Subject (Lecture + tutorial)
	//PROBLEM : at the end of the first lecture, the timetable duplicates // SOLVED
	DynArr< DynArr<TimeTable*> >  subjects;

	for (int i = 0; i < no_of_user_courses; i++)
	{
		DynArr<TimeTable*> course_1;

		DynArr<Course*> lec;
		DynArr<Course*> tut;

		for (int j = 0; j < no_of_courses; j++)
		{
			if (courses[j]->getCourse() == p_user_courses[i] && courses[j]->isLecture())
			{
				lec.PushBack(courses[j]);
			}
			else if (courses[j]->getCourse() == p_user_courses[i] && courses[j]->isTutorial())
			{
				tut.PushBack(courses[j]);
			}
		}

		//cout << "Lectures : " << lec << "\n";
		//cout << "\nTutorials : " << tut << "\n";
		//system("pause");

		/*
		int** mm;
		mm = new int* [5];
		for (int i = 0; i < 5; i++)
			mm[i] = new int[11];
		*/

		//===========Adding lectures and tutorials together
		for (int j = 0; j < lec.Size(); j++)
		{
			if ( lec.Get(j)->getLinker() == 'z' || lec.Get(j)->getLinker() == 'Z')
			{
				TimeTable* t = new TimeTable();
				t->AddCourse(lec.Get(j));
				course_1.PushBack(t);
				continue;
			}
			for (int k = 0; k < tut.Size(); k++)
			{

				if (lec.Get(j)->getLinker() == tut.Get(k)->getLinker() && Check_If_Matrix_Added(lec.Get(j)->getMatrix(), tut.Get(k)->getMatrix()))
				{
					TimeTable* t = new TimeTable();
					t->AddCourse(lec.Get(j));
					t->AddCourse(tut.Get(k));
					course_1.PushBack(t);
				}
			}
		}

		// add array to "subjects" arr
		//if (course_1.Size() != 0)
		subjects.PushBack(course_1);
		if (course_1.Size() == 0)
			cout << "Course " << p_user_courses[i] << " does not have a tutorial and a lecture that can be combined\n";
		/*
		else
			// Printing the Timetable of the course
			cout << "Printing Timetable contents of " << p_user_courses[i] << ": \n";
		*/
		//system("pause");

		for (int l = 0; l < course_1.Size(); l++)
			cout << *(course_1.Get(l)) << "\n";

		system("pause");
	}

	//Adding each course lec & tut to other courses
	time_t stime = time(NULL);

	DynArr<TimeTable> finalTables; //Contains the final tables to be displayed before sorting

	if (subjects.Size() != 0)
	{
		bool end = false;

		DynArr<int> indices;
		int n1 = 0;
		for (int i = 0; i < subjects.Size(); i++)
		{
			if (subjects.Get(i).Size() == 0)
				end = true;
			indices.PushBack(n1);
		}

		//cout << "Indices : " << indices << "\n";
		//system("pause");

		//int v = 0;


		bool dismissed = false;

		

		while (indices.Get(0) < subjects.Get(0).Size() && !end) //REMEMBER Size is more than the indices by 1
		{
			TimeTable temp;
			for (int i = 0; i < subjects.Size(); i++)	//Can be change to a for loop
			{
				if (Check_If_Matrix_Added(subjects.Get(i).Get(indices.Get(i))->getTimeMatrix(), temp.getTimeMatrix()))
				{
					temp.AddTable(subjects.Get(i).Get(indices.Get(i)));
				}
				else
				{
					dismissed = true;
				}
			}
			if (!dismissed)
			{
				finalTables.PushBack(temp);
			}
			dismissed = false;
			resetIndex(subjects.Size() - 1, indices, subjects, end);
		} 
	}

	//Sorting final tables according to the noOfFreeDays and noOfGaps
	for (int i = 0; i < finalTables.Size(); i++)
	{
		for (int j = i; j < finalTables.Size(); j++)
		{
			if ( finalTables.Get(j).getNoOfFreeDays() < finalTables.Get(i).getNoOfFreeDays() )
			{
				TimeTable temp;
				temp = finalTables.Get(j);
				finalTables.Set(j, finalTables.Get(i));
				finalTables.Set(i, temp);
			}
			else if ( finalTables.Get(j).getNoOfFreeDays() == finalTables.Get(i).getNoOfFreeDays() )
			{
				if ( finalTables.Get(j).getNoOfGaps() < finalTables.Get(i).getNoOfGaps() )
				{
					TimeTable temp;
					temp = finalTables.Get(j);
					finalTables.Set(j, finalTables.Get(i));
					finalTables.Set(i, temp);
				}
			}
		}
	}


	//Printing the sorted timetables
	for (int i = 0; i < finalTables.Size(); i++ )
	{
		cout << "\n";
		cout << "\n";
		cout << "======================================================================================================================\n";
		cout << "Table number " << i+1 << "\n" << finalTables.Get(i) << "\n";
		finalTables.Get(i).PrintMatrix();
		cout <<"\nNo of Gaps = " << finalTables.Get(i).getNoOfGaps();
		cout << "\nNo of free days = " << finalTables.Get(i).getNoOfFreeDays() << "\n";
		cout << "======================================================================================================================\n";
	}
	time_t etime = time(NULL);
	double diff = difftime(etime, stime);
	cout << "The Program took " << (diff) << " seconds.\n";

	cout << "Total number of tables = " << finalTables.Size() << "\n";
	cout << "Finished!! =)\n";
	system("pause");
	return 0;
}

DynArr<string> FileReader()
{
	cout << "Please input file name : ";

	string in;
	getline(cin, in);

	//cout << "\n " << in.size() << "\n";
	if (in[0] == '"')
		in.erase(0,1);
	if (in[in.size()-1] == '"')
		in.erase(in.size()-1,1);
	//cout << "\n " << in.size() << "\n" << in.substr(in.size()-4,4) << "\n";
	if (in.size()-4 < 0)
		in += ".txt";
	else if (in.substr(in.size()-4,4) != ".txt")
		in += ".txt";

	int pos = in.find_last_of('\\');	//Returns the position of the last '\', or npos if not found
	cout << in.substr(pos+1) << "\n";

	ifstream input;
	input.open(in);

	while (!input)
	{
		cout << "Error\nPlease input file name : ";
		getline(cin, in);
		in += ".txt";
		input.open(in);
	}
	cout << "Opened\n";

	string a;
	DynArr<string> result;

	while (input)
	{
		string temp = a;
		getline(input, a);
		if (a != temp)
			result.PushBack(a);
	}
	return result;
}

DynArr<string> fileReadProcess( const DynArr<string>& read ) // need to be implemented
{
	DynArr<string> result;
	for (int i = 0; i < read.Size(); i++)
	{
		string temp;
		temp = read.Get(i);
		int spaceCount = 0;
		for (int j = 0; j < temp.length() - 1; j++)
		{

			if ( temp.substr(j,2) == "\t")
				cout << "tab found";
		}
		cout <<  temp;
		system("pause");
	}
	return result;
}

void resetIndex(int v, DynArr<int>& indices, const DynArr< DynArr<TimeTable*> >& subjects, bool& end)
{
	while (v >= 0 && indices.Get(v) == subjects.Get(v).Size() - 1)
	{
		indices.Set(v, 0);
		v--;
	}
	if (v == -1)
	{
		end = true;
		//THere was a break
	}
	else
	{
		indices.Set(v, indices.Get(v) + 1);
		v = 0;
	}
}