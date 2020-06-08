#include <iostream>
#include <string>
#include "ENUM.h"
#include "Functions.h"
#include "Course.h"
#include "DynamicArray.h"
#include "TimeTable.h"
using namespace std;


template<class T>
ostream & operator << (ostream &out, const DynArr<T> &D)
{
	for (int i = 0; i < D.size; i++)
	{
		out << D.darr[i] << " ";
	}
	out << "\n";
	return out;
}

ostream & operator << (ostream &out, const Course &c)		//Working
{
	out << "Course code: " << c.course_code << "  " ;

	if (c.is_lecture == true)
		cout << "Lecture\t" ;
	else if (c.is_tutorial == true)
		cout << "Tutorial\t";

	Print_Day_From_Day(c.day);

	cout << "\tStart time : " << c.start_time << "\t\t";
	cout << "End time: " << c.end_time << " \t" ;
	cout << "Linker to tutorial: " << c.code ;
	cout << "\n" ;
	return out;
}

int main()
{

	//----------------------------------------a few messages for the user
	cout << "This program is used to create for you the University timetable" << endl;
	cout << "THIS PROGRAM IS NOT GUARANTEED!!!, YOU MUST VERIFY THE TIMETABLE ON THE WEBSITE " << endl;
	cout << "USE IT AT YOUR OWN RISK " << endl;
	cout << "\n" ;
	cout << "\n" ;
	cout << "Please read the instructions carefully" << endl;
	cout << "\n" ;

	///-----------------------------Getting inputs and adding them to an array
	string user_input;
	string code;
	char lec_or_tut;
	char linker_to_tutorial;
	int st;
	int et;

	cout << "Please enter: " << endl;
	cout << "1. lecture code + a unique letter to link it with a tutorial. " << endl;
	cout << "2. 'l' for lecture OR 't' for tutorial " << endl;
	cout << "3. Start time + End time (Both in 24-hour format)" << endl;
	cout << "4. Day (sat/sun/mon/tue/wed/thu)" << endl;
	cout << "ex. MTHN102a l 08 11 sun	(REMEMBER, use the letter 'a' with the same tutorial. 'a' can be any letter EXCEPT z). If the Course has no tutorial, enter letter z" << endl;
	//			 01234567890123456789
	cout << "YOU NEED TO WRITE A LETTER EVEN IF THERE IS NO TUTORIAL (like GENNs)" << endl;
	cout << "\n" ;

	getline(cin, user_input);

	code				= user_input.substr(0,7);
	linker_to_tutorial	= user_input[7];
	lec_or_tut			= user_input[9];

	string t1			= user_input.substr(11,2);
	string t2			= user_input.substr(14,2);

	st				= stoi(t1);
	et				= stoi(t2);

	Day d			= Read_Day_From_String( user_input.substr(17,3) );

	Course* courses[200];
	int no_of_courses = 0;

	courses[no_of_courses] = new Course (code, linker_to_tutorial, st, et, lec_or_tut, d);
	//courses[no_of_courses]->print_matrix(); //////testing
	no_of_courses++;

	while ( code.length() == 7  )
	{
		cout << "\n" ;
		cout << "Please enter another session or enter 0 to end " << endl;

		getline(cin, user_input);

		code				= user_input.substr(0,7);
		if (code == "0")
		{break;}

		linker_to_tutorial	= user_input[7];
		lec_or_tut			= user_input[9];

		string t1			= user_input.substr(11,2);
		string t2			= user_input.substr(14,2);

		st					= stoi(t1);
		et					= stoi(t2);

		Day d				= Read_Day_From_String( user_input.substr(17,3) );

		courses[no_of_courses] = new Course (code, linker_to_tutorial, st, et, lec_or_tut, d);
		///courses[no_of_courses]->print_matrix(); //////testing
		no_of_courses++;


	}

	//------------------------------Printing inputs
	for (int i = 0; i<no_of_courses; i++)
	{
		courses[i]->print();
		//courses[i]->print_matrix();////////////////////////////////////////
	}

	cout << "\n";

	//-----------------Getting the courses the user want to enroll at
	int no_of_user_courses;
	cout << "Please enter the number of courses you want: " ;
	cin >> no_of_user_courses;

	string* p_user_courses = new string [no_of_user_courses];

	cout << "Please enter the courses you want " ;
	cout << "\n";
	cout << "enter each course then press enter" ;
	cout << "\n";

	for (int i = 0; i<no_of_user_courses; i++)
	{
		string temp1;
		cout << i+1 << " " ;
		cin >> temp1;
		Convert_String_To_Uppercase(temp1);
		p_user_courses[i] = temp1;

	}


	//------------------Printing the courses the user want to enroll at
	cout << "\n";
	cout << "The courses you entered are: ";
	cout << "\n";

	for (int i = 0; i<no_of_user_courses; i++)
	{
		cout << i+1 << " " << p_user_courses[i] ;
		cout << "\n";

	}

	//-------------Organising courses into Subject (Lecture + tutorial)
	DynArr< DynArr< DynArr<TimeTable*> > > subjects;

	for (int i = 0; i < no_of_user_courses ; i++ )
	{
		DynArr< DynArr<TimeTable*> > course_1;

		DynArr<Course*> lec;
		DynArr<Course*> tut;
		DynArr<TimeTable*> lec_tut;

		for (int j = 0; j < no_of_courses; j++)
		{
			if ( courses[j]->getCourse() == p_user_courses[i] && courses[j]->isLecture() )
			{
				lec.PushBack( courses[j] );
			}
			else if ( courses[j]->getCourse() == p_user_courses[i] && courses[j]->isTutorial() )
			{
				tut.PushBack( courses[j] );
			}

		}

		for ( int j = 0; j < lec.Size(); j++ )
		{
			for ( int k = 0; k < tut.Size(); k++ )
			{
				int ** mm;
				if ( lec.Get(j)->getLinker() == tut.Get(k)->getLinker() && Add_Matrix_And_Check( lec.Get(j)->getMatrix(), tut.Get(k)->getMatrix(), mm) )
				{
					TimeTable* t = new TimeTable();
					t->AddCourse( lec.Get(j) );
					t->AddCourse( tut.Get(k) );
					lec_tut.PushBack( t );
				}
			}
		}

		// add array to "subjects" arr
		if (lec_tut.Size() != 0)
		{
			course_1.PushBack( lec_tut );
			subjects.PushBack( course_1 );
		}
		else
		{
			cout << "Course " << p_user_courses[i] << " does not have a tutorial and a lecture that can be combined\n";
		}

	}

















	system("pause");


	return 0;
}









