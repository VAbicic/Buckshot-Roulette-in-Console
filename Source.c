#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<stdlib.h>
#include<time.h>
#include"Header.h"

//varijable
int metci[8];
int brojMetaka;
int trenutniMetak;
int dealerHealth = 4;
int playerHealth = 4;
int maxHealth;
int dealerItemi[8];
int playerItemi[8];
int dealerKnowsRound=0;
int doubleDamage;
int pItemCount;
int dItemCount;
int cuffs;
//logika igre
int main(void)
{
	srand(time(NULL));
	printf("Jedna demo runda zapoceta...\n");
	int gameOver = 0;
	//glavni game loop
	while (gameOver!=1)
	{
		newGame();
		int uvijet = 1;

		do {
			uvijet = izbornik();
			//ponavlja se igracev potez dok nije postignut uvijet za dealerov potez
			if (uvijet == -1&&dealerHealth>0&&!cuffs>0)
			{
				_getch();
				dealerPotez();
			}
		} while (uvijet && dealerHealth > 0 && playerHealth > 0);
		_getch();
		system("cls");
		//kraj runde
		if (dealerHealth == 0) {
			printf("IGRAC POBJEDUJE!\n");
		}
		else if (playerHealth == 0)
		{
			printf("Dealer pobjeduje...\n");
		}
		printf("Igra je zavrsena.\n");
		printf("Jos jednu rundu? (da/ne)\n");
		char potvrda[3] = { '\0' };
		scanf("%2s", potvrda);
		if (strcmp("da", potvrda)) {
			gameOver = 1;
		}
		else { system("cls"); }
	}
	
	//Animation();
}

int RNG(int min, int max) {
	int result= (rand() %(max - min + 1)) + min;
	return result;
}
int izbornik()
{
a:	printf("\n");
	showItems('p');
	showItems('d');
	//printf("\n");
	printf("\n\tHealth: %d",playerHealth);
	printf("\n\t  ==================");
	printf("Odaberi radnju:");
	printf("==================\n");
	printf("\t\t\t\t1) Pucaj \n");
	printf("\t\t\t\t 2) Itemi \n");
	printf("\t\t\t\t  3) Izlaz iz igre \n");
	printf("\t\t\t\t   4) Refresh RNG (debug) \n");
	printf("\t\t\t\t    5) Prikazi metke (debug)\n");
	printf("\t\t\t\t     6) Vidi dealerove iteme\n");
	//printf("\t\t\tOpcija 5: izlaz iz programa!\n");
	printf("\t       ==================\
=================================");
	printf(" Dealer HP: %d\n", dealerHealth);
	int uvijet = 0;
	//scanf("%d", &uvijet);
	if (!scanf("%d", &uvijet))
	{
		scanf("%*[^\n]"); //discard that line up to the newline
		system("cls");
		goto a;
	}
	switch (uvijet)
	{
	case 1: printf("Pucanje...\n");
		system("cls");
		uvijet=pucajIzbornik(uvijet);
		break;
	case 2: 
		if (pItemCount != 0) {
			printf("Odabir itema...\n");
			system("cls");
			itemSelect();
		}
		else {
			system("cls");
			printf("Nemas itema.");
		}
		break;
	case 3: system("cls");
		printf("Utipkajte \"da\" ako uistinu zelite izaci iz igre! \n");
		char potvrda[3] = { '\0' };
		scanf("%2s", potvrda);
		if (!strcmp("da", potvrda)) {
			uvijet = 0;
		}
		system("cls");
		break;
	case 4: system("cls");
		printf("Resetiranje...\n");
		newGame();
			break;
	case 5: printf("Prikaz metaka...\n ");
		system("cls");
		prikaziMetke();
			break;
	case 6:
		system("cls");
		showItems('d');
		break;
	default:
		system("cls");
		goto a;
		uvijet = 0;
	}
	return uvijet;
}
int pucajIzbornik(int uvijet) {
a:	printf("====================");
	printf("Pucaj:");
	printf("====================\n");
	printf("\t\t\t1) U dealera \n");
	printf("\t\t\t2) U sebe \n");
	printf("\t\t\t3) Odustani \n");
	//printf("\t\t\tOpcija 4: \n");
	//printf("\t\t\tOpcija 5: izlaz iz programa!\n");
	printf("======================================\
======================================\n");
	//scanf("%d", &uvijet);
	if (!scanf("%d", &uvijet))
	{
		scanf("%*[^\n]"); //discard that line up to the newline
		system("cls");
		goto a;
	}
	switch (uvijet)
	{
	case 1: system("cls");
		printf("Pucanje u dealera...\n");
		if (trenutniMetak + 1 != brojMetaka && dealerHealth!=0)uvijet = -1;
		pucaj(1);
		if (metci[trenutniMetak - 1] == 0) { doubleDamage = 0; }
		if (cuffs > 0) { 
			cuffs--; 
			if (cuffs == 1) { printf("Dealeru su ruke svezane pa igras jos jednom.\n"); }
			else if (cuffs == 0)printf("Lisice su skinute.\n");
		}
		return uvijet;
		break;
	case 2: system("cls");
		printf("Pucanje u sebe...\n");
		if (metci[trenutniMetak] != 0 ) {
			uvijet = -1;
		}
		pucaj(0);
		if (cuffs > 0) { cuffs--; if (cuffs == 1) { printf("Dealeru su ruke svezane pa igras jos jednom.\n"); }
		else if (cuffs == 0)printf("Lisice su skinute.\n");
		}
		return uvijet;
		break;
	case 3: system("cls");
		printf("Vracanje... \n");
		break;
		/*case 4: printf("Odabir 4.\n");
			//funkcija();
			break;
		case 5: printf("Kraj programa.\n");
			uvijet = 0;
			break;*/
	default:
		system("cls");
		goto a;
		/*uvijet = 0;
		return uvijet;*/
	}
	
}
void pucaj(int target) {
	int damage = 1;
	if (doubleDamage == 1)damage = 2;
	if (metci[trenutniMetak] == 1)
	{
		printf("BOOM!!!\n");
		doubleDamage = 0;
		if (target == 1) dealerHealth-=damage;
		else
		{
			playerHealth-=damage;
		}
	}
	else
	{
		printf("*Click* (prazno)\n");
	}
	iduciMetak();
	if (trenutniMetak == brojMetaka && dealerHealth != 0)
	{
		printf("Zadnji metak izbacen.\n");
		generateBullets();
	}
}
void reset() {
	trenutniMetak = 0;
	if (cuffs != 0) { cuffs = 0; printf("Lisice su skinute.\n"); }
}
void newGame() {
	for (int i = 0; i < 8; i++)
	{
		playerItemi[i] = 0;
		dealerItemi[i] = 0;
	}
	pItemCount = 0;
	dItemCount = 0;

	maxHealth = RNG(2, 6);
	dealerHealth = maxHealth;
	playerHealth = maxHealth;
	generateBullets();
}
void iduciMetak()
{
	trenutniMetak++;
}
