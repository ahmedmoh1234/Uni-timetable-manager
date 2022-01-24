#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <time.h>
#include <sstream> 
#include <set>
#include <unordered_set>
#include <chrono>

#include "ENUM.h"
#include "Functions.h"
#include "Session.h"
#include "DynamicArray.h"
#include "TimeTable.h"
#include "Course.h"

using namespace std;
using Time = std::chrono::high_resolution_clock;


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
	out << "Credit hours = " << t.getNoOfCH() << "\n";
	for (int i = 0; i < t._table.size(); i++)
	{
		if (i > 0 && !(t._table[i]->getDay() == t._table[i - 1]->getDay()) && t._table.size() > 2)
			out << "\n";
		out << *(t._table[i]);
	}
	out << "\n";
	return out;
}

ostream& operator << (ostream& out, TimeTable* t)
{
	out << "Credit hours = " << t->getNoOfCH() << "\n";
	for (int i = 0; i < t->_table.size(); i++)
	{
		if (i > 0 && !(t->_table[i]->getDay() == t->_table[i-1]->getDay()) && t->_table.size() > 2)
			out << "\n";
		out << *(t->_table[i]);
	}
	out << "\n";
	return out;
}

ostream& operator << (ostream& out, const Session& c)		//Working
{
	out << "Course code: " << c.course_code << "  ";

	if (c.is_lecture == true)
		cout << "Lecture\t";
	else if (c.is_tutorial == true)
		cout << "Tutorial\t";

	Print_Day_From_Day(c.day);

	cout << "\tStart time : " << c.start_time << "\t\t";
	cout << "End time: " << c.end_time << " \t";
	//cout << "Linker to tutorial: " << c.code;
	cout << "\n";
	return out;
}

ostream& operator << (ostream& out, const Session*& c)		//Working
{
	out << "Course code: " << c->course_code << "  ";

	if (c->is_lecture == true)
		cout << "Lecture\t";
	else if (c->is_tutorial == true)
		cout << "Tutorial\t";

	Print_Day_From_Day(c->day);

	cout << "\tStart time : " << c->start_time << "\t\t";
	cout << "End time: " << c->end_time << " \t";
	//cout << "Linker to tutorial: " << c->code;
	cout << "\n";
	return out;
}

vector<string> FileReader();

vector<string> fileReadProcess( const vector<string>& read );

