#pragma once
#include "DynamicArray.h"
#include "Course.h"
#include "Functions.h"

class TimeTable
{
private:
	DynArr<Course*> table;
	int** time;

public:
	TimeTable()
	{
		//----------------Creating 2D array-----------
		time = new int* [5];
		for (int  i = 0; i < 11; i++)
			time[i] = new int [11];

		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 11; j++)
			{
				time[i][j] = 0;
			}

		}
		//--------------------------------------------
	}

	TimeTable ( DynArr<Course*> d1, DynArr<Course*> d2 ) //NOT COMPLETED
	{
		//----------------Creating 2D array-----------
		time = new int* [5];
		for (int  i = 0; i < 11; i++)
			time[i] = new int [11];

		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 11; j++)
			{
				time[i][j] = 0;
			}

		}
		//--------------------------------------------


		//--------Add two arrays of courses
		int end = 0;
		for (int i = 0; i < d1.Size(); i++)
		{
			
		}



	}


	bool AddCourse(Course* c)
	{
		int ** new_time;
		if ( Add_Matrix_And_Check(time, c->getMatrix(), new_time) )
		{
			table.PushBack(c);
			time = new_time;
			return true;
		}
		else
			return false;


	}

	bool AddTable (const TimeTable& t)
	{
		int ** new_time;
		if ( Add_Matrix_And_Check( time, t.getTimeMatrix(), new_time ) )
		{
			for ( int  i = 0; i < t.table.Size(); i++ )
			{
				table.PushBack( t.table.Get(i) );
			}

			time = new_time;
			return true;
		}
		else
		{
			return false;
		}


	}


	void Print()
	{
		cout << table;
		cout << "\n";
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 11; j++)
			{
				cout << time[i][j] << " ";
			}
			cout << "\n";
		}
	}

	void PrintMatrix()
	{
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 11; j++)
			{
				cout << time[i][j] << " ";
			}
			cout << "\n";
		}
	}

	int** getTimeMatrix() const
	{
		return time;
	}


	~TimeTable()
	{

	}





};
