// ignore deprecated functions
#ifdef _MSC_VER	
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <stdlib.h>

typedef struct
{
	unsigned int id;
	char firstname[20 + 1];
	char lastname[20 + 1];
	unsigned int score;
	unsigned int passedexams;
} Student;

typedef struct
{
	char filename[30 + 1];
	int scoreThreshold;
} Exam;

#define DEBUG 0

#define BLOK 512L		// block on the disk
#define N 1000				// expected number of entries  
#define C ((int) (BLOK / sizeof (Student)))	// number of entries per slot
#define M ((int) (N / C * 1.3))	// number of slots. Size is 30% bigger than minimum.

char waitforkey();
void errorexit(char *message, int code);
void messageexit(char *message);
void debugprint(char *message);
void messagewait(char *message);

Student slot[C];

Student* ReadStudents(char *filename, int *outCount);
Student* ReadStudentsBin(char *filename, int *outCount);
Exam* ReadExams(char *filename, int *outCount);
void ReadExamFile(Exam *exam, Student *students, int studentCount);
Student* FindStudentById(Student *students, int studentCount, int id);

unsigned int HashAddress(unsigned int x);
void WriteStudents(char *filename, Student *students, int studentCount);
void WriteStudentsCond(char *filename, Student *students, int studentCount, int examCount);
void WriteStudentsBin(char *filename, Student *students, int studentCount);
void PrintStudents(Student *studentBegin, int studentCount);
void PrepareTable(FILE *ft);

void MergeSort(Student *studentBegin, Student *temp, int studentCount);
void QuickSort(Student *s1, Student *s2);
void SwapStudents(Student *s1, Student *s2);
void SwapStudentsCond(Student *s1, Student *s2);
void SortThreeStudents(Student *s1, Student *s2, Student *s3);