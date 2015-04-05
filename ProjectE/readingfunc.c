#include "projecte.h"

// reads student entries from filename and saves 
// them into memory on outStudents location.
// Writes number of entries into outCount.
Student* ReadStudents(char* filename, int* outCount){
	Student* students = (Student*)malloc(sizeof(Student));
	FILE *fstudents;
	int i, count, nextid;
	char ch;

	// read pristupnici.txt, format: id#firstname#lastname
	if ((fstudents = fopen(filename, "r")) == NULL)
		errorexit("File \"pristupnici.txt\" not found.", 404);

	count = 0;
	nextid = 0;
	while (fscanf(fstudents, "%d", &nextid) == 1) {
		if ((students = (Student*)realloc(students, sizeof(Student) * (count + 1))) == NULL)
			errorexit("Failed to allocate memory while reading.", 200);

		// if the next char is not #, errorexit!
		if (fscanf(fstudents, "%c", &ch) == 1 && ch != '#')
			errorexit("Error in reading student line.", 101);

		// write id
		students[count].id = nextid;

		// read first name
		i = 0;
		while (fscanf(fstudents, "%c", &ch) == 1 && ch != '#'){
			students[count].firstname[i++] = ch;
			if (i == 22)
				errorexit("Error in reading student line.", 102);
		}
		// terminate with 0
		students[count].firstname[i] = 0;

		// read last name
		i = 0;
		while (fscanf(fstudents, "%c", &ch) == 1 && ch != '#' && ch != '\n'){
			students[count].lastname[i++] = ch;
			if (i == 22)
				errorexit("Error in reading student line.", 103);
		}
		// terminate with 0
		students[count].lastname[i] = 0;

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

// reads student entries from filename and saves 
// them into memory on outStudents location.
// Writes number of entries into outCount.
Exam* ReadExams(char* filename, int* outCount){
	Exam* exams = (Exam*)malloc(sizeof(Exam));
	FILE *fexams;
	int i, count;
	char ch;

	// read ispiti.txt, format: filename#mintreshold
	if ((fexams = fopen(filename, "r")) == NULL)
		errorexit("File \"ispiti.txt\" not found.", 404);

	count = 0;
	while (1) {
		if ((exams = (Exam*)realloc(exams, sizeof(Exam) * (count + 1))) == NULL)
			errorexit("Failed to allocate memory while reading.", 200);

		// read filename
		i = 0;
		while (fscanf(fexams, "%c", &ch) == 1 && ch != '#'){
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

		printf(
			"exam entry: %s, %d\n",
			exams[count].filename,
			exams[count].scoreThreshold
			);
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
void ReadExamFile(char* filename, Student* students, int studentCount){
	FILE *fexam;
	int count, id, score;

	printf("Reading file %s\n", filename);

	// read ispiti.txt, format: filename#mintreshold
	if ((fexam = fopen(filename, "r")) == NULL)
		errorexit("File \"predmet.txt\" not found.", 404);

	count = 0;
	while (fscanf(fexam, "%d#%d", &id, &score) == 2) {
		printf(
			"exam result: id:%d, score:%d\n",
			id, score
			);
		count++;
	}
	fclose(fexam);
}