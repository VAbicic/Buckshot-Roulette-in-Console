#include"Header.h"

int inventory(char user) {
	char move;
	int indeks = 0;
	int odabir;
	int itemCode=0;
	int dealerUsedItem = 0;
	int amount = dItemCount;
	int unavailable;
b:	if (user == 'd') {
	for (int i = 0; i < amount; i++)
	{
		//int slot = RNG(0, pItemCount - 1);
		if (dealerItemi[i] != 0 && trenutniMetak + 1 != brojMetaka)
		{
			dealerUsedItem = functionSelect(dealerItemi[i], 'd');
			if (dealerUsedItem == 1) {
				for (int j = i; j < dItemCount; j++)
				{
					dealerItemi[j] = dealerItemi[j + 1];
				}
				dItemCount--;
				i--;
				dealerUsedItem = 0;
			}
		}
	}
}
else if (user == 'p')
{
	do {
		unavailable = 0;
		system("cls");
		printf("Kreci se sa 1 i 3, ako se zelis vratit stisni 0.\n\n");
		if (pItemCount == 0) {
			printf("Nemas itema.\n");
			break;
		}
		printf("Imas %d itema.\n ", pItemCount);

		printf("\t\t  Slot %d: \n", indeks + 1);


		if (playerItemi[indeks] == 1) {
			printf("\t<--\t Povecalo \t-->\n");
			printf("\n Zaviri unutar sacmarice i saznaj koja je trenutna cahura.\n");
			itemCode = 1;
		}
		else if (playerItemi[indeks] == 2)
		{
			printf("\t<--\t  Pivo    \t-->\n");
			printf("\n Otpij malo i izbaci trenutnu cahuru iz sacmarice.\n");
			itemCode = 2;
		}
		else if (playerItemi[indeks] == 3)
		{
			printf("\t<--\t Cigarete \t-->\n");
			printf("\n Zapali cigaru i vrati si jedan zivot.\n");
			if (playerHealth != maxHealth) {
				itemCode = 3;
			}
			else {
				printf("\n(Vec imas sve zivote...)\n");
				unavailable = 1;
			}
		}
		else if (playerItemi[indeks] == 4)
		{
			printf("\t<--\t  Pila  \t-->\n");
			printf("\n Otpiljeni vrh daje dvostruku stetu za iduci metak.\n");
			if (doubleDamage == 0) {
				itemCode = 4;
			}
			else {
				printf("\n(Sacmarici je vec otpiljen vrh.)\n");
				unavailable = 1;
			}
		}
		else if (playerItemi[indeks] == 5)
		{
			printf("\t<--\t Lisice \t-->\n");
			printf("\n Natjeraj dealera da preskoci iduci potez.\n");
			itemCode = 5;
		}
		move = _getch();
		if (move == '3') {
			indeks++;
			if (indeks == pItemCount) {
				indeks = 0;
			}
		}
		else if (move == '1') {
			indeks--;
			if (indeks == -1) {
				indeks = pItemCount - 1;
			}
		}
		else if (move == '0')
		{
			system("cls");
			printf("Povratak...\n");
			return 0;
		}
	} while (move != '\r');
	if (unavailable == 1)goto b;
	//system("cls");
	printf("\n  1) Iskoristi\n");
	printf("  2) Odustani\n");
	if (!scanf("%d", &odabir))
	{
		scanf("%*[^\n]"); //discard that line up to the newline
		system("cls");
		goto b;
	}
	switch (odabir)
	{
	case 1:
		system("cls");
		//printf("Iskoristeno.\n");
		for (int i = indeks; i < pItemCount; i++)
		{
			playerItemi[i] = playerItemi[i + 1];
		}
		pItemCount--;
		return itemCode;
		break;
	case 2:
		system("cls");
		goto b;
		break;
	default:
		system("cls");
		goto b;
	}
}
return 0;
}
void showItems(char user) {
	if (user == 'p') {
		printf("Player items: ");
		for (int i = 0; i < pItemCount; i++)
		{
			if (playerItemi[i] == 1) {
				printf("|Povecalo| ");
			}
			else if (playerItemi[i] == 2)
			{
				printf("|Pivo| ");
			}
			else if (playerItemi[i] == 3)
			{
				printf("|Cigarete| ");
			}
			else if (playerItemi[i] == 4)
			{
				printf("|Pila| ");
			}
			else if (playerItemi[i] == 5)
			{
				printf("|Lisice| ");
			}
		}
		printf("\n");
	}
	else if (user == 'd') {
		printf("Dealer items: ");
		for (int i = 0; i < dItemCount; i++)
		{
			if (dealerItemi[i] == 1) {
				printf("|Povecalo| ");
			}
			else if (dealerItemi[i] == 2)
			{
				printf("|Pivo| ");
			}
			else if (dealerItemi[i] == 3)
			{
				printf("|Cigarete| ");
			}
			else if (dealerItemi[i] == 4)
			{
				printf("|Pila| ");
			}
			else if (dealerItemi[i] == 5)
			{
				printf("|Lisice| ");
			}
		}
		printf("\n");
	}
}
void itemSelect() {
	//pokrece se inventory od igraca
	functionSelect(inventory('p'), 'p');
}

