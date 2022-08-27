/**
 * grade_reporting.cpp
 *
 *  Created on: Sep 25, 2021
 *  Author: Thuan Bach
 *
 *  The purpose of this module is to implement functionalities mentioned in grade_reporting.h
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <iomanip>

using namespace std;

const unsigned int MAX_STUDENT_LINE_LENGTH = 1000;

const string STUDENT_NAME_HEADER = "Student Name";
const string AVERAGE_EXAM_SCORE_HEADER = "Average Exam Score";
const string LETTER_GRADE_HEADER = "Grade";
const string NUMBER_OF_SCORE_HEADER = "Number of Exam Scores";

const string STUDENT_GRADE_EXPORTED_FILE_NAME = "Student_Grades";
const string STUDENT_GRADE_EXPORTED_FILE_FORMAT = ".csv";

const char FILE_SEPARATOR = '/';
const char CSV_SEPARATOR = ',';
const char DELIMITER = ' ';
const char BLANK_CHARACTER = ' ';
const char PLUS_CHARACTER = '+';

const char TABLE_HORIZONTAL_BORDER_CHARACTER = '-';
const char TABLE_VERTICAL_BORDER_CHARACTER = '|';

const unsigned int AVERAGE_SCORE_WIDTH = 18;
const unsigned int AVERAGE_SCORE_LEFT_PADDING_WIDTH = 7;
const unsigned int LETTER_GRADE_WIDTH = 5;
const unsigned int LETTER_GRADE_LEFT_PADDING_WIDTH = 2;
const unsigned int TOTAL_VERTICAL_BORDER_WIDTH = 2;

struct Student {
    string student_name;
    unsigned int number_of_exam_scores = 0;
    unsigned int *exam_scores;
    float average_exam_score = 0.00f;
    string letter_grade;
};

/**
 * Generate the letter grade based on a student's average exam score.
 *
 * Parameter(s)
 * <1>: A Student object
 *
 * Returns: A letter grade
 */

string generate_student_letter_grade(Student &student) {
    float average_score = student.average_exam_score;

    if (average_score < 61.67f) {
        return "F";
    } else if (average_score < 65.00f) {
        return "D-";
    } else if (average_score < 68.33f) {
        return "D";
    } else if (average_score < 71.67f) {
        return "D+";
    } else if (average_score < 75.00f) {
        return "C-";
    } else if (average_score < 78.33f) {
        return "C";
    } else if (average_score < 81.67f) {
        return "C+";
    } else if (average_score < 85.00f) {
        return "B-";
    } else if (average_score < 88.30f) {
        return "B";
    } else if (average_score < 91.67f) {
        return "B+";
    } else if (average_score < 95.00f) {
        return "A-";
    } else {
        return "A";
    }
}

/**
 * Find the maximum length of names of students.
 *
 * Parameter(s)
 * <1>: A array of Student objects
 * <2>: The number of students in the array
 *
 * Returns: The maximum length of names of students
 */
unsigned int find_student_name_max_length(const Student students[],
                                          unsigned int number_of_students) {
    unsigned int student_name_max_length = 0;

    for (unsigned int i = 0; i < number_of_students; i++) {
        if (students[i].student_name.length() > student_name_max_length) {
            student_name_max_length = students[i].student_name.length();
        }
    }

    return student_name_max_length;
}

/**
 * Print students' name, average exam score, and letter grade to the console.
 *
 * Parameter(s)
 * <1>: A array of Student objects
 * <2>: Number of students in the array
 *
 * Returns: N/A
 */

