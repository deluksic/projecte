#include "projecte.h"

// reads student entries from filename and saves 
// them into memory on outStudents location.
// Writes number of entries into outCount.
void ReadStudents(char* filename, Student* outStudents, int* outCount){
	FILE *fstudents;
	int i, count, nextid;
	char ch;

	// read pristupnici.txt, format: id#firstname#lastname
	if ((fstudents = fopen(filename, "r")) == NULL)
		errorexit("File \"pristupnici.txt\" not found.", 404);

	count = 0;
	nextid = 0;
	while (fscanf(fstudents, "%d", &nextid) == 1) {
		if ((outStudents = (Student*)malloc(sizeof(Student) * (count + 1))) == NULL)
			errorexit("Failed to allocate memory while reading.", 200);

		// if the next char is not #, errorexit!
		if (fscanf(fstudents, "%c", &ch) == 1 && ch != '#')
			errorexit("Error in reading student line.", 101);

		// write id
		outStudents[count].id = nextid;

		// read first name
		i = 0;
		while (fscanf(fstudents, "%c", &ch) == 1 && ch != '#'){
			outStudents[count].firstname[i++] = ch;
			if (i == 22)
				errorexit("Error in reading student line.", 102);
		}
		// terminate with 0
		outStudents[count].firstname[i] = 0;

		// read last name
		i = 0;
		while (fscanf(fstudents, "%c", &ch) == 1 && ch != '#' && ch != '\n'){
			outStudents[count].lastname[i++] = ch;
			if (i == 22)
				errorexit("Error in reading student line.", 103);
		}
		// terminate with 0
		outStudents[count].lastname[i] = 0;

		printf(
			"stud entry: %d, %s, %s\n",
			outStudents[count].id,
			outStudents[count].firstname,
			outStudents[count].lastname
			);
		count++;
	}
	fclose(fstudents);
	*outCount = count;
}

// reads student entries from filename and saves 
// them into memory on outStudents location.
// Writes number of entries into outCount.
void ReadExams(char* filename, Exam* outExams, int* outCount){
	FILE *fexams;
	int i, count;
	char ch;

	// read ispiti.txt, format: filename#mintreshold
	if ((fexams = fopen(filename, "r")) == NULL)
		errorexit("File \"ispiti.txt\" not found.", 404);

	count = 0;
	while (1) {
		if ((outExams = (Exam*)malloc(sizeof(Exam) * (count + 1))) == NULL)
			errorexit("Failed to allocate memory while reading.", 200);

		// read filename
		i = 0;
		while (fscanf(fexams, "%c", &ch) == 1 && ch != '#'){
			outExams[count].filename[i++] = ch;
			if (i == 22)
				errorexit("Error in reading exam line.", 104);
		}
		// terminate with 0
		outExams[count].filename[i] = 0;

		// read score threshold (the previous # is taken already 
		// and we are ready to read threshold value)
		if (fscanf(fexams, "%d", &outExams[count].scoreThreshold) != 1)
			errorexit("Error in reading exam line.", 105);

		printf(
			"exam entry: %s, %d\n",
			outExams[count].filename,
			outExams[count].scoreThreshold
			);
		count++;

		if (fscanf(fexams, "%c", &ch) != 1 || ch == EOF)
			break;
	}
	fclose(fexams);
	*outCount = count;
}