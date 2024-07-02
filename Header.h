#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define iduciMetak() (trenutniMetak++)
#include <stdio.h>
#include<stdlib.h>
#include<time.h>
#include <conio.h>
//varijable
extern int metci[];
extern int brojMetaka;
extern int trenutniMetak;
extern int dealerHealth;
extern int playerHealth;
extern int dealerItemi[];
extern int playerItemi[];
extern int pItemCount;
extern int dItemCount;
extern int dealerKnowsRound;
extern int maxHealth;
extern int doubleDamage;
extern int cuffs;
extern int score;
extern int scorePenalty;
extern int doubleOrNothing;
typedef struct player {
	int id;
	char ime[40];
	int score;
	int specialMode;
}PLAYER;
//funkcije deklaracija
void delay(float);
void Animation();
int pucajIzbornik(int uvijet);
void itemSelect();
void generateBullets();
void generateItems();
int RNG(int min, int max);
void pucaj(int target);
//void iduciMetak();
void reset();
void prikaziMetke();
void dealerPotez();
void dealerUseItem(int target);
void dealerShoot();
void shuffle(int* array, size_t n);
void povecalo(char user);
void pivo();
void cigarete(char user);
void pilica();
void lisice();
int inventory(char user);
int functionSelect(int itemCode, char user);
void showItems(char user);
void newGame();
//leaderboard
void kreirajDatoteku();
void saveResults(const PLAYER* leaderboard);
void* readResults();
void ispisiLeaderboard(const PLAYER* const);
void* pronadiSave(PLAYER* const);
int oslobadanjeMem(PLAYER*);
void brisanjePlayera(PLAYER** const trazeniPLAYER, const PLAYER* const leaderboard);
void leaderboardIzbornik(const PLAYER* leaderboard);
//quicksort
void swap(int* p1, int* p2);
int partition(int arr[], int low, int high);
void quickSort(int arr[], int low, int high);