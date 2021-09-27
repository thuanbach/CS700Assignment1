/**
 * grade_reporting_v2.cpp
 *
 *  Created on: Sep 26, 2021
 *      Author: Thuan Bach
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <iomanip>

using namespace std;


const string STUDENT_NAME_HEADER = "Student Name";
const string EXAM_HEADER = "Exam";
const string SCORE_HEADER = "Score";
const string GRADE_HEADER = "Grade";

const char DELIMITER = ' ';
const char BLANK_CHARACTER = ' ';
const char PLUS_CHARACTER = '+';

const char TABLE_HORIZONTAL_BORDER_CHARACTER = '-';
const char TABLE_VERTICAL_BORDER_CHARACTER = '|';
const unsigned int EXAM_HEADER_PADDING_WIDTH = 3;

const unsigned int NUMBER_OF_BORDER_PER_EXAM = 2;
const unsigned int NUMBER_OF_BORDER_PER_EXAM_HEADER = 1;

const unsigned int SCORE_COLUMN_WITH = 5;
const unsigned int GRADE_COLUMN_WITH = 5;


struct StudentsData {
    unsigned int number_of_students;
    unsigned int number_of_exams;

    /**
     * An array of string objects to store names of students
     */
    string *student_names;

    /**
     * A two-dimensional array to store scores of exams of students.
     * The row subscript is the student number, and the column subscript is the exam number
     */
    unsigned int **exam_scores;

    /**
     * A two-dimensional array to store grades of exams of students.
     * The row subscript is the student number, and the column subscript is the exam number
     */
    char **exam_grades;

    /**
     * An array of float number to store the average score of each exam.
     */
    float *average_scores_per_exam;
};

/**
 * Initiate StudentsData's arrays based on the number students and the number of exams.
 *
 * Parameter(s)
 * <1> An StudentsData object
 *
 * Returns: N/A
 */
void initiate_students_data(StudentsData &studentsData) {

    unsigned int number_of_students = studentsData.number_of_students;
    unsigned int number_of_exams = studentsData.number_of_exams;

    studentsData.student_names = new string[number_of_students];

    studentsData.exam_scores = new unsigned int *[number_of_students];
    studentsData.exam_grades = new char *[number_of_students];

    for (unsigned int i = 0; i < number_of_students; i++) {
        studentsData.exam_scores[i] = new unsigned int[number_of_exams];
        studentsData.exam_grades[i] = new char[number_of_exams];
    }

    studentsData.average_scores_per_exam = new float[number_of_exams];
}


/**
 * Parse a student' information from a text, and update to StudentsData at the provided index.
 *
 * Parameter(s)
 * <1> A string object presenting a student information in the text file
 * <2> A StudentsData object
 * <3> The student index in the file.
 *
 * Returns: N/A
 */
void parse_a_student_from_raw_text_line(string &studentRawText,
                                        StudentsData &studentsData,
                                        unsigned int student_index) {
    stringstream ss(studentRawText);
    string word;

    unsigned int examIndex = 0;

    while (getline(ss, word, DELIMITER)) {

        if (word.empty()) continue;

        int numericToken = atoi(word.c_str());

        if (numericToken == 0) {
            if (studentsData.student_names[student_index].empty()) {
                studentsData.student_names[student_index] = word;

            } else {
                studentsData.student_names[student_index].append(1, DELIMITER);
                studentsData.student_names[student_index].append(word);
            }

        } else {

            studentsData.exam_scores[student_index][examIndex] = numericToken;
            examIndex++;
        }
    }
}

/**
 * Generate the exam grade
 *
 * Parameter(s)
 * <1> The score of an exam of a student
 * <2> The average score of the exam among students
 *
 * Returns: A character presenting the exam grade
 */
char generate_grade_letter(const unsigned int student_exam_score, const float average_exam_score) {

    if (student_exam_score > average_exam_score + 15) {
        return 'A';
    } else if (student_exam_score > average_exam_score + 5) {
        return 'B';
    } else if (student_exam_score >= average_exam_score - 5) {
        return 'C';
    } else if (student_exam_score >= average_exam_score - 15) {
        return 'D';
    } else {
        return 'F';
    }
}

/**
 * Parse number of students and exams from the first line of the text file, and update them to StudentsData object
 *
 * Parameter(s)
 * <1> The first line of the input text
 * <2> A StudentsData object
 *
 * Returns: N/A
 */

void parse_number_of_students_and_exams(const string firstLine, StudentsData &studentData) {

    stringstream ss(firstLine);
    string word;

    int index = 0;
    while (getline(ss, word, DELIMITER)) {
        int numericToken = atoi(word.c_str());
        if (index == 0) {
            studentData.number_of_students = numericToken;
        } else {
            studentData.number_of_exams = numericToken;
        }
        index++;
    }
}

/**
 * Parse a text file and return a StudentsData object
 *
 * Parameter(s)
 * <1> Path to the text file
 *
 * Returns: A StudentsData object
 */
StudentsData read_student_exam_scores_from_file(const string &file_path) {

    StudentsData studentsData;

    ifstream inData;

    inData.open(file_path);


    string firstLine;
    getline(inData, firstLine);

    parse_number_of_students_and_exams(firstLine, studentsData);
    initiate_students_data(studentsData);


    string studentRawText;

    unsigned int student_index = 0;

    while (getline(inData, studentRawText)) {
        parse_a_student_from_raw_text_line(studentRawText, studentsData, student_index);
        student_index++;
    }


    for (unsigned exam_index = 0; exam_index < studentsData.number_of_exams; exam_index++) {
        unsigned int totalScorePerExam = 0;

        for (unsigned int student_index = 0; student_index < studentsData.number_of_students; student_index++) {
            totalScorePerExam += studentsData.exam_scores[student_index][exam_index];
        }

        studentsData.average_scores_per_exam[exam_index] = (float) totalScorePerExam / studentsData.number_of_students;
    }

    for (unsigned int student_index = 0; student_index < studentsData.number_of_students; student_index++) {

        for (unsigned exam_index = 0; exam_index < studentsData.number_of_exams; exam_index++) {

            studentsData.exam_grades[student_index][exam_index] =
                    generate_grade_letter(studentsData.exam_scores[student_index][exam_index],
                                          studentsData.average_scores_per_exam[exam_index]);

        }
    }

    inData.close();

    return studentsData;
}

