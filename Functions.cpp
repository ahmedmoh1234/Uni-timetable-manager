#include "Functions.h"


void Convert_String_To_Uppercase(string& s)
{
	for (int i = 0; i < s.length(); i++)
	{
		s[i] = toupper(s[i]);
	}

}

void Convert_String_To_Uppercase(char& s)
{
	s = toupper(s);
}

Day Read_Day_From_String(string s)
{
	Convert_String_To_Uppercase(s);
	Day d;

	if (s == "SAT")
	{
		d = Saturday;
	}
	else if (s == "SUN")
	{
		d = Sunday;
	}
	else if (s == "MON")
	{
		d = Monday;
	}
	else if (s == "TUE")
	{
		d = Tuesday;
	}
	else if (s == "WED")
	{
		d = Wednesday;
	}
	else if (s == "THU")
	{
		d = Thursday;
	}
	return d;
}

void Print_Day_From_Day(Day d)
{
	if (d == 0)
		cout << "Saturday   ";
	else if (d == 1)
		cout << "Sunday   ";
	else if (d == 2)
		cout << "Monday   ";
	else if (d == 3)
		cout << "Tuesday   ";
	else if (d == 4)
		cout << "Wednesday   ";
	else if (d == 5)
		cout << "Thursday   ";
}


void Print_2D_Matrix(char** arr, int rows, int cols)
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			cout << arr[i][j] << " ";
		}

		cout << "\n";
	}
	cout << "\n";
}

bool Add_Matrix_And_Check(matTime arr1, matTime arr2, matTime& arr3)	//i<5 & j<11
{
	for (int i = 0; i < ROW_COUNT; i++)
	{
		for (int j = 0; j < COL_COUNT; j++)
		{
			arr3[i][j] = arr1[i][j] + arr2[i][j];
			if (arr3[i][j] > 1)
				return false;
		}

	}

	return true;
}

bool Check_If_Matrix_Added(matTime arr1, matTime arr2)	//i<5 & j<11
{
	/*cout << "\n Matrix 1\n";
	for (int i = 0; i < ROW_COUNT; i++)
	{
		for (int j = 0; j < COL_COUNT; j++)
		{
			cout << arr1[i][j] << " ";
		}
		cout << "\n";

	}


	cout << "\n Matrix 2\n";
	for (int i = 0; i < ROW_COUNT; i++)
	{
		for (int j = 0; j < COL_COUNT; j++)
		{
			cout << arr2[i][j] << " ";
		}
		cout << "\n";

	}*/

	for (int i = 0; i < ROW_COUNT; i++)
	{
		for (int j = 0; j < COL_COUNT; j++)
		{
			char a = arr1[i][j] + arr2[i][j];
			if (a > 1)
			{
				return false;
			}
		}

	}

	return true;
}

//Course* Make_Courses_Package (string* user_courses, Course* av_courses)
//{
//
//}


