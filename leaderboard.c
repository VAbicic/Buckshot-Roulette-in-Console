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
	printf("Broj saveova: %d\n", brojSaveova);
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
	int i;
	for (i = 0; i < brojSaveova; i++)
	{
		if ((leaderboard + i)->specialMode == 1) {
			printf("Player ID: %d\tIme: %s\tScore: %d\tDouble or nothing: yes\n", (leaderboard + i)->id, (leaderboard + i)->ime, (leaderboard + i)->score);
		}
		else {
			printf("Player ID: %d\tIme: %s\tScore: %d\tDouble or nothing: no\n", (leaderboard + i)->id, (leaderboard + i)->ime, (leaderboard + i)->score);
		}
	}
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