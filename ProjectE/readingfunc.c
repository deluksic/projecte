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
			"read entry: %d, %s, %s\n",
			outStudents[count].id,
			outStudents[count].firstname,
			outStudents[count].lastname
			);
		count++;
	}
	fclose(fstudents);
	*outCount = count;
}