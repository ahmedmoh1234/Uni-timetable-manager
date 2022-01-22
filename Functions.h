#pragma once

#include <iostream>
#include <string>
#include "ENUM.h"
#include "Session.h"

#include <vector>

using namespace std;
using matTime = vector<vector<int>>;



void Convert_String_To_Uppercase (string& s);			//Tested and working

void Convert_String_To_Uppercase (char& s);				//Tested and working

Day Read_Day_From_String (string s);			//Tested and working

void Print_Day_From_Day (Day d);		//Tested and working


bool Add_Matrix_And_Check(matTime arr1, matTime arr2, matTime& arr3);	//Tested and working

bool Check_If_Matrix_Added (matTime arr1, matTime arr2);	//Tested and working

//Course* Make_Courses_Package (string* user_courses, Course* av_courses);
