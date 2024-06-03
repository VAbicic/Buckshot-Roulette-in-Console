#include"Header.h"

void dealerPotez() {
	//int items = RNG(1, 3);
	system("cls");
	printf("Dealerov potez...\n");
	_getch();
	if (trenutniMetak + 1 == brojMetaka)dealerKnowsRound = 1;
	//items
	if (dItemCount > 0) {

		inventory('d');
	}
	//dealerUseItem();
	system("cls");
	showItems('p');
	showItems('d');
	printf("\n\n");
	puts("Dealer uzima sacmaricu.\n");
	_getch();
	dealerShoot();
	system("cls");
	if (playerHealth > 0)printf("Tvoj red.\n\n");
}
void dealerShoot()
{
	int dstartHealth = dealerHealth;
	int target;
a:
	if (dealerKnowsRound == 1) {
		if (metci[trenutniMetak] == 1)
		{
			target = 0;
		}
		else { target = 1; }
	}
	else if (doubleDamage == 1) {
		target = 0;
	}
	else {
		target = RNG(0, 1);
	}
	if (target == 0)
	{
		puts("Dealer je uperio sacmaricu u tebe.\n");
	}
	else puts("Dealer je uperio sacmaricu sebi u glavu.\n");
	_getch();

	pucaj(target);
	_getch();
	if (dealerKnowsRound = 1)dealerKnowsRound = 0;
	//bonus potez ako je pogodio sebe sa praznim
	if (target == 1 && dstartHealth == dealerHealth && trenutniMetak != 0) {
		dstartHealth = dealerHealth;
		//dealerPotez();
		printf("\n");
		//goto a;
		dealerPotez();
	}
	else if (target = 1)doubleDamage = 0;

	if (cuffs != 0) {
		cuffs--;
		if (cuffs == 1 && playerHealth > 0 && dealerHealth > 0)
		{
			system("cls");
			puts("Dealer igra jos jednom...\n");
			_getch();
			//goto a;
			dealerPotez();
		}
	}
}