#define _CRT_SECURE_NO_WARNINGS
#include "MiniGame.h"
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include<time.h>
#include <windows.h>

int flag=1;//맨 처음만 아스키 아트 출력

void screen(int cur) {
	if(cur==1) {
		FILE* rock = fopen("rock.txt", "r");
		char rockprint[100];
		while (fgets(rockprint, sizeof(rockprint), rock)) {
			printf("%s", rockprint);
		}
		fclose(rock);
	}
	else if(cur==2) {
		FILE* paper = fopen("paper.txt", "r");
		char paperprint[100];
		while (fgets(paperprint, sizeof(paperprint), paper)) {
			printf("%s", paperprint);
		}
		fclose(paper);
	}
	else {
		FILE* scissor = fopen("scissor.txt", "r");
		char scissorprint[100];
		while (fgets(scissorprint, sizeof(scissorprint), scissor)) {
			printf("%s", scissorprint);
		}
		fclose(scissor);
	}

}

int RockPaperScissor() {

	srand(time(NULL));
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);

	int cur = 1, random = 0;
	char arrow;
	random = rand() % 3 + 1;

	// ⭐⭐⭐ 미니게임 시작 ASCII 아트⭐⭐⭐
	if(flag){
    system("cls");
    printAscii("asset/rockpaperscissor.txt");    // 넣고 싶은 아트 파일명
    Sleep(1500);
    system("cls");
	}
    // ⭐⭐⭐ 끝 ⭐⭐⭐
	flag=0;

	system("cls");
	screen(cur);

	while (1) {

		if (_kbhit()) {
			arrow = _getch();
			if (arrow == 13) break;
			if (arrow == -32) {
				arrow = _getch();

				switch (arrow) {

				case 75:
					if (cur == 1) continue;
					else {
						cur--; system("cls");
						screen(cur);
					}
					break;

				case 77:
					if (cur == 3)continue;
					else {
						cur++; system("cls");
						screen(cur);
					}
					break;
				}
			}
		}
	}

	system("cls");
	if (random == cur) { printf("\n\n\n	       !!!비겼다!!!\n              - !!다시!! -\n\n\n"); Sleep(1000); RockPaperScissor(); }
	else{
		switch (cur) {
		case 1:
			if (random == 2) {printf("\n\n\n	       !!!졌다!!!\n	- 자네, 가위바위보 재수강이네. -\n\n\n"); return 1;}
			else {printf("\n\n\n	       !!!이겼다!!!\n       - 자네, 가위바위보 전공인가? -\n\n\n"); return 0;}
			break;
		case 2:
			if (random == 3) {printf("\n\n\n	       !!!졌다!!!\n	- 자네, 가위바위보 재수강이네. -\n\n\n"); return 1;}
			else {printf("\n\n\n	       !!!이겼다!!!\n       - 자네, 가위바위보 전공인가? -\n\n\n"); return 0;}
			break;
		case 3:
			if (random == 1) {printf("\n\n\n	       !!!졌다!!!\n	- 자네, 가위바위보 재수강이네. -\n\n\n"); return 1;}
			else {printf("\n\n\n	       !!!이겼다!!!\n       - 자네, 가위바위보 전공인가? -\n\n\n"); return 0;}
			break;
		}
	}
    return 0;
}
