#include "projecte.h"

void SwapStudents(Student *s1, Student *s2)
{
	Student stemp = *s2;
	*s2 = *s1;
	*s1 = stemp;
}

void SwapStudentsCond(Student *s1, Student *s2)
{
	Student stemp = *s2;
	if (s1->score < s2->score)
	{
		*s2 = *s1;
		*s1 = stemp;
	}
}

void SortThreeStudents(Student *s1, Student *s2, Student *s3)
{
	SwapStudentsCond(s1, s2);
	SwapStudentsCond(s1, s3);
	SwapStudentsCond(s2, s3);
}

void QuickSort(Student *s1, Student *s2)
{
	Student *piv, *left, *right;

	if (s1 == s2) return;
	if (s2 == s1 + 1)
	{
		SwapStudentsCond(s1, s2);
		return;
	}
	if (s2 - s1 == 2)
	{
		SortThreeStudents(s1, s1 + 1, s2);
		return;
	}

	// choose a pivot, and sort first, pivot and last
	piv = s1 + (s2 - s1 + 1) / 2;
	SortThreeStudents(s1, piv, s2);
	// swap pivot for the last element to move it aside
	SwapStudents(piv, s2);
	
	left = s1;
	right = s2 - 1;

	while (1)
	{
		while (left->score > s2->score && left != right) left++;
		while (right->score <= s2->score && right != left) right--;
		if (left != right)
			SwapStudents(left, right);
		else
			break;
	}
	// return pivot
	SwapStudents(right, s2);
	QuickSort(s1, right);
	QuickSort(right + 1, s2);
}