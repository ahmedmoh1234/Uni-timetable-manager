#include "Course.h"
#include <sstream>


Course::Course(void)
{
}


Course::Course(std::string s, char c, int st, int et, char b, Day d)
{
	Convert_String_To_Uppercase(s);
	course_code = s;

	Convert_String_To_Uppercase(c);
	code = c;

	start_time = st;
	end_time = et;

	day = d;

	Convert_String_To_Uppercase(b);
	if (b == 'L')
	{
		is_lecture = true;
		is_tutorial = false;
	}
	else if (b == 'T')
	{
		is_lecture = false;
		is_tutorial = true;
	}

	//----------------Creating 2D array-----------
	matrix_of_time = new int* [ROW_COUNT];
	for (int i = 0; i < ROW_COUNT; i++)
		matrix_of_time[i] = new int[COL_COUNT];
	//--------------------------------------------


	for (int i = 0; i < ROW_COUNT; i++)
	{
		for (int j = 0; j < COL_COUNT; j++)
		{
			if ((d - 1) == i)
			{
				if ((st - 8) == j)
				{
					for (int k = (st - 8); k < (et - 8); k++)
					{
						matrix_of_time[i][k] = 1;
						j = k;
					}

				}
				else { matrix_of_time[i][j] = 0; }
			}
			else
			{
				matrix_of_time[i][j] = 0;
			}
		}
	}
}


Course::Course(std::string user_input)
{
	stringstream sstream(user_input);
	string temp;
	//Course code
	getline(sstream, temp, ' ');

	Convert_String_To_Uppercase(temp);
	course_code = temp.substr(0, temp.length() - 1);

	//Linker
	char linker_to_tutorial = temp[temp.length() - 1];
	//Convert_String_To_Uppercase(linker_to_tutorial);
	code = linker_to_tutorial;

	getline(sstream, temp, ' ');
	char lec_or_tut = temp[0];
	Convert_String_To_Uppercase(lec_or_tut);
	if (lec_or_tut == 'L')
	{
		is_lecture = true;
		is_tutorial = false;
	}
	else if (lec_or_tut == 'T')
	{
		is_lecture = false;
		is_tutorial = true;
	}

	getline(sstream, temp, ' ');
	int st = stoi(temp);

	getline(sstream, temp, ' ');
	int et = stoi(temp);


	if (st >= 1 && st <= 7)
	{
		st += 12;
		et += 12;
	}
	else if (st > et)
		et += 12;


	start_time = st;
	end_time = et;

	matrix_of_time = new int* [ROW_COUNT];
	for (int i = 0; i < ROW_COUNT; i++)
		matrix_of_time[i] = new int[COL_COUNT];
	//--------------------------------------------

	getline(sstream, temp, ' ');	//get day
	Day d = Read_Day_From_String(temp);
	day = d;

	for (int i = 0; i < ROW_COUNT; i++)
	{
		for (int j = 0; j < COL_COUNT; j++)
		{
			if (d  == i)
			{
				if ((st - 8) == j)
				{
					for (int k = (st - 8); k < (et - 8); k++)
					{
						matrix_of_time[i][k] = 1;
						j = k;
					}

				}
				else { matrix_of_time[i][j] = 0; }
			}
			else
			{
				matrix_of_time[i][j] = 0;
			}
		}
	}

	getline(sstream, temp, ' ');	//get "open" or "closed"
	if (temp == "open")
		isOpen = true;
	else
		isOpen = false;

	bool falser = false;
	for (int i = 0; i < ROW_COUNT; i++)
	{
		for (int j = 0; j < COL_COUNT; j++)
		{
			if (matrix_of_time[i][j] == 1)
				falser = true;
		}

	}

	if (!falser)
	{
		cout << "ERROR\n";
		cout << "Course name : " << course_code << "\tStart time : " << st << "\tEnd time: " << et << "\n";
		for (int i = 0; i < ROW_COUNT; i++)
		{
			for (int j = 0; j < COL_COUNT; j++)
			{
				cout << matrix_of_time[i][j] << " ";
			}
			cout << "\n";
		}
		system("pause");
	}
}

