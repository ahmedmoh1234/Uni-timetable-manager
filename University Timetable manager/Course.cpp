#include "Course.h"


Course::Course(void)
{
}


Course::Course(std::string s, char c, int st, int et, char b, Day d)
{
	Convert_String_To_Uppercase(s);
	course_code = s;

	Convert_String_To_Uppercase(c);
	code		= c;

	start_time	= st;
	end_time	= et;

	day			= d;
	
	Convert_String_To_Uppercase(b);
	if ( b == 'L')
	{
		is_lecture  = true;
		is_tutorial = false;
	}
	else if ( b == 'T')
	{
		is_lecture  = false;
		is_tutorial = true;
	}

	//----------------Creating 2D array-----------
	matrix_of_time = new int* [5];
	for (int  i = 0; i < 11; i++)
		matrix_of_time[i] = new int [11];
	//--------------------------------------------


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


const void Course::print() 
{
	cout << "Course code: " << course_code << "  " ;
	
	if (is_lecture == true)
		cout << "Lecture\t" ;
	else if (is_tutorial == true)
		cout << "Tutorial\t";

	Print_Day_From_Day(day);

	cout << "\tStart time : " << start_time << "\t\t";
	cout << "End time: " << end_time << " \t" ;
	cout << "Linker to tutorial: " << code ;
	cout << "\n" ;
}



const void Course::print_matrix()
{
	for (int  i = 0; i < 5; i++)
	{
		for (int j = 0; j < 11; j++)
		{
			cout << matrix_of_time[i][j] << " ";
		}
		cout << "\n" ;
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






Course::~Course(void)
{
	for ( int i = 0; i < 5; i++)
	{
		delete [] matrix_of_time[i];
	}
	delete [] matrix_of_time;

}
