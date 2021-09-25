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

using namespace std;



const char DELIMETER = ' ';

typedef struct Student {
	string student_name;
	unsigned int number_of_exam_scores = 0;
	unsigned int *exam_scores;
	float average_exam_score = 0.00f;
	string letter_grade;
};

string generate_student_letter_grade(Student &student) {
	float average_score = student.average_exam_score;

	if (average_score < 61.67f ) {
		return "F";
	} else if (average_score < 65.00f) {
		return "D-";
	} else if (average_score <68.33f){
		return "D";
	} else if (average_score <71.67f){
		return "D+";
	} else if (average_score <75.00f){
		return "C-";
	} else if (average_score < 78.33f){
		return "C";
	} else if (average_score <81.67f){
		return "C+";
	} else if (average_score <85.00f){
		return "B-";
	} else if (average_score <88.30f){
		return "B";
	} else if (average_score <91.67f){
		return "B+";
	} else if (average_score <95.00f){
		return "A-";
	} else {
		return "A";
	}
}



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



void print_students_to_console(const Student students[], unsigned int number_of_students)
{
	const string STUDENT_NAME_HEADER = "Student Name";
	const string AVERAGE_EXAM_SCORE_HEADER = "Average Exam Score";
	const string letter_grade_HEADER = "Grade";

	const char TABLE_HOZIONTAL_BORDER_CHARACTER = '-';
	const char TABLE_VERTICAL_BORDER_CHARACTER = '|';

	const unsigned int AVERAGE_SCORE_WIDTH = 20;
	const unsigned int LETTER_GRADE_WIDTH = 10;
	const unsigned int TOTAL_VERTICAL_BORDER_WIDTH = 5;

	unsigned int student_name_max_length = find_student_name_max_length(students, number_of_students);

	unsigned int TOTAL_TABLE_WIDTH = student_name_max_length + AVERAGE_SCORE_WIDTH + LETTER_GRADE_WIDTH + TOTAL_VERTICAL_BORDER_WIDTH;

	//cout << setfill(TABLE_HOZIONTAL_BORDER_CHARACTER) << setw(TOTAL_TABLE_WIDTH) << TABLE_HOZIONTAL_BORDER_CHARACTER << endl;

	cout << TABLE_VERTICAL_BORDER_CHARACTER << left << setw(student_name_max_length) << STUDENT_NAME_HEADER;
	cout << TABLE_VERTICAL_BORDER_CHARACTER << left << setw(AVERAGE_SCORE_WIDTH) << AVERAGE_EXAM_SCORE_HEADER;
	cout << TABLE_VERTICAL_BORDER_CHARACTER << left << setw(LETTER_GRADE_WIDTH) << letter_grade_HEADER << TABLE_VERTICAL_BORDER_CHARACTER;
	cout << endl;

	//cout << setfill(TABLE_HOZIONTAL_BORDER_CHARACTER) << setw(TOTAL_TABLE_WIDTH) << TABLE_HOZIONTAL_BORDER_CHARACTER << endl;

	for (unsigned int i = 0; i < number_of_students; i++) {
		cout << TABLE_VERTICAL_BORDER_CHARACTER << left << setw(student_name_max_length) << students[i].student_name;
		cout << TABLE_VERTICAL_BORDER_CHARACTER << left << setw(AVERAGE_SCORE_WIDTH) << fixed << setprecision(2) << students[i].average_exam_score;
		cout << TABLE_VERTICAL_BORDER_CHARACTER << left << setw(LETTER_GRADE_WIDTH) << students[i].letter_grade << TABLE_VERTICAL_BORDER_CHARACTER;
		cout << endl;

		//cout << setfill(TABLE_HOZIONTAL_BORDER_CHARACTER) << setw(TOTAL_TABLE_WIDTH) << TABLE_HOZIONTAL_BORDER_CHARACTER << endl;
	}

	//cout << setfill(TABLE_HOZIONTAL_BORDER_CHARACTER) << setw(TOTAL_TABLE_WIDTH) << TABLE_HOZIONTAL_BORDER_CHARACTER << endl;

}

Student extract_student_from_line(string &studentRecord) {
	Student student;

	stringstream ss(studentRecord);
	string item;
	int scoreIndex = 0;

	while (getline(ss, item, DELIMETER)) {
		int token = atoi(item.c_str());
		if (token == 0 && student.number_of_exam_scores == 0) {
			if (student.student_name.empty()) {
				student.student_name.append(item);
			} else {
				student.student_name.append(1, DELIMETER);
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
	for (unsigned int i=0; i<student.number_of_exam_scores; i++){
		total_score += student.exam_scores[i];
	}

	student.average_exam_score = (float) total_score / student.number_of_exam_scores;

	student.letter_grade = generate_student_letter_grade(student);

	return student;
}


void export_student_grades_to_console(const string &file_name)
{
	ifstream inData;

	inData.open(file_name);

	string line;

	unsigned int student_index = 0;
	unsigned int number_of_students = 0;

	Student students[100];

	while (getline(inData, line)) {
		students[student_index] = extract_student_from_line(line);
		student_index++;
	}

	number_of_students = student_index;

	inData.close();

	print_students_to_console(students, number_of_students);
}

int main() {

	string student_exam_scores_raw_file = "resource/grades_Section1.txt";

	export_student_grades_to_console(student_exam_scores_raw_file);

	return 0;
}
