#include "projecte.h"

// reads student entries from filename and saves 
// them into memory on outStudents location.
// Writes number of entries into outCount.
Student* ReadStudents(char *filename, int *outCount)
{
	Student* students = (Student*)malloc(sizeof(Student));
	FILE *fstudents;
	int i, count, nextid;
	char ch;

	// read pristupnici.txt, format: id#firstname#lastname
	if ((fstudents = fopen(filename, "r")) == NULL)
		errorexit("File \"pristupnici.txt\" not found.", 404);

	count = 0;
	nextid = 0;
	while (fscanf(fstudents, "%d", &nextid) == 1)
	{
		if ((students = (Student*)realloc(students, sizeof(Student) * (count + 1))) == NULL)
			errorexit("Failed to allocate memory while reading.", 200);

		// if the next char is not #, errorexit!
		if (fscanf(fstudents, "%c", &ch) == 1 && ch != '#')
			errorexit("Error in reading student line.", 101);

		// write id
		students[count].id = nextid;

		// read first name
		i = 0;
		while (fscanf(fstudents, "%c", &ch) == 1 && ch != '#')
		{
			students[count].firstname[i++] = ch;
			if (i == 22)
				errorexit("Error in reading student line.", 102);
		}
		// terminate with 0
		students[count].firstname[i] = 0;

		// read last name
		i = 0;
		while (fscanf(fstudents, "%c", &ch) == 1 && ch != '#' && ch != '\n')
		{
			students[count].lastname[i++] = ch;
			if (i == 22)
				errorexit("Error in reading student line.", 103);
		}
		// terminate with 0
		students[count].lastname[i] = 0;
		// reset score
		students[count].score = 0;
		// reset passed exams
		students[count].passedexams = 0;

		if (DEBUG)
			printf(
			"stud entry: %d, %s, %s\n",
			students[count].id,
			students[count].firstname,
			students[count].lastname
			);
		count++;
	}
	fclose(fstudents);
	*outCount = count;
	return students;
}

Student* ReadStudentsBin(char *filename, int *outCount)
{
	Student* students = (Student*)malloc(sizeof(Student));
	FILE *fstudents;
	int i, j, count, nextid;
	char ch;

	count = 0;
	// read pristupnici.bin
	if ((fstudents = fopen(filename, "rb")) == NULL)
		errorexit("File \"pristupnici.bin\" not found.", 404);

	for (i = 0; i < M; i++)
	{
		fseek(fstudents, i*BLOK, SEEK_SET);
		fread(slot, sizeof(slot), 1, fstudents);
		for (j = 0; j < C; j++)
		{
			if (slot[j].id == 0)
				continue;

			if ((students = (Student*)realloc(students, sizeof(Student) * (count + 1))) == NULL)
				errorexit("Failed to allocate memory while reading.", 200);

			students[count++] = slot[j];
		}

	}

	fclose(fstudents);
	*outCount = count;
	return students;
}

// reads student entries from filename and saves 
// them into memory on outStudents location.
// Writes number of entries into outCount.
Exam* ReadExams(char *filename, int *outCount)
{
	Exam* exams = (Exam*)malloc(sizeof(Exam));
	FILE *fexams;
	int i, count;
	char ch;

	// read ispiti.txt, format: filename#mintreshold
	if ((fexams = fopen(filename, "r")) == NULL)
		errorexit("File \"ispiti.txt\" not found.", 404);

	count = 0;
	while (1)
	{
		if ((exams = (Exam*)realloc(exams, sizeof(Exam) * (count + 1))) == NULL)
			errorexit("Failed to allocate memory while reading.", 200);

		// read filename
		i = 0;
		while (fscanf(fexams, "%c", &ch) == 1 && ch != '#')
		{
			exams[count].filename[i++] = ch;
			if (i == 22)
				errorexit("Error in reading exam line.", 104);
		}
		// terminate with 0
		exams[count].filename[i] = 0;

		// read score threshold (the previous # is taken already 
		// and we are ready to read threshold value)
		if (fscanf(fexams, "%d", &exams[count].scoreThreshold) != 1)
			errorexit("Error in reading exam line.", 105);

		printf("exam entry: %s, %d\n", exams[count].filename, exams[count].scoreThreshold);
		count++;

		if (fscanf(fexams, "%c", &ch) != 1 || ch == EOF)
			break;
	}
	fclose(fexams);
	*outCount = count;
	return exams;
}

// reads student entries from filename and saves 
// them into memory on outStudents location.
// Writes number of entries into outCount.
void ReadExamFile(Exam *exam, Student *students, int studentCount)
{
	FILE *fexam;
	Student *currstud;
	int id, score;

	printf("Reading file %s\n", (*exam).filename);

	// read ispiti.txt, format: filename#mintreshold
	if ((fexam = fopen((*exam).filename, "r")) == NULL)
		errorexit("File \"predmet.txt\" not found.", 404);

	while (fscanf(fexam, "%d#%d", &id, &score) == 2)
	{
		if (score < (*exam).scoreThreshold)
		{
			if (DEBUG)
				printf("student with id:%d failed this exam.\n", id);
			continue;
		}
		else
		{
			if ((currstud = FindStudentById(students, studentCount, id)) != NULL)
			{
				(*currstud).score += score;
				(*currstud).passedexams += 1;
				if (DEBUG)
					printf("exam result: id:%d, score:%d\n", id, score);
			}
			else
			{
				if (DEBUG)
					printf("Student with id %d doesn't exist.\n", id);
			}
		}
	}
	fclose(fexam);
}

// O(n) search through array by id
Student* FindStudentById(Student *students, int studentCount, int id)
{
	int i;
	for (i = 0; i < studentCount; i++)
	{
		if (students[i].id == id)
			return &students[i];
	}
	return NULL;
}