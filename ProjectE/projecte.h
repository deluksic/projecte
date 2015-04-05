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
} Student;

char waitforkey();
void errorexit(char* message, int code);
void messageexit(char* message);

void ReadStudents(char* filename, Student* outStudents, int* outCount);