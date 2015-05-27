#include "projecte.h"

unsigned int HashAddress(unsigned int x)
{
	x = ((x >> 16) ^ x) * 0x45d9f3b;
	x = ((x >> 16) ^ x) * 0x45d9f3b;
	x = ((x >> 16) ^ x) * 0x45d9f3b;
	return x % M;
}

int WriteStudent(Student student, FILE *ft)
{
	int i, j, start;
	i = HashAddress((unsigned int)student.id);
	// Upamti izraèunatu adresu kao poèetnu
	start = i;
	do
	{ // Ponavljaj dok ne upišeš ili ustanoviš da je datoteka puna    
		// Èitaj iz pretinca sve upisane zapise
		fseek(ft, i*BLOK, SEEK_SET);
		fread(slot, sizeof(slot), 1, ft);
		for (j = 0; j < C; j++)
		{
			if (slot[j].id != 0)
			{
				// Ako zapis nije prazan
				if (DEBUG)
				{
					printf("Existing id =");
					printf("%d\n", slot[j].id);
				}
				if (slot[j].id == student.id)
				{
					printf("There already exists entry with id %d\n", student.id);
					return 1;
				}
			}
			else
			{
				// Upiši ulazni zapis na prazno mjesto
				slot[j] = student;
				fseek(ft, i*BLOK, SEEK_SET);
				if (DEBUG)
					printf("In slot #%d writing %d. entry\n", i, j);
				fwrite(slot, sizeof(slot), 1, ft);
				return 1;
			}
		}
		// U pretincu nema mjesta, prijeði ciklièki na sljedeæega
		i = (i + 1) % M;
		printf("No room in this slot, moving to #%d\n", i);
	} while (i != start); // Dok se ne ne vratiš na poèetni
	return 0;  // Niti u jednom zapisu nema mjesta
}

void WriteStudents(char *filename, Student *students, int studentCount)
{
	FILE *ft;
	int i = 0;
	if ((ft = fopen(filename, "wb+")) == NULL)
		errorexit("Could not open \"pristupnici.bin\" for writing.", 301);
	PrepareTable(ft);
	for (i = 0; i < studentCount; i++)
		if (WriteStudent(students[i], ft) == 0)
			break; // There was no room for the entry, break writing
	fclose(ft);
}

void PrepareTable(FILE *ft)
{
	int i;
	printf("Clearing table...");
	// empty row is identified by id = 0
	for (i = 0; i < C; i++) slot[i].id = 0;
	for (i = 0; i < M; i++)
	{
		fseek(ft, i*BLOK, SEEK_SET);
		fwrite(slot, sizeof(slot), 1, ft);
	}
	printf("Table cleared N=%d, C=%d, M=%d\n", N, C, M);
	printf("Slot size = %d\n", sizeof(slot));
}

void PrintStudents(Student *studentBegin, int studentCount)
{
	Student *ptemp = studentBegin;
	while (ptemp < studentBegin + studentCount)
	{
		printf("id:%d score:%d\n", ptemp->id, ptemp->score);
		ptemp++;
	}
}