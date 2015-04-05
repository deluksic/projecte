// ignore deprecated functions
#ifdef _MSC_VER	
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int id;
	char firstname[20 + 1];
	char lastname[20 + 1];
	int score;
} Student;

typedef struct {
	char filename[30 + 1];
	int scoreThreshold;
} Exam;

char waitforkey();
void errorexit(char* message, int code);
void messageexit(char* message);

Student* ReadStudents(char* filename, int* outCount);
Exam* ReadExams(char* filename, int* outCount);
void ReadExamFile(Exam* exam, Student* students, int studentCount);
Student* FindStudentById(Student* students, int studentCount, int id);