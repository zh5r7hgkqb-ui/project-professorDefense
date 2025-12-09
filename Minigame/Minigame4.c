#include "MiniGame.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include<conio.h>

#pragma execution_character_set("utf-8")

int miniGame_Sequence()
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    srand((unsigned int)time(NULL));

    int length = 5;
    int seq[10];
    int answer[10];
    
   //  ASCII 아트 출력
    system("cls");
    printAscii("asset/sequence.txt");   // ← 파일만 만들면 됨
    Sleep(2500);
    system("cls");
    //  여기까지 아스키 아트 

    printf("=====================================\n");
    printf("🧠 순서 기억 미니게임\n");
    printf("제시되는 숫자들을 순서대로 입력하세요!\n");
    printf("아무 키나 누르면 시작합니다.\n");
    printf("=====================================\n");
    _getch();
    system("cls");

    // 수열 생성
    for (int i = 0; i < length; i++) {
        seq[i] = rand() % 9 + 1;
    }

    printf("👇 아래 숫자를 순서대로 기억하세요!\n\n");
    for (int i = 0; i < length; i++) {
        printf("%d ", seq[i]);
        Sleep(700);
    }

    Sleep(1500);
    system("cls");

    printf("이제 순서대로 입력하세요!\n");

    for (int i = 0; i < length; i++) {
        printf("[%d] 번째 숫자: ", i + 1);
        scanf("%d", &answer[i]);
    }

    // 판정
    for (int i = 0; i < length; i++) {
        if (seq[i] != answer[i]) {
            printf("\n❌ 틀렸습니다!\n");
            
            printAscii("asset/itemfail.txt");
            Sleep(2500);
            
            return 0;   // 실패
        }
    }

    printf("\n🎉 성공! 완벽하게 기억했습니다!\n");

    printAscii("asset/itemsuccess.txt");
    Sleep(2500);

    return 1; // 성공
}