/*
Course::Course(std::string user_input)
{
	string ccode				= user_input.substr(0,7);
	Convert_String_To_Uppercase(ccode);
	course_code = ccode;

	char linker_to_tutorial		= user_input[7];
	Convert_String_To_Uppercase(linker_to_tutorial);
	code		= linker_to_tutorial;

	char lec_or_tut			= user_input[9];
	Convert_String_To_Uppercase(lec_or_tut);
	if ( lec_or_tut == 'L')
	{
		is_lecture  = true;
		is_tutorial = false;
	}
	else if ( lec_or_tut == 'T')
	{
		is_lecture  = false;
		is_tutorial = true;
	}

	string t1				= user_input.substr(11,2);
	string t2				= user_input.substr(14,2);

	int st				= stoi(t1);
	int et				= stoi(t2);
	start_time = st;
	end_time	= et;

	matrix_of_time = new int* [5];
	for (int  i = 0; i < 5; i++)
		matrix_of_time[i] = new int [11];
	//--------------------------------------------
	Day d				= Read_Day_From_String( user_input.substr(17,3) );
	day = d;

	for (int i = 0; i<5; i++)
	{
		for (int j = 0; j<11; j++)
		{
			if ( (d-1) == i )
			{
				if ( (st - 8) == j)
				{
					for ( int k = (st - 8); k < (et - 8); k++)
					{
						matrix_of_time[i][k] = 1;
						j = k;
					}

				}
				else {matrix_of_time[i][j] = 0;}
			}
			else
			{
				matrix_of_time[i][j] = 0;
			}
		}
	}


}
*/
const void Course::print()
{
	cout << "Course code: " << course_code << "  ";

	if (is_lecture == true)
		cout << "Lecture\t";
	else if (is_tutorial == true)
		cout << "Tutorial\t";

	Print_Day_From_Day(day);

	cout << "\tStart time : " << start_time << "\t\t";
	cout << "End time: " << end_time << " \t";
	cout << "Linker to tutorial: " << code;
	cout << "\n";
}



const void Course::print_matrix()
{
	for (int i = 0; i < ROW_COUNT; i++)
	{
		for (int j = 0; j < COL_COUNT; j++)
		{
			cout << matrix_of_time[i][j] << " ";
		}
		cout << "\n";
	}

}

string Course::getCourse() const
{
	return course_code;
}

char Course::getLinker() const
{
	return code;
}

bool Course::isLecture() const
{
	return is_lecture;
}

bool Course::isTutorial() const
{
	return is_tutorial;
}

int Course::getStartTime() const
{
	return start_time;
}

int Course::getEndTime() const
{
	return end_time;
}

Day Course::getDay() const
{
	return day;
}


int** Course::getMatrix() const
{
	return matrix_of_time;
}

bool Course::getIsOpen() const
{
	return isOpen;
}
//bool Course::operator< (Course* c2)
//{
//	if (this->getCourse() < c2->getCourse())
//	{
//		return true;
//	}
//
//	else if (this->getCourse() == c2->getCourse())
//	{
//		if (this->getDay() < c2->getDay())
//		{
//			return true;
//		}
//		else if (this->getDay() == c2->getDay())
//		{
//			if (this->getStartTime() < c2->getStartTime())
//			{
//				return true;
//			}
//		}
//	}
//	return false;
//}

//bool Course::operator== (Course* c2)
//{
//	if (this->getCourse() < c2->getCourse())
//	{
//		return true;
//	}
//
//	else if (this->getCourse() == c2->getCourse())
//	{
//		if (this->getDay() < c2->getDay())
//		{
//			return true;
//		}
//		else if (this->getDay() == c2->getDay())
//		{
//			if (this->getStartTime() < c2->getStartTime())
//			{
//				return true;
//			}
//		}
//	}
//	return false;
//}


Course::~Course(void)
{
	for (int i = 0; i < 5; i++)
	{
		//delete [] matrix_of_time[i];
	}
	//delete [] matrix_of_time;

}
