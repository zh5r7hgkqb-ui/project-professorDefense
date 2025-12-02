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

    // ⭐⭐ 여기 ASCII 아트 표시 ⭐⭐
    system("cls");
    printAscii("asset/timegame.txt");   // ← ASCII 출력
    Sleep(2000);
    system("cls");
    // ⭐⭐ 여기까지 ⭐⭐

    printf("=====================================\n");
    printf("🎯 10초 맞추기 미니게임!\n");
    printf("10초를 기다렸다가 스페이스바를 누르세요.\n");
    printf("아무 키나 누르면 시작!\n");
    printf("=====================================\n");
    _getch();

    system("cls");
    printf("🔥 타이머 시작!\n");
    printf("⏱ 현재 시간: 0.00초\n");

    clock_t start = clock();

    while (1) {
        if (_kbhit()) {
            if (_getch() == ' ') break;
        }

        clock_t now = clock();
        double elapsed = (double)(now - start) / CLOCKS_PER_SEC;

        // 커서를 "⏱ 현재 시간:" 있는 줄로 이동시켜 한 줄만 업데이트
        gotoxy(0, 1);
        printf("⏱ 현재 시간: %.2f초  ", elapsed);

        fflush(stdout);
        Sleep(10);
    }

    clock_t end = clock();
    double result = (double)(end - start) / CLOCKS_PER_SEC;

    printf("\n\n⏱ 최종 기록: %.2f 초\n", result);

     //  여기만 수정됨 — 성공/실패 return 추가
    if (result >= 9.90 && result <= 10.10) {
        printf("🎉 성공! 정확합니다!\n");
        return 1;   // 성공 반환
    }
    else {
        printf("💀 실패! 다시 도전하세요!\n");
        return 0;   // 실패 반환
    }

    // 기존 코드의 return 0 제거됨 
}