/**
 * Find the max length among names of students
 *
 * Parameter(s)
 * <1> A StudentsData object
 *
 * Returns: The max length among names of students
 */
unsigned int find_student_name_max_length(StudentsData studentsData) {

    unsigned int student_name_max_length = 0;

    for (unsigned int i = 0; i < studentsData.number_of_students; i++) {
        if (studentsData.student_names[i].length() > student_name_max_length) {
            student_name_max_length = studentsData.student_names[i].length();
        }
    }

    return student_name_max_length;
}

/**
 * Print each exam's score and letter grade for each student to the console in table format.
 *
 * Parameter(s)
 * <1> A StudentsData object
 *
 * Returns: N/A
 */
void print_students_data_to_console(StudentsData studentsData) {



    unsigned int student_name_max_length = find_student_name_max_length(studentsData);

    unsigned int TOTAL_TABLE_WIDTH =
            student_name_max_length +
            (SCORE_COLUMN_WITH + GRADE_COLUMN_WITH + NUMBER_OF_BORDER_PER_EXAM) * studentsData.number_of_exams;

    // Create the table header's horizontal line border
    cout << PLUS_CHARACTER << setfill(TABLE_HORIZONTAL_BORDER_CHARACTER) << setw(TOTAL_TABLE_WIDTH)
         << TABLE_HORIZONTAL_BORDER_CHARACTER << PLUS_CHARACTER << setfill(BLANK_CHARACTER) << endl;

    cout << TABLE_VERTICAL_BORDER_CHARACTER << setw(student_name_max_length) << BLANK_CHARACTER
         << TABLE_VERTICAL_BORDER_CHARACTER;

    for (unsigned int i = 0; i < studentsData.number_of_exams; i++) {
        cout << left << setw(EXAM_HEADER_PADDING_WIDTH) << BLANK_CHARACTER
             << setw(SCORE_COLUMN_WITH + GRADE_COLUMN_WITH + NUMBER_OF_BORDER_PER_EXAM_HEADER -
                     EXAM_HEADER_PADDING_WIDTH)
             << EXAM_HEADER + BLANK_CHARACTER + to_string(i+1) << TABLE_VERTICAL_BORDER_CHARACTER;
    }
    cout << endl;
    cout << PLUS_CHARACTER << setfill(TABLE_HORIZONTAL_BORDER_CHARACTER) << setw(TOTAL_TABLE_WIDTH)
         << TABLE_HORIZONTAL_BORDER_CHARACTER << PLUS_CHARACTER << setfill(BLANK_CHARACTER) << endl;

    // Create the table header
    cout << TABLE_VERTICAL_BORDER_CHARACTER << left << setw(student_name_max_length) << STUDENT_NAME_HEADER
         << TABLE_VERTICAL_BORDER_CHARACTER;
    for (unsigned int i = 0; i < studentsData.number_of_exams; i++) {
        cout << SCORE_HEADER << TABLE_VERTICAL_BORDER_CHARACTER << GRADE_HEADER << TABLE_VERTICAL_BORDER_CHARACTER;
    }
    cout << endl;

    cout << PLUS_CHARACTER << setfill(TABLE_HORIZONTAL_BORDER_CHARACTER) << setw(TOTAL_TABLE_WIDTH)
         << TABLE_HORIZONTAL_BORDER_CHARACTER << PLUS_CHARACTER << setfill(BLANK_CHARACTER) << endl;

    for (unsigned int i = 0; i < studentsData.number_of_students; i++) {
        cout << left << TABLE_VERTICAL_BORDER_CHARACTER << setw(student_name_max_length)
             << studentsData.student_names[i] << TABLE_VERTICAL_BORDER_CHARACTER;
        for (unsigned int j = 0; j < studentsData.number_of_exams; j++) {
            cout << right << setw(SCORE_COLUMN_WITH) << studentsData.exam_scores[i][j]
                 << TABLE_VERTICAL_BORDER_CHARACTER;
            cout << setw(GRADE_COLUMN_WITH) << studentsData.exam_grades[i][j] << TABLE_VERTICAL_BORDER_CHARACTER;
        }
        cout << endl;
    }

    cout << PLUS_CHARACTER << setfill(TABLE_HORIZONTAL_BORDER_CHARACTER) << setw(TOTAL_TABLE_WIDTH)
         << TABLE_HORIZONTAL_BORDER_CHARACTER << PLUS_CHARACTER << setfill(BLANK_CHARACTER) << endl;
}

/**
 * Read a text file mentioned in the grade reporting.h, and calculate the average score for each exam, and then based
 * on the average score of each exam, it will calculate the student's letter grade for the exam. Finally, print each
 * exam's score and letter grade for each student to the console in table format.
 *
 * Parameter(s)
 * <1> A path to the text file.
 *
 * Returns: N/A
 *
 */
void export_student_grades_v2_to_console(const string &file_path) {
    StudentsData studentsData = read_student_exam_scores_from_file(file_path);
    print_students_data_to_console(studentsData);
}

