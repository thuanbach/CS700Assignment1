/**
 *  main.cpp
 *  Created on: Sep 25, 2021
 *  Author: Thuan Bach
 *
 *  The purpose of this module is to test interface functions mentioned in grade_reporting.h
 */

#include <iostream>
#include "grade_reporting_v2.h"

using namespace std;

/**
 * The main application of the program. It executes two test data defined in resource folder of the program
 *
 * Parameter(s): N/A
 *
 * Returns: 0
 */
int main() {

	export_student_grades_v2_to_console("resource/grades_Section2.txt");

	export_student_grades_v2_to_console("resource/grades_Section2_1.txt");

	return 0;
}
