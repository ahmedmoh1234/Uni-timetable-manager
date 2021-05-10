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
		for (int i = 0; i < 5; i++)
			time[i] = new int[11];

		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 11; j++)
			{
				time[i][j] = 0;
			}
		}
		//--------------------------------------------
	}

	/*
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
	*/

	bool AddCourse(Course* c)
	{
		int** new_time;
		new_time = new int* [5];
		for (int i = 0; i < 5; i++)
			new_time[i] = new int[11];

		if (table.Size() == 0)
		{
			Add_Matrix_And_Check(time, c->getMatrix(), new_time);

			table.PushBack(c);

			for (int i = 0; i < 5; i++)
				delete[] time[i];
			delete[] time;
			time = new_time;

			return true;
		}
		else
		{
			bool added = false;
			if (Add_Matrix_And_Check(time, c->getMatrix(), new_time))
			{

				int index = -1;
				for (int i = 0; i < this->table.Size(); i++)
				{
					if (c->getDay() < this->table.Get(i)->getDay())
					{
						table.PushBack(table.Get(table.Size() - 1));
						for (int j = table.Size() - 2; j >= i; j--)
						{
							table.Set(j + 1, table.Get(j));
						}
						table.Set(i, c);
						added = true;
						break;
					}
					else if (c->getDay() == this->table.Get(i)->getDay())
					{
						if (c->getStartTime() < this->table.Get(i)->getStartTime())
						{
							table.PushBack(table.Get(table.Size() - 1));
							for (int j = table.Size() - 2; j >= i; j--)
							{
								table.Set(j + 1, table.Get(j));
							}
							table.Set(i, c);
							added = true;
							break;
						}
					}

				}

				if (!added)
					table.PushBack(c);

				for (int i = 0; i < 5; i++)
					delete[] time[i];
				delete[] time;

				time = new_time;
				return true;
			}
			else
				return false;
		}


	}

	bool AddTable(const TimeTable& t) //Tested and working. Works both ways ( t1.Addtable(t2) == t2.AddTable(t1) )
	{
		DynArr<Course*> new_temp;

		int** new_time;
		new_time = new int* [5];
		for (int i = 0; i < 5; i++)
			new_time[i] = new int[11];

		if (table.Size() == 0)//POSSIBLE ERROR
		{
			table = t.table;
			int** tblTime = t.getTimeMatrix();
			for (int i = 0; i < 5; i++)
			{
				for (int j = 0; j < 11; j++)
				{
					this->time[i][j] = tblTime[i][j];
				}
			}
			return true;
		}

		if (t.table.Size() == 0)
			return true;

		if (Add_Matrix_And_Check(time, t.getTimeMatrix(), new_time))
		{

			int i = 0;
			int k = 0;

			while (i < table.Size() && k < t.table.Size())
			{
				if (table.Get(i)->getDay() < t.table.Get(k)->getDay())
				{
					new_temp.PushBack(table.Get(i));
					i++;
				}
				else if (table.Get(i)->getDay() == t.table.Get(k)->getDay())
				{
					if (table.Get(i)->getStartTime() < t.table.Get(k)->getStartTime())
					{
						new_temp.PushBack(table.Get(i));
						i++;
					}
					else
					{
						new_temp.PushBack(t.table.Get(k));
						k++;
					}
				}
				else
				{
					new_temp.PushBack(t.table.Get(k));
					k++;
				}
			}
			//Check if i or j reached the maximum
			while (i < table.Size())
			{
				//NEEDS MOdification
				//the remainig items in the table must be inserted in order
				//Unless the timetables are in order
				new_temp.PushBack(table.Get(i));
				i++;
			}

			while (k < t.table.Size())
			{
				new_temp.PushBack(t.table.Get(k));
				k++;
			}

			table = new_temp;
			//time = new_time;
			for (int i = 0; i < 5; i++)
			{
				for (int j = 0; j < 11; j++)
				{
					this->time[i][j] = new_time[i][j];
				}
			}
			return true;
		}
		else
		{
			return false;
		}
	}

	bool AddTable(TimeTable* t) //Tested and working. Works both ways ( t1.Addtable(t2) == t2.AddTable(t1) )
	{
		DynArr<Course*> new_temp;

		int** new_time;
		new_time = new int* [5];
		for (int i = 0; i < 5; i++)
			new_time[i] = new int[11];

		if (table.Size() == 0)//POSSIBLE ERROR
		{
			table = t->table;
			int** tblTime = t->getTimeMatrix();
			for (int i = 0; i < 5; i++)
			{
				for (int j = 0; j < 11; j++)
				{
					this->time[i][j] = tblTime[i][j];
				}
			}
			return true;
		}

		if (t->table.Size() == 0)
			return true;

		if (Add_Matrix_And_Check(time, t->getTimeMatrix(), new_time))
		{

			int i = 0;
			int k = 0;

			while (i < table.Size() && k < t->table.Size())
			{
				if (table.Get(i)->getDay() < t->table.Get(k)->getDay())
				{
					new_temp.PushBack(table.Get(i));
					i++;
				}
				else if (table.Get(i)->getDay() == t->table.Get(k)->getDay())
				{
					if (table.Get(i)->getStartTime() < t->table.Get(k)->getStartTime())
					{
						new_temp.PushBack(table.Get(i));
						i++;
					}
					else
					{
						new_temp.PushBack(t->table.Get(k));
						k++;
					}
				}
				else
				{
					new_temp.PushBack(t->table.Get(k));
					k++;
				}
			}
			//Check if i or j reached the maximum
			while (i < table.Size())
			{
				new_temp.PushBack(table.Get(i));
				i++;
			}

			while (k < t->table.Size())
			{
				new_temp.PushBack(t->table.Get(k));
				k++;
			}
			table = new_temp;
			//time = new_time;
			for (int i = 0; i < 5; i++)
			{
				for (int j = 0; j < 11; j++)
				{
					this->time[i][j] = new_time[i][j];
				}
			}
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

	void clear(DynArr<Course*>& dynarr)			//Tested and working
	{
		int size = table.Size();
		/*
		for (int i = 0; i < size; i++)
		{
			this->table.Set(i,nullptr);
		}
		*/
		/*
		for (int i = 0; i < size; i++)
		{
			this->table.Remove(0);
		}
		*/

		table = dynarr;
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 11; j++)
			{
				this->time[i][j] = 0;
			}
		}


	}

	int size()
	{
		return table.Size();
	}

	friend ostream& operator << (ostream& out, const TimeTable& t);

	int getNoOfGaps()
	{
		int result = 0;

		for (int i = 0; i < 5; i++)
		{
			int firstOneInd = -1;
			int lastOneInd = -1;
			for (int j = 0; j < 11; j++)
			{
				if ( time[i][j] == 1 && firstOneInd == -1)
				{
					firstOneInd = j;
					lastOneInd = j;
				}
				else if ( time[i][j] == 1 && firstOneInd != -1)
				{
					lastOneInd = j;
				}
			}

			for (int j = firstOneInd; j < lastOneInd; j++)
			{
				if ( time[i][j] == 0 )
					result++;
			}
		}
		return result;
	}


	int getNoOfFreeDays()
	{
		int result = 0;

		for (int i = 0; i < 5; i++)
		{
			int temp = 0;
			for (int j = 0; j < 11; j++)
			{
				temp += time[i][j];
			}

			if ( temp == 0 )
				result++;
		}
		return result;
	}

	~TimeTable()
	{

	}
};
