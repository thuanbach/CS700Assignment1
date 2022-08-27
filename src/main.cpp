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

/**
 * The main application of the program. It executes two test data defined in resource folder of the program
 *
 * Parameter(s): N/A
 *
 * Returns: 0
 */

int main() {

	// run program with the first input data set
	string student_exam_scores_raw_file_1 = "resource/grades_Section1.txt";

	export_student_grades_to_console(student_exam_scores_raw_file_1);

	export_student_grades_to_directory(student_exam_scores_raw_file_1, "export/1");

	// run program with the second input data set
	string student_exam_scores_raw_file_1_1 = "resource/grades_Section1_1.txt";

	export_student_grades_to_console(student_exam_scores_raw_file_1_1);

	export_student_grades_to_directory(student_exam_scores_raw_file_1_1, "export/2");

	return 0;
}
