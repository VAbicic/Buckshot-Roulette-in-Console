#include"Header.h"

void generateBullets() {
	int live = 0; 
	int blank=0;
	//resetiraj metke na pocetku funkcije
	for (int i = 0; i < 8; i++)
	{
		metci[i] = 0;
	}
	reset();
	_getch();
	system("cls");
	printf("Pripremanje svjezih metaka...\n");
	//odabir broja metaka u puski
	brojMetaka = RNG(2, 8);
	//postavljanje svakog metka
	while ((((float)live/(float)brojMetaka)<0.3f)||blank<1||((live==2)&&brojMetaka==3)) { //barem 30% metaka mora biti live i mora biti barem jedan blank
		live = 0;
		blank = 0;
		for (int i = 0; i < brojMetaka; i++)
		{
			metci[i] = RNG(0, 1);
			if (metci[i] == 1) { live++; }
			else if (metci[i] == 0) { blank++; }
		}
	}
	//novi itemi svaki reload
	generateItems();
	//printf("\n");
	prikaziMetke();
	_getch();
	printf("Metci ulaze u sacmaricu skrivenim redoslijedom: \n\t");
	for (int i = 0; i < brojMetaka; i++)
	{
		printf("X ");
		delay(0.21);
	}
	printf("\n\n");
	//shuffle bullets
	shuffle(metci, brojMetaka);
	shuffle(metci, brojMetaka);
	shuffle(metci, brojMetaka);
	//provjera ispis
	printf("Ima %d metaka: ", brojMetaka);
	for (int i = 0; i < brojMetaka; i++)
	{
		printf("%d ", metci[i]);
	}
	printf("\n");
	_getch();
	system("cls");
}
void generateItems() {
	//dodavanje novih itema dealeru i igracu
	int amount = RNG(2, 4);
	int amount2 = amount;
	printf("%d itema dodano...\n",amount);
	int i = 0;
	while (pItemCount+amount > 8) {
		if (amount == 0)break;
		amount--;
	}
	pItemCount += amount;
	if (pItemCount != 0) {
		while (playerItemi[i] != 0) {
			i++;
		}
	}
	for (i; i < pItemCount; i++)
	{
		playerItemi[i] = RNG(1, 5);
	}
	i = 0;
	while (dItemCount + amount2 > 8) {
		if (amount2 == 0)break;
		amount2--;
	}
	dItemCount += amount2;
	if (dItemCount != 0)
	{
		while (dealerItemi[i] != 0) {
			i++;
		}
	}
	for (i; i < dItemCount; i++)
	{
		dealerItemi[i] = RNG(1, 5);
	}
	i = 0;
}
void prikaziMetke() {
	//prikazi iteme
	//showItems('p');
	//showItems('d');
	printf("\n");
	printf("Metci:  ");
	for (int i = trenutniMetak; i < brojMetaka; i++)
	{
		printf("%d ", metci[i]);
	}
	printf("\n");
}


void shuffle(int* array, size_t n)
{
	if (n > 1)
	{
		size_t i;
		for (i = 0; i < n - 1; i++)
		{
			size_t j = i + rand() / (RAND_MAX / (n - i) + 1);
			int t = array[j];
			array[j] = array[i];
			array[i] = t;
		}
	}
}

void delay(float number_of_seconds)
{
	// Converting time into milli_seconds
	float milli_seconds = 1000 * number_of_seconds;
	// Storing start time
	clock_t start_time = clock();
	// looping till required time is not achieved
	while (clock() < start_time + milli_seconds);
}
void Animation() {
	//this is a test animation preset
	char filename_format[] = "testAnim/anim%d.txt";
	char filename[sizeof(filename_format) + 3]; //setting the directory for animation frames
	while (1)
	{
		for (int i = 0; i < 10; i++) {
			snprintf(filename, sizeof(filename), filename_format, i + 1);
			FILE* fr = fopen(filename, "r");

			if (!fr)
				break;

			int ch;

			while ((ch = fgetc(fr)) != EOF)
				putchar(ch);

			fclose(fr);

			delay(0.5); //time per frame
			system("cls");
		}
	}
}