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

    //메인 메뉴 파일 출력
    system("cls");
    FILE *mainmenu=fopen("asset/mainmenu.txt","r");
    if (mainmenu) {
        char mainmenuarr[4096];
        while (fgets(mainmenuarr, sizeof(mainmenuarr), mainmenu)) {
            printf("%s", mainmenuarr);
        }
        fclose(mainmenu);
    }

    printf("\n학생 이름을 입력하세요: ");
    scanf("%s", bs->student.name);

    do {
    printf("학년을 입력하세요 (1~4): ");

    if (scanf("%d", &bs->student.grade) != 1) {
        printf("잘못된 입력입니다! 숫자를 입력해주세요.\n");

        // 버퍼 비우기
        while (getchar() != '\n');

        continue;
    }

    // 정상 입력 후 버퍼에 남은 '\n' 제거
    while (getchar() != '\n');

    if (bs->student.grade < 1 || bs->student.grade > 4)
        printf("잘못된 범위입니다! 1~4 사이로 입력해주세요.\n");

} while (bs->student.grade < 1 || bs->student.grade > 4);

    system("cls");
    // 학생 초기값 설정
    bs->student.maxHp = 30;
    bs->student.hp = bs->student.maxHp;
    bs->student.hintCount = 2;

    // 교수님 초기값 설정 (학년별 난이도 조정)
    snprintf(bs->professor.name, sizeof(bs->professor.name), "교수님");
    bs->professor.maxHp = 20 + (bs->student.grade - 1) * 10;
    bs->professor.hp = bs->professor.maxHp;

    printf("\n 학생 %s (%d학년) 전투를 준비하세요!\n",
           bs->student.name, bs->student.grade);
    printf("교수님 HP: %d\n", bs->professor.maxHp);
    printf("======================================\n");
}

// -------------------------------------------
// 메인 함수 (UTF-8 완전 지원 버전)
// -------------------------------------------
int main(void) {

    // ========================================
    //  한글 깨짐 해결 (이 3줄이 핵심)
    // ========================================
    setlocale(LC_ALL, "ko_KR.UTF-8");
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    // ========================================

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


