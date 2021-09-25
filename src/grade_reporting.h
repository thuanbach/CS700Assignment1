/**
 * This module provides functionalities for reading a text file in which each line contains
 * a student's name, the number of exam scores, and exam scores, and then calculate students'
 * average score and letter grade, and finally export them to the console or a CSV file.
 *
 * Here is an example for a line in the text file: SPWKLZWHCIE GAPCEXAS 11 100 88 95 94 98 100 90 71 100 92 98.
 *  + SPWKLZWHCIE GAPCEXAS is the student name.
 *  + 11 is the number of exam scores.
 *  + 100 88 95 94 98 100 90 71 100 92 98 are the exam scores.
 *
 * A student's letter grade will be calculated based on his average score and the below table.
 *  +-------------------------------+
 *  | Letter Grade 	|  Percentage  	|
 *  +-------------------------------+
 *  | A			  	| 95% - 100%	|
 *  | A-			| 91.67%–95%	|
 *  | B+			| 88.3%–91.67%	|
 *  | B				| 85%–88.3% 	|
 *  | B-			| 81.67%–85%	|
 *  | C+			| 78.33%–81.67%	|
 *  | C				| 75%–78.33% 	|
 *  | C-			| 71.67%–75%	|
 *  | D+			| 68.33%–71.67%	|
 *  | D				| 65%–68.33%	|
 *  | D-			| 61.67%–65% 	|
 *  | F				| 0%–61.67%		|
 *  +-------------------------------+
 */

#pragma once

using namespace std;

/**
 * export_student_grades_to_console
 *
 * Purpose: Read a text file mentioned above and print each student's name, average exam score and letter grade to the console in table-like format.
 * For example, the text file has one line with this data: SPWKLZWHCIE GAPCEXAS 11 100 88 95 94 98 100 90 71 100 92 98
 * Then, the console output will be like below.
 *  +--------------------------------------------------------+
 *  | Student Name 			|  Average Exam Score  	|  Grade |
 *  +--------------------------------------------------------+
 *  | SPWKLZWHCIE GAPCEXAS	|	  	93.27			|	A-   |
 *  +--------------------------------------------------------+
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
void export_student_grades_to_console(const string &file_path);


/**
 * export_student_grades_to_directory
 *
 * Purpose: Read a text file mentioned above and write each student's all information in the text file (student name, number of exam scores, the exam scores),
 * the average exam score, and the letter grade to a CSV file in a provided directory. The CSV file name will be formatted with this pattern "Student_Grades_YYYY-MM-DD.csv",
 * in which YYYY-MM-DD is the date of export.
 *
 * Parameter(s)
 * <1> file_path: The path to the text file.
 * <2> export_directory: The directory where the student grades are exported
 * Precondition(s): N/A
 *
 * Returns: N/A
 *
 * Side effect: N/A
 */
void export_student_grades_to_directory(const string &file_path, const string &export_directory);
