#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>

using namespace std;

//****************************
//    StudentType Structure
//****************************
struct StudentType
{
	string studentFName;	//first name		 
	string studentLName;	//last name
	int testScore;			
	char grade;				//letter grade
};

//***************************
//   Function Prototypes
//***************************
void pullStudentData(StudentType *student);
void assignGrade(StudentType *student);
void findHighestScore(StudentType student[], int &highScore);
bool highScorer(StudentType student, int highscore);
void outputStudentData(StudentType *student, int studentArraySize, int highScore);

//*************************
//   Global Constants
//*************************
const int LIST_SIZE = 20;

int main()
{
	StudentType studentList[LIST_SIZE];
	int highScore = 0;
	int x = 0;

	pullStudentData(studentList);
	assignGrade(studentList);
	findHighestScore(studentList, highScore);
	outputStudentData(studentList, LIST_SIZE, highScore);

	system("pause");
	return 0;
}// end main

//***************************
//   Function Definitions
//***************************

//**************************************
//Pull student data from Data.txt file
//Save into array of students
//**************************************
void pullStudentData(StudentType *student) {
	ifstream studentData;

	cout << "Opening file....\n";

	studentData.open("Data.txt", ios::in);

	if (studentData.fail()) {
		cout << "File open fail\n";
	}
	else {
		cout << "Writing to file...\n";
	}

	//Assign data from file to studentList array
	for (int i = 0; i < LIST_SIZE; i++) {
		studentData >> student[i].studentFName;
		studentData >> student[i].studentLName;
		studentData >> student[i].testScore;
	}

	studentData.close();
}// end pullStudentData

//****************************************************************
//Assigning appropriate grade to each student based on test score
//****************************************************************
void assignGrade(StudentType *student) {
	
	for (int i = 0; i < LIST_SIZE; i++) {
		if (student[i].testScore > 89) {
			student[i].grade = 'A';
		}

		if (student[i].testScore > 79 && student[i].testScore < 90) {
			student[i].grade = 'B';
		}

		if (student[i].testScore > 69 && student[i].testScore < 80) {
			student[i].grade = 'C';
		}

		if (student[i].testScore > 59 && student[i].testScore < 70) {
			student[i].grade = 'D';
		}

		if (student[i].testScore < 60) {
			student[i].grade = 'F';
		}
	}
}// end assignGrade

//********************************************************
//Step through student test scores and find highest score
//********************************************************
void findHighestScore(StudentType student[], int &highScore) {
	for (int i = 0; i < LIST_SIZE; i++)
	{
		if (student[i].testScore > student[i+1].testScore) {
			highScore = student[i].testScore;
		}
	}
}//end findHighestScore

//************************************
//Find students who got highest score
//************************************
bool highScorer(StudentType student, int highscore) {
	 bool hiScoreStudent = false;
		if (student.testScore == highscore) {
			hiScoreStudent = true;
		}

	return hiScoreStudent;
}//end highScorer

//************************************************************
//Print table of student names, test scores, and letter grade
//Print high score and students who got high score
//If file fails to open, program exit
//************************************************************
void outputStudentData(StudentType *student, int studentArraySize, int highScore) {
	ofstream outStudentData;

	outStudentData.open("Out.txt", ios::out); //Create file for output

	//Exit program if output file fails to create
	if (outStudentData.fail()) {
		cout << "Failed to create file...." << endl;
		system("pause");
		exit(0);
	}
	
	//Table header
	outStudentData << "Student Name";
	outStudentData << setw(20) << "Test Score";
	outStudentData << setw(10) << "Grade";
	outStudentData << "\n-----------------------------------------------\n";

	//Print each student's name, score, and grade
	for (int i = 0; i < LIST_SIZE; i++)
	{
		int nameLength;
		string studentName = student[i].studentLName;
		studentName += ", ";
		studentName += student[i].studentFName;

		nameLength = studentName.length();

		int firstCol = 27 - nameLength; //set first column print field to 29 spaces

		outStudentData << left << studentName;
		outStudentData << right << setw(firstCol) << student[i].testScore; //add firstCol spaces before test scores
		outStudentData << right << setw(13) << student[i].grade << endl;
	}
	outStudentData << "-----------------------------------------------\n";

	//Print high score
	outStudentData << "\nHigh score is: " << highScore << endl;

	//Print students who got high score with highScorer function
	outStudentData << "\nStudents that got the high score:\n";
	for (int i = 0; i < LIST_SIZE; i++)
	{
		if (highScorer(student[i], highScore)) {
			outStudentData << student[i].studentLName << ", " << student[i].studentFName << endl;
		}
	}
}//end outputStudentData
