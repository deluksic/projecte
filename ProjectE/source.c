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
// <author>David Emanuel Luk�i�</author>
// <email>deluksic@windowslive.com</email>
// <date>2015-04-05</date>
// <summary>Contains a main function for ASP lab project (FER, secod semester).</summary>

#include "projecte.h"
#include <string.h>

int main()
{
	Student *students;
	Exam *exams;
	unsigned int studcount, examcount, i;
	unsigned int hashes[M] = { 0 };

	students = ReadStudents("pristupnici.txt", &studcount);
	printf("stud count: %d\n", studcount);

	exams = ReadExams("ispiti.txt", &examcount);
	printf("exam count: %d\n", examcount);

	for (i = 0; i < examcount; i++)
		ReadExamFile(&exams[i], students, studcount);

	if (DEBUG)
	{
		for (i = 0; i < studcount; i++)
			printf("student id:%d score:%d\n", students[i].id, students[i].score);
		for (i = 0; i < studcount; i++)
		{
			printf("id:%7d hash:%3d\n", students[i].id, HashAddress((unsigned int)students[i].id));
			hashes[HashAddress(students[i].id)]++;
		}
		printf("Hash distribution: ");
		for (i = 0; i < M; i++)
			printf("%d ", hashes[i]);
		printf("\n");
	}

	//success and wait for enter
	messageexit("Successfuly wrote pristupnici.bin");
	return 0;
}