#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <time.h>
#include <sstream> 
#include <set>

#include "ENUM.h"
#include "Functions.h"
#include "Course.h"
#include "DynamicArray.h"
#include "TimeTable.h"
#include <unordered_set>

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

vector<string> FileReader();

vector<string> fileReadProcess( const vector<string>& read );

bool operator < (Course c1, Course c2)
{
	if (c1.getCourse() < c2.getCourse())
	{
		return true;
	}

	else if (c1.getCourse() == c2.getCourse())
	{
		if (c1.getDay() < c2.getDay())
		{
			return true;
		}
		else if (c1.getDay() == c2.getDay())
		{
			if (c1.getStartTime() < c2.getStartTime())
			{
				return true;
			}
		}

	}

	return false;
}

void resetIndex(int v, DynArr<int>& indices, const DynArr< DynArr<TimeTable*> >& subjects, bool& end);



int main()
{
	system("title University Timetable Manager V1");
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
	//cout << "Please enter: " << endl;
	//cout << "1. lecture code + a unique letter to link it with a tutorial. " << endl;
	//cout << "2. 'l' for lecture OR 't' for tutorial " << endl;
	//cout << "3. Start time + End time (Both in 24-hour format)" << endl;
	//cout << "4. Day (sat/sun/mon/tue/wed/thu)" << endl;
	//cout << "ex. MTHN102a l 08 11 sun	(REMEMBER, use the letter 'a' with the same tutorial. 'a' can be any letter EXCEPT z). If the Course has no tutorial, enter letter z" << endl;
	////			 01234567890123456789
	//cout << "YOU NEED TO WRITE A LETTER EVEN IF THERE IS NO TUTORIAL (like GENNs)" << endl;
	//cout << "\n";

	cout << "1. Open the student portal and login\n";
	cout << "2. Open ""Registration Status Report""  \n";
	cout << "3. Select all (CTRL + A) then copy (CTRL + C)\n";
	cout << "4. Open a notepad and paste the copied data into it and save it\n";
	cout << "5. Press ""SHIFT + Right mouse click"" on the saved notepad\n";
	cout << "6. Press on ""Copy as path""\n";
	cout << "7. Run the program, paste the path and follow the instructions\n";

	vector<string> input_courses;

	input_courses = FileReader();
	cout << "Please Wait\n";
	input_courses = fileReadProcess(input_courses);
	
	
	vector<Course> courses;
	
	for (int i = 0; i < input_courses.size(); i++)
	{
		courses.push_back( Course(input_courses[i]) );
	}

	
	//Sorting courses and removing duplicates
	set<Course> s(courses.begin(), courses.end());
	courses.assign(s.begin(), s.end());
	//for (int i = 0; i < courses.size(); i++)
	//{
	//	s.insert(courses[i]);
	//}
	//cout << s.size() << "\n";;
	//courses.assign(s.begin(), s.end());
	//cout << courses.size() << "\n";
	//courses.shrink_to_fit();
	//cout << courses.size() << "\n";
	//system("pause");

	//===============================TO BE DONE============= Add a functor for comparison between courses


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
	for (int i = 0; i < courses.size(); i++)
	{
		cout << i+1 << " ";
		courses[i].print();
		//courses[i]->print_matrix();////////////////////////////////////////
	}

	cout << "\n";
	
	//-----------------Getting the courses the user want to enroll at
	/*
	int no_of_user_courses;
	cout << "Please enter the number of courses you want: ";
	cin >> no_of_user_courses;

	string* p_user_courses = new string[no_of_user_courses];
	*/
	vector<string> p_user_courses;
	cout << "Please enter the courses you want ";
	cout << "\n";
	cout << "enter each course then press enter";
	cout << "\n";
	cout << "Enter 0 when you finish";
	cout << "\n";
	string temp1 = "";
	int userCount = 0;
	cout << userCount + 1 << " ";
	cin >> temp1;
	while (temp1 != "0")
	{
		Convert_String_To_Uppercase(temp1);
		p_user_courses.push_back(temp1);
		userCount++;
		cout << userCount + 1 << " ";
		cin >> temp1;
	}


	//------------------Printing the courses the user want to enroll at
	cout << "\n";
	cout << "The courses you entered are: ";
	cout << "\n";

	for (int i = 0; i < p_user_courses.size(); i++)
	{
		cout << i + 1 << " " << p_user_courses[i];
		cout << "\n";

	}
	
	

	//-------------Organising courses into Subject (Lecture + tutorial)
	//PROBLEM : at the end of the first lecture, the timetable duplicates // SOLVED
	DynArr< DynArr<TimeTable*> >  subjects;

	for (int i = 0; i < p_user_courses.size(); i++)
	{
		DynArr<TimeTable*> course_1;

		DynArr<Course*> lec;
		DynArr<Course*> tut;

		for (int j = 0; j < courses.size(); j++)
		{
			if (courses[j].getCourse() == p_user_courses[i] && courses[j].isLecture())
			{
				lec.PushBack(&courses[j]);
			}
			else if (courses[j].getCourse() == p_user_courses[i] && courses[j].isTutorial())
			{
				tut.PushBack(&courses[j]);
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
			//if ( lec.Get(j)->getLinker() == 'z' || lec.Get(j)->getLinker() == 'Z')// TO BE CHANGED TO -1
			if ( lec.Get(j)->getLinker() == '0')// TO BE CHANGED TO -1
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


	////////////////////////////PROBLEM: EXCESSIVE memory use 2GB//////////////////////////////////////////////////
	////////////////////////////SOLVED, the problem was with the time matrix///////////////////////////////////////


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
		/*cout << "Indices : " << indices << "\n";
		system("pause");*/



		//int v = 0;


		bool dismissed = false;



		while (indices.Get(0) < subjects.Get(0).Size() && !end) //REMEMBER Size is more than the indices by 1
		{
			TimeTable temp;
			for (int i = 0; i < subjects.Size(); i++)	
			{
				if (Check_If_Matrix_Added(subjects.Get(i).Get(indices.Get(i))->getTimeMatrix(), temp.getTimeMatrix()))
				{
					temp.AddTable(subjects.Get(i).Get(indices.Get(i)));
				}
				else
				{
					dismissed = true;
					break;
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

	//Sorting final tables according to the noOfFreeDays and noOfGaps DESCENDINGLY
	for (int i = 0; i < finalTables.Size(); i++)
	{
		for (int j = i; j < finalTables.Size(); j++)
		{
			if ( finalTables.Get(j).getNoOfFreeDays() > finalTables.Get(i).getNoOfFreeDays() )
			{
				TimeTable temp;
				temp = finalTables.Get(j);
				finalTables.Set(j, finalTables.Get(i));
				finalTables.Set(i, temp);
			}
			else if ( finalTables.Get(j).getNoOfFreeDays() == finalTables.Get(i).getNoOfFreeDays() )
			{
				if ( finalTables.Get(j).getNoOfGaps() > finalTables.Get(i).getNoOfGaps() )
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
		//finalTables.Get(i).PrintMatrix();
		cout <<"\nNo of gap hours = " << finalTables.Get(i).getNoOfGaps();
		cout << "\nNo of free days = " << finalTables.Get(i).getNoOfFreeDays() << "\n";
		cout << "======================================================================================================================\n";
	}
	time_t etime = time(NULL);
	double diff = difftime(etime, stime);
	cout << "The Program took " << (diff) << " seconds.\n";

	cout << "Total number of tables = " << finalTables.Size() << "\n";
	cout << "Finished!! \n";
	system("pause");
	return 0;
}

vector<string> FileReader()
{
	cout << "Please input file name or file path : ";

	string in;
	getline(cin, in);

	//Removing " at the beginning and at the end of the path
	if (in[0] == '"')
		in.erase(0,1);
	if (in[in.size()-1] == '"')
		in.erase(in.size()-1,1);
	
	if (in.size()-4 < 0)
		in += ".txt";
	else if (in.substr(in.size()-4,4) != ".txt")
		in += ".txt";

	if ( in.find_last_of('\\') != string::npos)	//Returns the position of the last '\', or npos if not found
		cout << in.substr(in.find_last_of('\\') +1) << "\n";

	ifstream input;
	input.open(in);

	while (!input)
	{
		cout << "Error\nPlease input file name : ";
		getline(cin, in);
		if (in == "")
			continue;
		//Removing " at the beginning and at the end of the path
		if (in[0] == '"')
			in.erase(0, 1);
		if (in[in.size() - 1] == '"')
			in.erase(in.size() - 1, 1);

		if (in.size() - 4 < 0)
			in += ".txt";
		else if (in.substr(in.size() - 4, 4) != ".txt")
			in += ".txt";

		if (in.find_last_of('\\') != string::npos)	//Returns the position of the last '\', or npos if not found
			cout << in.substr(in.find_last_of('\\') + 1) << "\n";
		input.open(in);
	}
	cout << "Opened\n";

	string a;
	vector<string> result;

	while (input)
	{
		string temp = a;
		getline(input, a);
		if (a != temp)
			result.push_back(a);
	}
	return result;
}

vector<string> fileReadProcess( const vector<string>& read ) // need to be implemented
{

	//try using move to make is efficient
	vector<string> result;
	bool nexter = false;
	for (int i = 0; i < read.size(); i++)
	{
		stringstream sstream ( read[i] );
		if ( read[i] == "" )
			continue;

		if ( read[i].substr(0,2) == "id" )
		{
			nexter = true;
			continue;
		}

		if ( nexter )
		{
			//"ex. MTHN102a l 08 11 sun
			bool isGENN = false;
			string temp;
			string finaler = "";
			getline(sstream, temp, '\t');		//GET id
			if ( temp[0] < '1' || temp[0] > '9' )
				continue;
			getline(sstream, temp, '\t');		//GET code
			while ( temp.find('_') != string::npos)
				temp.erase( temp.find('_'), 1);

			//Now, temp has the course code
			if ( temp.find("GENN") != string::npos )
				isGENN = true;

			finaler += temp;
			getline(sstream, temp, '\t');	//name
			getline(sstream, temp, '\t');	//group
			if ( isGENN )
				finaler += "0 ";
			else
				finaler += "1 ";

			getline(sstream, temp, '\t');	//type
			if ( temp == "Lecture_" )
				finaler += "l ";
			else
				finaler += "t ";

			string day;
			getline(sstream, temp, '\t');	//Day
			if ( temp == "Sunday" )
				day = "sun";
			else if ( temp == "Monday" )
				day = "mon";
			else if ( temp == "Tuesday" )
				day = "tue";
			else if ( temp == "Wednesday" )
				day = "wed";
			else if ( temp == "Thursday" )
				day = "thu";
			else if ( temp == "Saturday" )
				continue;
				
				//day = "sun";			////////////////////////////////////////////////TO BE FIXED

			

			getline(sstream, temp, '\t');	//start time
			temp = temp.substr(0, temp.find(':'));
			if ( temp.size() == 1 )
			{
				temp.insert(0,"0");
			}
			finaler += temp + " ";

			getline(sstream, temp, '\t');	//end time
			temp = temp.substr(0, temp.find(':'));
			if ( temp.size() == 1 )
			{
				if (temp[0] == '9')
				{
					temp[0] = '1';
					temp += "0";
				}
				else
				{
					temp[0] += 1;		
					temp.insert(0,"0");
				}
			}
			else
				temp[1] += 1;
			finaler += temp + " ";
			finaler += day;
			result.push_back(finaler);
		}
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

