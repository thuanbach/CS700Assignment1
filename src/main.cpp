//============================================================================
// Name        : CS700Assignment1.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include <string.h>
#include <sstream>
#include <ctype.h>
#include <cstdlib>
#include <iomanip>
#include "grade_reporting.h"

using namespace std;

int main() {

	string student_exam_scores_raw_file = "resource/grades_Section1.txt";

	string export_folder = "D:\\ThuanBach\\UR Computer Science\\CS700\\CS700Assignment1\\resource";

	export_student_grades_to_directory(student_exam_scores_raw_file, export_folder);

	return 0;
}
