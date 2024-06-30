#include"Header.h"
static int brojSaveova = 0;
void kreirajDatoteku() {
	FILE* pF = fopen("rezultati", "ab");
	if (pF == NULL) {
		perror("Neuspjelo kreiranje datoteke");
		exit(EXIT_FAILURE);
	}
	fwrite(&brojSaveova, sizeof(int), 1, pF);
	fclose(pF);
}
void saveResults() {
	FILE* pF = fopen("rezultati", "rb+");
	if (pF == NULL) {
		perror("Neuspjelo pristupanje datoteci");
		exit(EXIT_FAILURE);
	}
	fread(&brojSaveova, sizeof(int), 1, pF);
	//printf("broj saveova: %d\n", brojSaveova);
	PLAYER temp = { 0 };
	temp.id = brojSaveova;
	printf("Unesite ime igraca:\n");
	scanf("%29[^\n]", temp.ime);
	temp.score = score;
	if (doubleOrNothing == 1)
	{
		temp.specialMode = 1;
	}
	else {
		temp.specialMode = 0;
	}
	fseek(pF, sizeof(PLAYER) * brojSaveova, SEEK_CUR);
	fwrite(&temp, sizeof(PLAYER), 1, pF);
	rewind(pF);
	brojSaveova++;
	fwrite(&brojSaveova, sizeof(int), 1, pF);
	fclose(pF);
}
void leaderboardIzbornik(const PLAYER* leaderboard) {
a:	printf("====================");
	printf("Leaderboard:");
	printf("====================\n");
	if (leaderboard != NULL) {
		free(leaderboard);
		leaderboard = NULL;
	}
	leaderboard = (PLAYER*)readResults();
	if (leaderboard == NULL) {
		exit(EXIT_FAILURE);
	}
	ispisiLeaderboard(leaderboard);
	printf("======================================\
=========================================\n");
	printf("\n  1) Uklanjanje rezultata\n");
	printf("  2) Nazad\n");
	int odabir;
	if (!scanf("%d", &odabir))
	{
		scanf("%*[^\n]"); //discard that line up to the newline
		system("cls");
		goto a;
	}
	switch (odabir)
	{
	case 1:
		system("cls");
		printf("====================");
		printf("Leaderboard:");
		printf("====================\n");
		ispisiLeaderboard(leaderboard);
		printf("======================================\
=========================================\n");
		PLAYER* pronadeniSave = NULL;
		pronadeniSave = (PLAYER*)pronadiSave(leaderboard);
		if (pronadeniSave != NULL) {
			printf("Zelite li obrisati taj rezultat s liste?\n");
			printf("(da/ne)\n");
			char potvrda[3] = { '\0' };
			scanf("%2s", potvrda);
			if (!strcmp("da", potvrda)) {
				brisanjePlayera(&pronadeniSave, leaderboard);
				system("cls");
				goto a;
			}
			else {
				system("cls");
				goto a;
			}
		}
		else {
			_getch();
			system("cls");
			goto a;
		}
		break;
	case 2:
		system("cls");
		printf("Vracanje...\n");
		oslobadanjeMem(leaderboard);
		break;
	default:
		system("cls");
		goto a;
	}
}
void* readResults() {
	FILE* pF = fopen("rezultati", "rb");
	if (pF == NULL) {
		perror("Neuspjelo ucitavanje rezultata iz datoteke");
		return NULL;
		//exit(EXIT_FAILURE);
	}
	fread(&brojSaveova, sizeof(int), 1, pF);
	//printf("Broj saveova: %d\n", brojSaveova);
	PLAYER* leaderboard = (PLAYER*)calloc(brojSaveova, sizeof(PLAYER));
	if (leaderboard == NULL) {
		perror("Neuspjelo zauzimanje memorije za leaderboard");
		return NULL;
		//exit(EXIT_FAILURE);
	}
	fread(leaderboard, sizeof(PLAYER), brojSaveova, pF);
	fclose(pF);
	return leaderboard;
}
void ispisiLeaderboard(const PLAYER* leaderboard) {
	if (leaderboard == NULL) {
		printf("Leaderboard je prazan\n");
		return;
	}
	//sortiranje prije ispisa
	int* sortBuffer;
	sortBuffer = (int*)malloc(brojSaveova * sizeof(int));
	if (sortBuffer != NULL) {
		for (int i = 0; i < brojSaveova; i++)
		{
			sortBuffer[i] = (leaderboard + i)->score;
		}
	}
	int n = brojSaveova;
	quickSort(sortBuffer, 0, n - 1);
	//ispis
	int noRepeat[200] = { 0 };
	for (int i = 0; i < brojSaveova; i++) {
		//i-petlja ide kroz svaki sortirani score
		for (int j = 0; j < brojSaveova; j++)
		{
			//j-petlja usporeduje pojedini score sa svim unosima na leaderboardu dok ne nade prvi koji ima isti score
			if ((leaderboard+j)->score==sortBuffer[i]) {
				int repeat = 0;
				//provjera da se ne ponavlja ispis igraca koji ima identican score kao neki drugi igrac
				if (i > 0) {
						if (noRepeat[j]==1) {
							repeat = 1;
						}
				}
				if (repeat == 0) {
					//ako ovo nije ponovljen igrac, ispis
					if ((leaderboard + j)->specialMode == 1) {
						printf("%d\t Player ID: %d\tIme: %s\tScore: %d\tDouble or nothing: yes\n",i+1, (leaderboard + j)->id, (leaderboard + j)->ime, (leaderboard + j)->score);
					}
					else {
						printf("%d\t Player ID: %d\tIme: %s\tScore: %d\tDouble or nothing: no\n",i+1, (leaderboard + j)->id, (leaderboard + j)->ime, (leaderboard + j)->score);
					}
					noRepeat[j] = 1;//trenutni igrac je oznacen da se ne ponavlja dalje u ispisu
					break;
				}
			}
		}
	}
	//stari ispis
	/*for (int i = 0; i < brojSaveova; i++)
	{
		if ((leaderboard + i)->specialMode == 1) {
			printf("Player ID: %d\tIme: %s\tScore: %d\tDouble or nothing: yes\n", (leaderboard + i)->id, (leaderboard + i)->ime, (leaderboard + i)->score);
		}
		else {
			printf("Player ID: %d\tIme: %s\tScore: %d\tDouble or nothing: no\n", (leaderboard + i)->id, (leaderboard + i)->ime, (leaderboard + i)->score);
		}
	}*/
	free(sortBuffer);
}
void* pronadiSave(PLAYER* const leaderboard) {
	if (leaderboard == NULL) {
		printf("Leaderboard je prazan\n");
		return NULL;
	}
	int i;
	int notok = 0;
	int trazenID;
	printf("Unesite ID trazenog igraca:\n");
	scanf("%d", &trazenID);
	for (i = 0; i < brojSaveova; i++)
	{
		if ((trazenID==(leaderboard + i)->id)) {
			notok = 1;
			printf("Igrac je pronaden!\n");
				if ((leaderboard + i)->specialMode == 1) {
					printf("Player ID: %d\tIme: %s\tScore: %d\tDouble or nothing: yes\n", (leaderboard + i)->id, (leaderboard + i)->ime, (leaderboard + i)->score);
				}
				else {
					printf("Player ID: %d\tIme: %s\tScore: %d\tDouble or nothing: no\n", (leaderboard + i)->id, (leaderboard + i)->ime, (leaderboard + i)->score);
				}
			return (leaderboard + i);
		}
	}
	if (notok == 0)
	{
		printf("Save nije pronaden!\n");
	}
	return NULL;
}
void brisanjePlayera(PLAYER** const trazeniPLAYER, const PLAYER* const leaderboard) {
	FILE* pF = fopen("rezultati", "wb");
	if (pF == NULL) {
		perror("Brisanje PLAYERa iz datoteke PLAYERi.bin");
		exit(EXIT_FAILURE);
	}
	fseek(pF, sizeof(int), SEEK_SET);
	int i;
	int noviBrojacStudenata = 0;
	for (i = 0; i < brojSaveova; i++)
	{
		if (*trazeniPLAYER != (leaderboard + i)) {
			fwrite((leaderboard + i), sizeof(PLAYER), 1, pF);
			noviBrojacStudenata++;
		}
	}
	rewind(pF);
	fwrite(&noviBrojacStudenata, sizeof(int), 1, pF);
	fclose(pF);
	printf("PLAYER je uspjesno obrisan!\n");
	*trazeniPLAYER = NULL;
}

int oslobadanjeMem(PLAYER* leaderboard) {
	free(leaderboard);
	return 0;
}
//sortiranje
void swap(int* p1, int* p2)
{
	int temp;
	temp = *p1;
	*p1 = *p2;
	*p2 = temp;
}

int partition(int arr[], int low, int high)
{
	// choose the pivot
	int pivot = arr[high];

	// Index of smaller element and Indicate
	// the right position of pivot found so far
	int i = (low - 1);

	for (int j = low; j <= high - 1; j++) {
		// If current element is smaller than the pivot
		if (arr[j] >= pivot) {
			// Increment index of smaller element
			i++;
			swap(&arr[i], &arr[j]);
		}
	}
	swap(&arr[i + 1], &arr[high]);
	return (i + 1);
}

// The Quicksort function Implement

void quickSort(int arr[], int low, int high)
{
	// when low is less than high
	if (low < high) {
		// pi is the partition return index of pivot

		int pi = partition(arr, low, high);

		// Recursion Call
		// smaller element than pivot goes left and
		// higher element goes right
		quickSort(arr, low, pi - 1);
		quickSort(arr, pi + 1, high);
	}
}