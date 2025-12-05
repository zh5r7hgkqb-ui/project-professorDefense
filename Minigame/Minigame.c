#include "MiniGame.h"
#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <windows.h>

#pragma execution_character_set("utf-8")

void gotoxy(int x, int y) {
    COORD pos = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

int TimeGame() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    // ===============================
    // 아스키 아트 출력
    // ===============================
    system("cls");
    printAscii("asset/timegame.txt");
    Sleep(1500);
    system("cls");

    // ===============================
    // 메인 화면 (민진 버전 레이아웃)
    // ===============================
    printf("┌────────────────────────────────────────────────────────────┐\n");
    printf("                        TIME ATTACK!                         \n");
    printf("                 10초에 최대한 가깝게 멈춰라!               \n");
    printf("                                                               \n");
    printf("              스페이스바를 누르면 타이머가 멈춥니다        \n");
    printf("└────────────────────────────────────────────────────────────┘\n");
    printf("\n               준비되면 아무 키나 누르세요...\n");

    _getch();
    system("cls");

    // ===============================
    // 카운트다운
    // ===============================
    for (int i = 3; i >= 1; i--) {
        system("cls");
        printf("\n\n\n");
        printf("                             %d\n", i);
        printf("\n\n\n");
        Sleep(800);
    }

    system("cls");
    printf("\n\n\n");
    printf("                           START!\n");
    printf("\n\n\n");
    Sleep(700);
    system("cls");

    // ===============================
    // 타이머 HUD
    // ===============================
    printf("┌────────────────────────────────────────────────────────────┐\n");
    printf("                         실시간 타이머                        \n");
    printf("                                                               \n");
    printf("                        목표 : 10.00초                       \n");
    printf("                                                               \n");
    printf("              스페이스바를 누르면 타이머가 멈춥니다            \n");
    printf("└────────────────────────────────────────────────────────────┘\n");

    // 초기 시간 표시 제거
    clock_t start = clock();

    // ===============================
    // 타이머 실시간 업데이트
    // ===============================
    while (1) {
        if (_kbhit()) {
            if (_getch() == ' ')
                break;
        }

        double elapsed = (double)(clock() - start) / CLOCKS_PER_SEC;

        gotoxy(0, 10);
        printf("현재 시간: %.2f초      ", elapsed);
        fflush(stdout);

        Sleep(10);
    }

    // ===============================
    // 결과 계산
    // ===============================
    system("cls");
    double result = (double)(clock() - start) / CLOCKS_PER_SEC;

    printf("┌────────────────────────────────────────────────────────────┐\n");
    printf("                           결과 화면                           \n");
    printf("--------------------------------------------------------------\n");
    printf("                       당신의 기록 : %.2f초                     \n", result);
    printf("--------------------------------------------------------------\n");

    // ===============================
    // 성공 / 실패 판정
    // ===============================
    if (result >= 9.90 && result <= 10.10) {
        printf("                  성공! 정확한 타이밍입니다!                   \n");
        printf("                  아이템 보상을 획득합니다.                    \n");
        printf("└────────────────────────────────────────────────────────────┘\n");

        printAscii("asset/itemsuccess.txt");
        Sleep(2500);
        
        return 1;
    }
    else {
        printf("                  실패! 다시 도전해보세요!                     \n");
        printf("               정확도 ±0.10초 이내여야 성공입니다              \n");
        printf("└────────────────────────────────────────────────────────────┘\n");

        printAscii("asset/itemfail.txt");
        Sleep(2500);

        return 0;
    }
}

