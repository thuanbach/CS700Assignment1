/**
 *  grade_reporting_v2.h
 *  Created on: Sep 26, 2021
 *  Author: Thuan Bach
 *
 * This module provides functionality for reading a text file in which the first line contains the number of students
 * and the number of exams, and each of the following lines contain a student' name and exam scores. All students have
 * the same number of exam scores. Then, calculate exam grades for each exam and export to a specific output as the
 * console.
 *
 * Here is an example for a line in the text file:
 * 		2 10
 * 		SPWKLZWHCIE GAPCEXAS 99 100 91 68 72 100 93 74 77 96
 * 		FCCEPWNFVV XJME W 100 100 100 92 80 70 84 76 77 80
 *
 * In the first line, 2 is the number of students, and 10 is the number of exams. In the first line,
 * "SPWKLZWHCIE GAPCEXAS" is the name of a student, and "99 100 91 68 72 100 93 74 77 96" are scores of exams. And it
 *  is similar for the third line.
 *
 * A student's letter grade for an exam will be calculated based on the average score of that exam and this rule
 *  +-----------------------------------------------------------+
 *  | Letter Grade 	|  Score	  								|
 *  +-----------------------------------------------------------+
 *  | A				| {average score + 15, above]				|
 *  | B				| {average score + 5 , average score + 15]	|
 *  | C				| [average score - 5 , average score + 5]	|
 *  | D				| [average score - 15 , average score - 5} 	|
 *  | F				| [Below, average score - 15}				|
 *  +-----------------------------------------------------------+
 *
 */

#pragma once

using namespace std;

/**
 * export_student_grades_v2_to_console
 *
 * Purpose: Read a text file mentioned above, and calculate the average score for each exam, and then based on the
 * average score of each exam, it will calculate the student's letter grade for the exam. Finally, print each exam's
 * score and letter grade for each student to the console in table format.
 *
 * For example, the text file contains this data:
 * 		5 2
 *		SPWKLZWHCIE GAPCEXAS  99 100
 *		FCCEPWNFVV XJME W  89 89
 *		FKAXVFR MAEPR X  79 86
 *		UJSYE DTULCIC A  69 90
 *		UIPXMS SLOVX  59 100
 *
 * Then, the console output will be like below.
 *    +--------------------------------------------+
 *    |                    |   Exam 0  |   Exam 1  |
 *    +--------------------------------------------+
 *    |Student Name        |Score|Grade|Score|Grade|
 *    +--------------------------------------------+
 *    |SPWKLZWHCIE GAPCEXAS|   99|    A|  100|    B|
 *    |FCCEPWNFVV XJME W   |   89|    B|   89|    C|
 *    |FKAXVFR MAEPR X     |   79|    C|   86|    D|
 *    |UJSYE DTULCIC A     |   69|    D|   90|    C|
 *    |UIPXMS SLOVX        |   59|    F|  100|    B|
 *    +--------------------------------------------+
 *
 * Parameter(s)
 * <1> file_path: The path to the student text file.
 *
 * Precondition(s): N/A
 *
 * Returns: N/A
 *
 * Side effect: N/A
 */
void export_student_grades_v2_to_console(const string &file_path);
