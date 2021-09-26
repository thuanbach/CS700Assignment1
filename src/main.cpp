/**
 *  main.cpp
 *  Created on: Sep 25, 2021
 *  Author: Thuan Bach
 *
 *  The purpose of this module is to test interface functions mentioned in grade_reporting.h
 */

#include <iostream>
#include "grade_reporting.h"

using namespace std;

int main() {

	string student_exam_scores_raw_file = "resource/grades_Section1.txt";

	string export_folder = "resource";

	export_student_grades_to_console(student_exam_scores_raw_file);

	export_student_grades_to_directory(student_exam_scores_raw_file, export_folder);

	return 0;
}
