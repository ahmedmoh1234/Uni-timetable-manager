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
		new_time = new int* [5];
		for (int  i = 0; i < 11; i++)
			new_time[i] = new int [11];

		if ( Add_Matrix_And_Check(time, c->getMatrix(), new_time) )
		{
			table.PushBack(c);
			time = new_time;
			return true;
		}
		else
			return false;


	}

	bool AddTable (const TimeTable& t) //Tested and working. Works both ways ( t1.Addtable(t2) == t2.AddTable(t1) )
	{
		DynArr<Course*> new_temp;

		int ** new_time;
		new_time = new int* [5];
		for (int  i = 0; i < 11; i++)
			new_time[i] = new int [11];

		if (table.Size() == 0)//POSSIBLE ERROR
		{
			table = t.table;
			return true;
		}

		if(t.table.Size() == 0)
			return true;

		if ( Add_Matrix_And_Check( time, t.getTimeMatrix(), new_time ) )
		{

			int i = 0;
			int k = 0;

			while ( i < table.Size() && k < t.table.Size() )
			{
				if ( table.Get(i)->getDay() < t.table.Get(k)->getDay() )
				{
					new_temp.PushBack( table.Get(i) );
					i++;
				}
				else if ( table.Get(i)->getDay() == t.table.Get(k)->getDay() )
				{
					if ( table.Get(i)->getStartTime() < t.table.Get(k)->getStartTime() )
					{
						new_temp.PushBack( table.Get(i) );
						i++;
					}
					else
					{
						new_temp.PushBack( t.table.Get(k) );
						k++;
					}
				}
				else
				{
					new_temp.PushBack( t.table.Get(k) );
					k++;
				}
			}
			//Check if i or j reached the maximum
			while ( i < table.Size() )
			{
				new_temp.PushBack( table.Get(i) );
				i++;
			}

			while ( k < t.table.Size() )
			{
				new_temp.PushBack( t.table.Get(k) );
				k++;
			}

			table = new_temp;
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


	friend ostream & operator << (ostream &out, const TimeTable &t);

	~TimeTable()
	{

	}





};