void print_student_grades_to_console(const Student students[], unsigned int number_of_students) {

    unsigned int student_name_max_length = find_student_name_max_length(students, number_of_students);

    unsigned int TOTAL_TABLE_WIDTH =
            student_name_max_length + AVERAGE_SCORE_WIDTH + LETTER_GRADE_WIDTH + TOTAL_VERTICAL_BORDER_WIDTH;

    // Create the table header's horizontal line border
    cout << PLUS_CHARACTER << setfill(TABLE_HORIZONTAL_BORDER_CHARACTER) << setw(TOTAL_TABLE_WIDTH)
         << TABLE_HORIZONTAL_BORDER_CHARACTER << PLUS_CHARACTER << setfill(BLANK_CHARACTER) << endl;

    // Create the table header
    cout << TABLE_VERTICAL_BORDER_CHARACTER << left << setw(student_name_max_length) << STUDENT_NAME_HEADER;
    cout << TABLE_VERTICAL_BORDER_CHARACTER << left << setw(AVERAGE_SCORE_WIDTH) << AVERAGE_EXAM_SCORE_HEADER;
    cout << TABLE_VERTICAL_BORDER_CHARACTER << left << setw(LETTER_GRADE_WIDTH) << LETTER_GRADE_HEADER
         << TABLE_VERTICAL_BORDER_CHARACTER;
    cout << endl;

    // Create a horizontal line border to close the table header
    cout << PLUS_CHARACTER << setfill(TABLE_HORIZONTAL_BORDER_CHARACTER) << setw(TOTAL_TABLE_WIDTH)
         << TABLE_HORIZONTAL_BORDER_CHARACTER << PLUS_CHARACTER << setfill(BLANK_CHARACTER) << endl;

    for (unsigned int i = 0; i < number_of_students; i++) {
        // Print each student's information to the console as a row of the table
        cout << TABLE_VERTICAL_BORDER_CHARACTER << left << setw(student_name_max_length) << students[i].student_name;
        cout << TABLE_VERTICAL_BORDER_CHARACTER << left << setw(AVERAGE_SCORE_LEFT_PADDING_WIDTH) << BLANK_CHARACTER
             << setw(AVERAGE_SCORE_WIDTH - AVERAGE_SCORE_LEFT_PADDING_WIDTH) << fixed << setprecision(2)
             << students[i].average_exam_score;
        cout << TABLE_VERTICAL_BORDER_CHARACTER << left << setw(LETTER_GRADE_LEFT_PADDING_WIDTH) << BLANK_CHARACTER
             << setw(LETTER_GRADE_WIDTH - LETTER_GRADE_LEFT_PADDING_WIDTH) << students[i].letter_grade
             << TABLE_VERTICAL_BORDER_CHARACTER;
        cout << endl;
    }

    // Create a horizontal line border to close table
    cout << PLUS_CHARACTER << setfill(TABLE_HORIZONTAL_BORDER_CHARACTER) << setw(TOTAL_TABLE_WIDTH)
         << TABLE_HORIZONTAL_BORDER_CHARACTER << PLUS_CHARACTER << setfill(BLANK_CHARACTER) << endl;

}

/**
 * Parse a line of the input text file to a Student object
 *
 * Parameter(s)
 * <1>: a string presenting student information: names, number of exam scores, and exam scores
 *
 * Returns: A Student object
 */

Student parse_student_from_line(string &studentRawText) {
    Student student;

    stringstream ss(studentRawText);
    string item;
    int scoreIndex = 0;

    while (getline(ss, item, DELIMITER)) {
        int token = atoi(item.c_str());
        if (token == 0 && student.number_of_exam_scores == 0) {
            if (student.student_name.empty()) {
                student.student_name.append(item);
            } else {
                student.student_name.append(1, DELIMITER);
                student.student_name.append(item);
            }
        } else {
            if (student.number_of_exam_scores == 0) {
                student.number_of_exam_scores = token;
                student.exam_scores =
                        new unsigned int[student.number_of_exam_scores];
            } else {
                student.exam_scores[scoreIndex] = token;
                scoreIndex++;
            }
        }
    }

    int total_score = 0;
    for (unsigned int i = 0; i < student.number_of_exam_scores; i++) {
        total_score += student.exam_scores[i];
    }

    student.average_exam_score = (float) total_score / student.number_of_exam_scores;

    student.letter_grade = generate_student_letter_grade(student);

    return student;
}

/**
 * Read the text file, and convert it into an array of Student objects
 *
 * Parameter(s)
 * <1>: Path to the text file
 * <2>: An array of Student objects to hold students' information parsed from the text file
 *
 * Returns: The number of students read from the text file
 */
