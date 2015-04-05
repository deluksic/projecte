#include "projecte.h"

unsigned int HashAddress(unsigned int x)
{
	x = ((x >> 16) ^ x) * 0x45d9f3b;
	x = ((x >> 16) ^ x) * 0x45d9f3b;
	x = ((x >> 16) ^ x) * 0x45d9f3b;
	return x % M;
}

//int WriteStudent(Student student, FILE *ft)
//{
//	int i, j, start;
//	i = HashAddress(student.id);
//	// Upamti izra�unatu adresu kao po�etnu
//	start = i;
//	do
//	{ // Ponavljaj dok ne upi�e� ili ustanovi� da je datoteka puna    
//		// �itaj iz pretinca sve upisane zapise
//		fseek(ft, i*BLOK, SEEK_SET);
//		fread(pretinac, sizeof(pretinac), 1, ft);
//		for (j = 0; j < C; j++)
//		{
//			if (pretinac[j].JMBG[0] != '\0')
//			{
//				// Ako zapis nije prazan
//				printf("Vec upisani JMBG =");
//				printf("%s\n", pretinac[j].JMBG);
//				if (strncmp(pretinac[j].JMBG, ulaz.JMBG, VELJMBG) == 0)
//				{
//					// Ako je upisani JMBG identi�an ulaznom
//					printf("Vec postoji zapis s JMBG %s\n", ulaz.JMBG);
//					return 1;
//				}
//			}
//			else
//			{
//				// Upi�i ulazni zapis na prazno mjesto
//				pretinac[j] = ulaz;
//				fseek(ft, i*BLOK, SEEK_SET);
//				printf("U pretinac %d upisujem %d. zapis\n", i, j);
//				fwrite(pretinac, sizeof(pretinac), 1, ft);
//				return 1;
//			}
//		}
//		// U pretincu nema mjesta, prije�i cikli�ki na sljede�ega
//		i = (i + 1) % M;
//		printf("Nema mjesta, slijedi pretinac = %d\n", i);
//	} while (i != poc); // Dok se ne ne vrati� na po�etni
//	return 0;  // Niti u jednom zapisu nema mjesta
//}