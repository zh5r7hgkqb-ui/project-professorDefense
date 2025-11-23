#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "gameutils.h"
#include <locale.h>
#include <windows.h>

// -------------------------------------------
// 난수 초기화
// -------------------------------------------
void initRandomSeed(void) {
    srand((unsigned int)time(NULL));
}

// -------------------------------------------
// 게임 초기화
// -------------------------------------------
void initGame(BattleState *bs) {
    //입출력 인코딩 UTF-8 설정
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    //메인 메뉴 파일 열기 및 출력
    FILE *mainmenu=fopen("mainmenu.txt","r");
    char mainmenuarr[4096];
    while (fgets(mainmenuarr, sizeof(mainmenuarr), mainmenu)) {
        printf("%s", mainmenuarr);
    }
    fclose(mainmenu);

    printf("학생 이름을 입력하세요: ");
    scanf("%s", bs->student.name);

    do {
        printf("학년을 입력하세요 (1~4): ");
        scanf("%d", &bs->student.grade);
    } while (bs->student.grade < 1 || bs->student.grade > 4);

    // 학생 초기값 설정
    bs->student.maxHp = 30;
    bs->student.hp = bs->student.maxHp;
    bs->student.hintCount = 2;

    // 교수님 초기값 설정 (학년별 난이도 조정)
    snprintf(bs->professor.name, sizeof(bs->professor.name), "교수님");
    bs->professor.maxHp = 20 + (bs->student.grade - 1) * 10;
    bs->professor.hp = bs->professor.maxHp;

    printf("\n 학생 %s (%d학년) 전투를 준비하세요!\n", bs->student.name, bs->student.grade);
    printf("교수님 HP: %d\n", bs->professor.maxHp);
    printf("==============================\n");
}

// -------------------------------------------
// 메인 함수
// -------------------------------------------
int main(void) {
    setlocale(LC_ALL, "");
    BattleState game;

    initRandomSeed();  // 난수 초기화
    initGame(&game);   // 게임 초기화

    // 퀴즈 파일 불러오기
    int count = loadQuizFile("quiz.txt", &game.quizList, game.student.grade);
    if (count == 0) {
        printf("문제를 불러오지 못했습니다. 게임을 종료합니다.\n");
        return 1;
    }

    game.quizCount = count;
    game.currentQuiz = 0;

    // 전투 시작
    startBattle(&game);

    // 메모리 해제
    freeQuizList(game.quizList);

    return 0;
}
