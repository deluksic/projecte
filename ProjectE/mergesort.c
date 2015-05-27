#include "projecte.h"

void SwapStudents(Student *s1, Student *s2)
{
	Student stemp = *s2;
	*s2 = *s1;
	*s1 = stemp;
}

void Merge(Student *studentBegin, Student *temp, int studentCount)
{
	Student *ptemp = temp;
	Student *s1 = studentBegin;
	Student *s2 = studentBegin + studentCount / 2;
	for (ptemp = temp; ptemp < temp + studentCount; ptemp++)
	{
		if (s1 == studentBegin + studentCount / 2)
			*(ptemp) = *(s2++);
		else if (s2 == studentBegin + studentCount || s1->score > s2->score)
			*(ptemp) = *(s1++);
		else
			*(ptemp) = *(s2++);
	}
	ptemp = temp;
	while (ptemp < temp + studentCount)
		*(studentBegin++) = *(ptemp++);
}

void MergeSort(Student *studentBegin, Student *temp, int studentCount)
{
	if (studentCount <= 1) return;
	if (studentCount == 2)
	{
		if (studentBegin->score < (studentBegin + 1)->score)
			SwapStudents(studentBegin, studentBegin + 1);
		return;
	}
	MergeSort(studentBegin, temp, studentCount / 2);
	MergeSort(studentBegin + studentCount / 2, temp, studentCount / 2 + studentCount % 2);
	Merge(studentBegin, temp, studentCount);
}