int functionSelect(int itemCode, char user) {
	int dealerUsedItem = 0;
	//printf("\t\t   %d: \n", indeks + 1);
	if (user == 'd') {
		// while ((getchar()) != '\n');

	}
	if (itemCode == 0) {

	}
	else if (itemCode == 1) {
		system("cls");
		if (user == 'p') {
			printf("Povecalo iskoristeno.\n");
			povecalo('p');
		}
		else if (user == 'd' && dealerKnowsRound != 1) {
			showItems('p');
			showItems('d');
			printf("\n \n");
			printf("Dealer uzima povecalo i gleda unutar sacmarice.\n");

			_getch();
			povecalo('d');
			_getch();
			dealerUsedItem = 1;
			return dealerUsedItem;
		}
	}
	else if (itemCode == 2)
	{
		system("cls");
		if (user == 'p')
		{
			printf("Pivo iskoristeno.\n");
			pivo();
			_getch();
		}
		else if (user == 'd' && dealerKnowsRound != 1) {
			system("cls");
			showItems('p');
			showItems('d');
			printf("\n \n");
			printf("Dealer uzima pivo i eksira ga.\n");
			dealerUsedItem = 1;
			pivo();
			_getch();
			//_getch();
		}
		return dealerUsedItem;
	}
	else if (itemCode == 3)
	{
		if (user == 'p') {
			system("cls");
			if (playerHealth != maxHealth)
			{
				printf("Cigarete iskoristene.\n");
				cigarete('p');
			}
			else
			{
				printf("Vec imas pune zivote.\n");
			}
		}
		else if (user == 'd' && dealerHealth != maxHealth)
		{
			system("cls");
			showItems('p');
			showItems('d');
			printf("\n \n");
			printf("Dealer pali cigaru...\n");
			_getch();
			cigarete('d');
			_getch();
			dealerUsedItem = 1;
			return dealerUsedItem;
		}
	}
	else if (itemCode == 4)
	{
		if (user == 'p') {
			if (doubleDamage == 0)
			{
				system("cls");
				printf("Pila iskoristena.\n");
				pilica();
			}
			else { printf("Sacmarici je vec otpiljen vrh."); }
		}
		else if (user == 'd') {
			if (dealerKnowsRound == 1 && doubleDamage != 1)
			{
				if (metci[trenutniMetak] == 0) {
					system("cls");
					showItems('p');
					showItems('d');
					printf("\n \n");
					printf("Dealer uzima sacmaricu i pocinje piliti.\n");
					_getch();
					pilica();
					dealerUsedItem = 1;
					//return dealerUsedItem;
				}
			}
			else if (doubleDamage != 1) {
				system("cls");
				showItems('p');
				showItems('d');
				printf("\n \n");
				printf("Dealer uzima sacmaricu i pocinje piliti.\n");
				_getch();
				pilica();
				_getch();
				dealerUsedItem = 1;
				//return dealerUsedItem;
			}
			return dealerUsedItem;
		}
	}
	else if (itemCode == 5)
	{
		if (user == 'p') {
			system("cls");
			if (cuffs == 0)
			{
				printf("Lisice iskoristene.\n");
				printf("Zavezao si dealera i ne moze igrati iduci potez.\n");
				lisice();
			}
			else if (cuffs == 2) {
				printf("Dealer je vec zavezan.\n");
			}
			else printf("Ne mozes dvaput zaredom koristiti lisice...\n");
		}
		else if ((user == 'd' && cuffs == 0 && dealerKnowsRound == 1 && metci[trenutniMetak] != 0) || user == 'd' && cuffs == 0) {
			system("cls");
			showItems('p');
			showItems('d');
			printf("\n \n");
			printf("Dealer uzima lisice i veze ti ruke.\n");
			printf("Preskaces svoj iduci potez...");
			_getch();
			lisice();
			dealerUsedItem = 1;
			return dealerUsedItem;
		}
	}
	return 0;
}
void povecalo(char user) {
	if (user == 'd') {
		dealerKnowsRound = 1;
		puts("Vidio je trenutnu cahuru.\n");
	}
	else if (user == 'p')
	{
		if (metci[trenutniMetak] == 0)printf("Trenutna cahura je prazna.\n");
		else printf("Trenutna cahura je napunjena.");
		printf("\n");
	}
}
void pivo() {
	printf("Sacmarica je nategnuta i jedna cahura je izbacena.\n");
	_getch();
	if (metci[trenutniMetak] == 0)printf("Izbacena cahura je bila prazna.\n");
	else printf("Izbacena cahura je bila napunjena.\n");
	iduciMetak();
	if (trenutniMetak == brojMetaka && dealerHealth != 0)
	{
		printf("Zadnji metak izbacen.\n");
		generateBullets();
	}
}
void cigarete(char user) {
	if (user == 'd')
	{
		if (dealerHealth < maxHealth) {
			dealerHealth++;
			printf("Dealer je dobio nazad 1 zivot.\n");
		}
	}
	else if (user == 'p') {
		if (playerHealth < maxHealth) {
			playerHealth++;
			printf("Igrac je dobio nazad 1 zivot.\n");
		}
	}
}
void pilica() {
	printf("Sacmarici je otpiljen vrh...\n");
	printf("Iduci metak radi dvostruku stetu.\n");
	doubleDamage = 1;
}
void lisice() {
	cuffs = 2;
}