bool operator < (Session c1, Session c2)
{
	if (c1.getCourseCode() < c2.getCourseCode())
	{
		return true;
	}

	else if (c1.getCourseCode() == c2.getCourseCode())
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

void resetIndex(int v, vector<int>& indices, const vector< vector<TimeTable*> >& subjects, bool& end);

template <class T>
void PrintVector(vector<T> vec)
{
	for (int i = 0; i < vec.size; i++)
	{
		cout << vec[i] << "\n";
	}
}

void createLecandTutArr(vector<Session>& allCourses, vector<Session*>& lec, vector<Session*>& tut, const string& inputUserCoursesString, bool openOrClose);

vector<TimeTable*> addLecandTut(vector<Session*>& lec, vector<Session*> &tut, const string& inputUserCoursesString);

vector<string> getUserCourses();

void printTimetables(const vector<TimeTable>& finalTables, Time::time_point sTime);

vector<TimeTable> getPremutations(const vector< vector<TimeTable*> >& subjects);

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
	cout << "The output tables are sorted DESCENDINGLY in order of the number of gap hours and number of free days\n";
	cout << "This means that the table with the least number of gap hours and the most free days will be the last timetable\n\n";

	vector<string> input_courses;

	input_courses = FileReader();
	cout << "Please Wait\n";
	input_courses = fileReadProcess(input_courses);
	
	
	vector<Session> allCourses;
	
	for (int i = 0; i < input_courses.size(); i++)
	{
		allCourses.push_back( Session(input_courses[i]) );
	}

	
	//Sorting courses and removing duplicates
	set<Session> s(allCourses.begin(), allCourses.end());
	allCourses.assign(s.begin(), s.end());


	//------------------------------Printing inputs
	for (int i = 0; i < allCourses.size(); i++)
	{
		cout << i+1 << " ";
		cout << allCourses[i];
	}

	cout << "\n";
	
	cout << "Do you want to take into consideration whether the session is opened or closed ? (Y/N)\n";
	char openOrCloseAnswer;
	bool openOrClose;
	cin >> openOrCloseAnswer;

	

	if (openOrCloseAnswer == 'y' || openOrCloseAnswer == 'Y')
		openOrClose = true;
	else if (openOrCloseAnswer == 'n' || openOrCloseAnswer == 'N')
		openOrClose = false;


	bool tryAgain = true;
	while (tryAgain)
	{
		//-----------------Getting the courses the user want to enroll at
		vector<string> inputUserCoursesString = getUserCourses();
		

		//------------------Printing the courses the user want to enroll at
		cout << "\n";
		cout << "The courses you entered are: ";
		cout << "\n";

		for (int i = 0; i < inputUserCoursesString.size(); i++)
		{
			cout << i + 1 << " " << inputUserCoursesString[i];
			cout << "\n";

		}


		//Adding each course lec & tut to other courses
		Time::time_point stime = Time::now();


		//-------------Organising courses into Subject (Lecture + tutorial)
		vector< vector<TimeTable*> >  subjects;
		for (int i = 0; i < inputUserCoursesString.size(); i++)
		{


			vector<TimeTable*> course_1;

			vector<Session*> lec;
			vector<Session*> tut;

			//Create a lecture array and tutorial array for the current course in the loop
			createLecandTutArr(allCourses, lec, tut, inputUserCoursesString[i], openOrClose);
	
			//===========Adding lectures and tutorials together for the current course in the loop
			subjects.push_back(addLecandTut(lec, tut, inputUserCoursesString[i]));
		}


		//Get premutations from subjects
		vector<TimeTable> finalTables = getPremutations(subjects); //Contains the final tables to be displayed before sorting
		

		//Sorting final tables according to the noOfFreeDays and noOfGaps DESCENDINGLY
		sort(finalTables.begin(), finalTables.end(), [](const TimeTable &t1, const TimeTable &t2) {
			if (t1.getNoOfFreeDays() < t2.getNoOfFreeDays())
				return true;
			else if (t1.getNoOfFreeDays() == t2.getNoOfFreeDays())
				if (t1.getNoOfGaps() > t2.getNoOfGaps())
					return true;

			return false;
			});
		

		//Printing the sorted timetables
		printTimetables(finalTables, stime);
		
		
		//Ask user to try again
		cout << "Try again ? (Y/N)\n";
		char tryAgainChar;
		cin >> tryAgainChar;

		if (tryAgainChar == 'y' || tryAgainChar == 'Y')
			tryAgain = true;
		else
			tryAgain = false;
		
	}

	
	system("pause");

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
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
			while ( temp.find('_') != string::npos) //removes underscore form code
				temp.erase( temp.find('_'), 1);

			//Now, temp has the course code
			if ( temp.find("GENN") != string::npos 
				|| temp.find("CCEN") != string::npos 
				|| temp.find("EEEN") != string::npos
				|| temp.find("CIEN") != string::npos
				|| temp.find("STEN") != string::npos
				|| temp.find("AETN") != string::npos
				|| temp.find("PPCN") != string::npos			
				|| temp.find("WEEN") != string::npos
				|| temp.find("CEMN") != string::npos
				|| temp.find("MDEN") != string::npos
				)
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
			if (temp == "Sunday")
				day = "sun";
			else if (temp == "Monday")
				day = "mon";
			else if (temp == "Tuesday")
				day = "tue";
			else if (temp == "Wednesday")
				day = "wed";
			else if (temp == "Thursday")
				day = "thu";
			else if (temp == "Saturday")
				day = "sat";
				
				

			

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

			getline(sstream, temp, '\t');	//class size NOT USED
			getline(sstream, temp, '\t');	//enrolled NOT USED
			getline(sstream, temp, '\t');	//waiting size NOT USED

			getline(sstream, temp, '\t');	//status
			if (temp == "___Opened___")
			{
				finaler += " open";
			}
			else if (temp == "___Closed___")
			{
				finaler += " closed";
			}
			else
			{
				cout << "Error: course is neither opened nor closed.\nRecommendation is to turn off the closed/open option";
			}

			result.push_back(finaler);
		}
	}
	return result;
}



void resetIndex(int v, vector<int>& indices, const vector< vector<TimeTable*> >& subjects, bool& end)
{
	while (v >= 0 && indices[v] == subjects[v].size() - 1)
	{
		indices[v] = 0;
		v--;
	}
	if (v == -1)
	{
		end = true;
		//THere was a break
	}
	else
	{
		indices[v] += 1;
		v = 0;
	}
}

void createLecandTutArr(vector<Session> &allCourses, vector<Session*>& lec, vector<Session*>& tut, const string &inputUserCoursesString, bool openOrClose)
{
	for (int j = 0; j < allCourses.size(); j++)
	{
		if (allCourses[j].getCourseCode() == inputUserCoursesString && allCourses[j].isLecture() && (!openOrClose || allCourses[j].getIsOpen()))
		{
			//lec.PushBack(&courses[j]);
			lec.push_back(&allCourses[j]);
		}
		else if (allCourses[j].getCourseCode() == inputUserCoursesString && allCourses[j].isTutorial() && (!openOrClose || allCourses[j].getIsOpen()))
		{
			//tut.PushBack(&courses[j]);
			tut.push_back(&allCourses[j]);

		}
	}
}


