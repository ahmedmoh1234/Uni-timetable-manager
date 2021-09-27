#pragma once
#include "DynamicArray.h"
#include "Session.h"
#include "Functions.h"
#include "Course.h"

class TimeTable
{
private:
	vector<Session*> table;
	int** time;
	int _creditHours;

public:
	TimeTable()
	{
		//----------------Creating 2D array-----------
		time = new int* [ROW_COUNT];
		for (int i = 0; i < ROW_COUNT; i++)
			time[i] = new int[COL_COUNT];

		for (int i = 0; i < ROW_COUNT; i++)
		{
			for (int j = 0; j < COL_COUNT; j++)
			{
				time[i][j] = 0;
			}
		}
		//--------------------------------------------

		//Credit hours = 0 for new timetables
		_creditHours = 0;
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
	for (int i = 0; i < d1.size(); i++)
	{

	}



	}
	*/

	bool AddCourse(Session* c)
	{
		int** new_time;
		new_time = new int* [ROW_COUNT];
		for (int i = 0; i < ROW_COUNT; i++)
			new_time[i] = new int[COL_COUNT];

		if (table.size() == 0)
		{
			Add_Matrix_And_Check(time, c->getMatrix(), new_time);

			table.push_back(c);

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
				for (int i = 0; i < this->table.size(); i++)
				{
					if (c->getDay() < this->table[i]->getDay())
					{
						table.push_back(table[table.size() - 1]);
						for (int j = table.size() - 2; j >= i; j--)
						{
							table[j + 1] = table[j];
						}
						table[i] = c;
						added = true;
						break;
					}
					else if (c->getDay() == this->table[i]->getDay())
					{
						if (c->getStartTime() < this->table[i]->getStartTime())
						{
							table.push_back(table[table.size() - 1]);
							for (int j = table.size() - 2; j >= i; j--)
							{
								table[j + 1] = table[j];
							}
							table[i] = c;
							added = true;
							break;
						}
					}

				}

				if (!added)
					table.push_back(c);

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
		vector<Session*> new_temp;

		int** new_time;
		new_time = new int* [ROW_COUNT];
		for (int i = 0; i < ROW_COUNT; i++)
			new_time[i] = new int[COL_COUNT];

		if (table.size() == 0)//POSSIBLE ERROR
		{
			table = t.table;
			int** tblTime = t.getTimeMatrix();
			for (int i = 0; i < ROW_COUNT; i++)
			{
				for (int j = 0; j < COL_COUNT; j++)
				{
					this->time[i][j] = tblTime[i][j];
				}
			}
			return true;
		}

		if (t.table.size() == 0)
			return true;

		if (Add_Matrix_And_Check(time, t.getTimeMatrix(), new_time))
		{

			int i = 0;
			int k = 0;

			while (i < table.size() && k < t.table.size())
			{
				if (table[i]->getDay() < t.table[k]->getDay())
				{
					new_temp.push_back(table[i]);
					i++;
				}
				else if (table[i]->getDay() == t.table[k]->getDay())
				{
					if (table[i]->getStartTime() < t.table[k]->getStartTime())
					{
						new_temp.push_back(table[i]);
						i++;
					}
					else
					{
						new_temp.push_back(t.table[k]);
						k++;
					}
				}
				else
				{
					new_temp.push_back(t.table[k]);
					k++;
				}
			}
			//Check if i or j reached the maximum
			while (i < table.size())
			{
				//NEEDS MOdification
				//the remainig items in the table must be inserted in order
				//Unless the timetables are in order
				new_temp.push_back(table[i]);
				i++;
			}

			while (k < t.table.size())
			{
				new_temp.push_back(t.table[k]);
				k++;
			}

			table = new_temp;
			//time = new_time;
			for (int i = 0; i < ROW_COUNT; i++)
			{
				for (int j = 0; j < COL_COUNT; j++)
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
		vector<Session*> new_temp;

		int** new_time;
		new_time = new int* [ROW_COUNT];
		for (int i = 0; i < ROW_COUNT; i++)
			new_time[i] = new int[COL_COUNT];

		if (table.size() == 0)//POSSIBLE ERROR
		{
			table = t->table;
			//this->time = std::move(t->time);
			int** tblTime = t->getTimeMatrix();
			for (int i = 0; i < ROW_COUNT; i++)
			{
				for (int j = 0; j < COL_COUNT; j++)
				{
					this->time[i][j] = tblTime[i][j];
				}
			}
			
			/*for (int i = 0; i < 5; i++)
				delete[] t->time[i];
			delete[] t->time;*/
			return true;
		}

		if (t->table.size() == 0)
			return true;

		if (Add_Matrix_And_Check(time, t->getTimeMatrix(), new_time))
		{

			int i = 0;
			int k = 0;

			while (i < table.size() && k < t->table.size())
			{
				if (table[i]->getDay() < t->table[k]->getDay())
				{
					new_temp.push_back(table[i]);
					i++;
				}
				else if (table[i]->getDay() == t->table[k]->getDay())
				{
					if (table[i]->getStartTime() < t->table[k]->getStartTime())
					{
						new_temp.push_back(table[i]);
						i++;
					}
					else
					{
						new_temp.push_back(t->table[k]);
						k++;
					}
				}
				else
				{
					new_temp.push_back(t->table[k]);
					k++;
				}
			}
			//Check if i or j reached the maximum
			while (i < table.size())
			{
				new_temp.push_back(table[i]);
				i++;
			}

			while (k < t->table.size())
			{
				new_temp.push_back(t->table[k]);
				k++;
			}
			table = new_temp;
			//time = new_time;
			for (int i = 0; i < ROW_COUNT; i++)
			{
				for (int j = 0; j < COL_COUNT; j++)
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
		//cout << table;
		cout << "\n";
		for (int i = 0; i < ROW_COUNT; i++)
		{
			for (int j = 0; j < COL_COUNT; j++)
			{
				cout << time[i][j] << " ";
			}
			cout << "\n";
		}
	}

	void PrintMatrix()
	{
		for (int i = 0; i < ROW_COUNT; i++)
		{
			for (int j = 0; j < COL_COUNT; j++)
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

	void clear(vector<Session*>& dynarr)			//Tested and working
	{
		int size = table.size();
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
		for (int i = 0; i < ROW_COUNT; i++)
		{
			for (int j = 0; j < COL_COUNT; j++)
			{
				this->time[i][j] = 0;
			}
		}


	}

	int size()
	{
		return table.size();
	}

	friend ostream& operator << (ostream& out, const TimeTable& t);

	friend ostream& operator << (ostream& out, TimeTable* t);

	int getNoOfGaps()
	{
		int result = 0;

		for (int i = 0; i < ROW_COUNT; i++)
		{
			int firstOneInd = -1;
			int lastOneInd = -1;
			for (int j = 0; j < COL_COUNT; j++)
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

		for (int i = 0; i < ROW_COUNT; i++)
		{
			int temp = 0;
			for (int j = 0; j < COL_COUNT; j++)
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
