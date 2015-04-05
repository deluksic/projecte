// <copyright file="source.cpp" company="deluksic">
// Copyright (c) 2015 All Right Reserved
//
// This source is subject to the Microsoft Permissive License.
// Please see the License.txt file for more information.
// All other rights reserved.
//
// THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY 
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// </copyright>
// <author>David Emanuel Lukšiæ</author>
// <email>deluksic@windowslive.com</email>
// <date>2015-04-05</date>
// <summary>Contains a main function for ASP lab project (FER, secod semester).</summary>

#include "projecte.h"
#include <string.h>

int main(){
	Student *students;
	int studcount;
	Exam *exams;
	int examcount;

	students = ReadStudents("pristupnici.txt", &studcount);
	printf("stud count: %d\n", studcount);

	exams = ReadExams("ispiti.txt", &examcount);
	printf("exam count: %d\n", examcount);

	ReadExamFile(exams[1].filename, students, studcount);

	// success and wait for enter
	messageexit("Successfuly wrote pristupnici.bin");
	return 0;
}