vector<TimeTable*> addLecandTut(vector<Session*> &lec, vector<Session*> &tut, const string& inputUserCoursesString)
{
	vector<TimeTable*> tempTimetable;
	for (int j = 0; j < lec.size(); j++)
	{
		//if ( lec.Get(j)->getLinker() == 'z' || lec.Get(j)->getLinker() == 'Z')// TO BE CHANGED TO -1
		if (lec[j]->getIsGENN())
		{
			TimeTable* t = new TimeTable();
			t->AddCourse(lec[j]);
			//TODO Add credit hours to the timetable
			t->setCH(lec[j]->getEndTime() - lec[j]->getStartTime());
			tempTimetable.push_back(t);

			continue;
		}
		for (int k = 0; k < tut.size(); k++)
		{

			if (lec[j]->getLinker() == tut[k]->getLinker()
				&& Check_If_Matrix_Added(lec[j]->getMatrix(), tut[k]->getMatrix()))
			{
				TimeTable* t = new TimeTable();
				t->AddCourse(lec[j]);
				t->AddCourse(tut[k]);
				//TODO Add credit hours to the timetable
				int lecTime = lec[j]->getEndTime() - lec[j]->getStartTime();
				int tutTime = tut[k]->getEndTime() - tut[k]->getStartTime();

				if (lecTime > tutTime)
					t->setCH(lecTime);
				else
					t->setCH(tutTime);

				tempTimetable.push_back(t);
			}
		}
	}

	if (tempTimetable.size() == 0)
		cout << "Course " << inputUserCoursesString << " cannot be added to the timetable\n";

	return tempTimetable;

}

vector<string> getUserCourses()
{
	vector<string> inputUserCoursesString;
	cout << "Please enter the courses you want ";
	cout << "\n";
	cout << "enter each course then press enter";
	cout << "\n";
	cout << "Enter 0 when you finish";
	cout << "\n";
	string temp1 = "";
	int userCount = 1;
	cout << userCount << " ";
	cin >> temp1;
	while (temp1 != "0")
	{

		Convert_String_To_Uppercase(temp1);
		inputUserCoursesString.push_back(temp1);
		userCount++;
		cout << userCount << " ";
		cin >> temp1;
	}

	return inputUserCoursesString;
}

void printTimetables(const vector<TimeTable> &finalTables, Time::time_point sTime)
{
	for (int i = 0; i < finalTables.size(); i++)
	{
		cout << "\n";
		cout << "\n";
		cout << "======================================================================================================================\n";
		cout << "Table number " << i + 1 << "\n" << finalTables[i] << "\n";
		//finalTables.Get(i).PrintMatrix();
		cout << "\nNo of gap hours = " << finalTables[i].getNoOfGaps();
		cout << "\nNo of free days = " << finalTables[i].getNoOfFreeDays() << "\t(Saturdays included)\n";
		cout << "======================================================================================================================\n";
	}

	//Calculating time
	Time::time_point etime = std::chrono::high_resolution_clock::now();
	std::chrono::microseconds diff = std::chrono::duration_cast<std::chrono::microseconds>(etime - sTime);
	cout << "The Program took " << diff.count() / 1000000.0 << " seconds.\n";

	cout << "Total number of tables = " << finalTables.size() << "\n";
	cout << "Finished!! \n";

}

vector<TimeTable> getPremutations(const vector< vector<TimeTable*> >&subjects)
{
	vector<TimeTable> finalTables;

	if (subjects.size() != 0)
	{
		bool end = false;

		vector<int> indices;
		int n1 = 0;
		for (int i = 0; i < subjects.size(); i++)
		{
			if (subjects[i].size() == 0)
				end = true;
			indices.push_back(n1);
		}

		bool dismissed = false;



		while (indices[0] < subjects[0].size() && !end) //REMEMBER Size is more than the indices by 1
		{
			TimeTable temp;
			for (int i = 0; i < subjects.size(); i++)
			{
				if (Check_If_Matrix_Added(subjects[i][indices[i]]->getTimeMatrix(), temp.getTimeMatrix()))
				{
					temp.AddTable(subjects[i][indices[i]]);
				}
				else
				{
					dismissed = true;
					break;
				}
			}
			if (!dismissed)
			{
				finalTables.push_back(temp);
			}
			dismissed = false;
			resetIndex(subjects.size() - 1, indices, subjects, end);
		}
	}

	return finalTables;
}