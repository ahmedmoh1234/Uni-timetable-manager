#include "Course.h"



Course::Course()
{
	_lecture = nullptr;
	_tutorial = nullptr;
	_creditHours = 0;

	//----------------Creating 2D array-----------
	_timeMatrix = new int* [ROW_COUNT];
	for (int i = 0; i < ROW_COUNT; i++)
		_timeMatrix[i] = new int[COL_COUNT];

	for (int i = 0; i < ROW_COUNT; i++)
	{
		for (int j = 0; j < COL_COUNT; j++)
		{
			_timeMatrix[i][j] = 0;
		}
	}
	//--------------------------------------------


}

Course::Course(Session* lec, Session* tut)
{

	Add_Matrix_And_Check(lec->getMatrix(), tut->getMatrix(), _timeMatrix);
	_lecture = lec;
	_tutorial = tut;

	if (lec->SessionDuration() > tut->SessionDuration())
	{
		_creditHours = lec->SessionDuration();
	}
	else
	{
		_creditHours = tut->SessionDuration();
	}

	
}


bool Course::AddLecture(Session* lec)
{
	if (_lecture != nullptr)
		return false;





	if (_tutorial == nullptr)
	{
		_lecture = lec;
		_creditHours = _lecture->SessionDuration();
	}
	else if (_tutorial != nullptr)
	{
		//Need to check whether the lecture and tutorial clash with each other or not

		int** new_time;
		new_time = new int* [ROW_COUNT];
		for (int i = 0; i < ROW_COUNT; i++)
			new_time[i] = new int[COL_COUNT];

		if (!Add_Matrix_And_Check(lec->getMatrix(), _tutorial->getMatrix(), new_time))
			return false;

		_timeMatrix = new_time;


		_lecture = lec;

		if (_lecture->SessionDuration() > _tutorial->SessionDuration())
		{
			_creditHours = _lecture->SessionDuration();
		}
		else
		{
			_creditHours = _tutorial->SessionDuration();
		}
	}

	return true;
}


bool Course::AddTutorial(Session* tut)
{
	if (_tutorial != nullptr)
		return false;

	if (_lecture == nullptr)
	{
		_tutorial = tut;
		_creditHours = _tutorial->SessionDuration();
	}
	else if (_lecture != nullptr)
	{

		//Need to check whether the lecture and tutorial clash with each other or not

		int** new_time;
		new_time = new int* [ROW_COUNT];
		for (int i = 0; i < ROW_COUNT; i++)
			new_time[i] = new int[COL_COUNT];

		if (!Add_Matrix_And_Check(_lecture->getMatrix(), tut->getMatrix(), new_time))
			return false;

		_timeMatrix = new_time;

		_tutorial = tut;

		if (_tutorial->SessionDuration() > _lecture->SessionDuration())
		{
			_creditHours = _tutorial->SessionDuration();
		}
		else
		{
			_creditHours = _lecture->SessionDuration();
		}
	}
}

int Course::GetCreditHours() const
{
	return _creditHours;
}

int** Course::GetTimeMatrix() const
{
	return _timeMatrix;
}