unsigned int read_student_exam_scores_from_file(const string &file_path, Student students[]) {
    ifstream inData;

    inData.open(file_path);

    string line;

    unsigned int student_index = 0;

    while (getline(inData, line)) {
        students[student_index] = parse_student_from_line(line);
        student_index++;
    }

    inData.close();

    return student_index;
}

/**
 * Find the maximum number of exam scores among students
 *
 * Parameter(s)
 * <1>: A array of Student objects
 * <2>: Number of students in the array
 *
 * Returns: The maximum number of exam scores among students
 */

unsigned int find_max_number_of_exam_scores(const Student students[], unsigned int number_of_students) {

    unsigned int max_number = 0;

    for (unsigned int i = 0; i < number_of_students; i++) {
        if (max_number < students[i].number_of_exam_scores) {
            max_number = students[i].number_of_exam_scores;
        }
    }

    return max_number;
}

/**
 * Write students' name, number of score, exam scores, average exam score, and grade to the CVS file. The CSV file name
 * will be "Student_Grades.csv".
 *
 * Parameter(s)
 * <1>: An array of Student objects to hold students' information parsed from the text file
 * <2>: Number of students in the array.
 * <3>: The folder path where the CSV is written to.
 *
 * Returns: The number of students read from the text file
 */

void write_student_grades_to_file(const Student students[], unsigned int number_of_students,
                                  const string &export_directory) {

    ofstream exportedFile;

    exportedFile.open(
            export_directory + FILE_SEPARATOR + STUDENT_GRADE_EXPORTED_FILE_NAME + STUDENT_GRADE_EXPORTED_FILE_FORMAT);

    cout << "Start exporting student grades to the export folder: " << export_directory << endl;

    unsigned int max_of_exam_scores = find_max_number_of_exam_scores(students, number_of_students);

    exportedFile << quoted(STUDENT_NAME_HEADER) << CSV_SEPARATOR << NUMBER_OF_SCORE_HEADER << CSV_SEPARATOR;

    for (unsigned int i = 0; i < max_of_exam_scores; i++) {
        exportedFile << CSV_SEPARATOR;
    }

    exportedFile << quoted(AVERAGE_EXAM_SCORE_HEADER) << CSV_SEPARATOR << LETTER_GRADE_HEADER << endl;

    for (unsigned int i = 0; i < number_of_students; i++) {
        exportedFile << quoted(students[i].student_name) << CSV_SEPARATOR;
        exportedFile << students[i].number_of_exam_scores << CSV_SEPARATOR;


        for (unsigned int j = 0; j < max_of_exam_scores; j++) {
            if (j < students[i].number_of_exam_scores) {
                exportedFile << students[i].exam_scores[j] << CSV_SEPARATOR;
            } else {
            	// create an empty column if the student's exam score is not available.
                exportedFile << CSV_SEPARATOR;
            }
        }


        exportedFile << fixed << setprecision(2) << students[i].average_exam_score << CSV_SEPARATOR
                     << quoted(students[i].letter_grade) << endl;
    }

    cout << "Exported successfully" << endl;

    exportedFile.close();
}

/**
 * Read a text file and print each student's name, average exam score, and letter grade to the console in table-like format
 *
 * Parameter(s)
 * <1>: Path to the text file
 *
 * Returns: N/A
 */
void export_student_grades_to_console(const string &file_path) {
    Student students[MAX_STUDENT_LINE_LENGTH];

    int number_of_students = read_student_exam_scores_from_file(file_path, students);

    print_student_grades_to_console(students, number_of_students);
}

/**
 * Read a text file and write each student's all information in the text file (student name, number of exam scores, the
 * exam scores), the average exam score, and the letter grade to a CSV file in a provided directory. The CSV file name
 * will be "Student_Grades.csv".
 *
 * Parameter(s)
 * <1> file_path: The path to the text file.
 * <2> export_directory: The directory where the student grades are exported
 *
 * Returns: N/A
 */

void export_student_grades_to_directory(const string &file_path, const string &export_directory) {
    Student students[MAX_STUDENT_LINE_LENGTH];

    int number_of_students = read_student_exam_scores_from_file(file_path, students);

    write_student_grades_to_file(students, number_of_students, export_directory);
}
