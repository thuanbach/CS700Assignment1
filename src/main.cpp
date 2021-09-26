/**
 *  main.cpp
 *  Created on: Sep 25, 2021
 *  Author: Thuan Bach
 *
 *  The purpose of this module is to test interface functions mentioned in grade_reporting.h
 */

#include <iostream>

using namespace std;

void export_student_grades_v2_to_console(const string &file_path);

int main() {

	string student_exam_scores_raw_file = "resource/grades_Section2.txt";

	export_student_grades_v2_to_console(student_exam_scores_raw_file);

	return 0;
}
