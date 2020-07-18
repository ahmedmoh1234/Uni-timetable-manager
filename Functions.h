#pragma once

#include <iostream>
#include <string>
#include "ENUM.h"
#include "Course.h"

using namespace std;



void Convert_String_To_Uppercase (string& s);			//Tested and working

void Convert_String_To_Uppercase (char& s);				//Tested and working

Day Read_Day_From_String (string s);			//Tested and working

void Print_Day_From_Day (Day d);		//Tested and working

void Print_2D_Matrix ( int ** arr , int rows, int cols);	//Tested and working

bool Add_Matrix_And_Check (int ** arr1, int ** arr2, int ** &arr3);	//Tested and working

//Course* Make_Courses_Package (string* user_courses, Course* av_courses);

