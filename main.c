#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "gameutils.h"
#include <locale.h>
#include <windows.h>

// 글자 하나씩 찍어주는 타자기 효과 함수

void typeWriter(const char* text, int delay) {
    while (*text) {
        putchar(*text);
        fflush(stdout);
        Sleep(delay);
        text++;
    }
}


// -------------------------------------------
// 로딩 씬 출력 함수
void showLoadingScene() {
    system("cls");

    printf(
"               ██████╗      █████╗     ███╗   ███╗    ███████╗\n"
"              ██╔════╝     ██╔══██╗    ████╗ ████║    ██╔════╝\n"
"              ██║  ███╗    ███████║    ██╔████╔██║    █████╗  \n"
"              ██║   ██║    ██╔══██║    ██║╚██╔╝██║    ██╔══╝  \n"
"              ╚██████╔╝    ██║  ██║    ██║ ╚═╝ ██║    ███████╗\n"
"               ╚═════╝     ╚═╝  ╚═╝    ╚═╝     ╚═╝    ╚══════╝\n"
"\n"
"                         [   학 점   수 호 대   ]\n"
"\n"
"       ╔══════════════════════════════════════════════════════════╗\n"
"       ║                                                          ║\n"
"       ║    ( ｀皿´)_╦︵╦   교수님이 천천히 다가오고 있습니다…  ║\n"    //일부러 이모티콘 깨지게 함 (콘솔 호환용)
"       ║                                                          ║\n"
"       ╚══════════════════════════════════════════════════════════╝\n"
"\n"
    );

    printf("                         잠시만 기다려 주세요"); 
    Sleep(1800);

    printf("."); 
    Sleep(1800);

    printf("."); 
    Sleep(1800);

    printf(".\n");  // 마지막에만 개행
    Sleep(500);
}

// -------------------------------------------

void showIntro() {
    printf("==============================================================\n");
    printf("                        [ 학점의 역습 ]\n\n");

    typeWriter("충북대 컴퓨터공학과 학생인 당신…\n", 60);
    typeWriter("이번 학기에 악명 높은 '그 교수님'의 수업을 듣게 되었다!\n\n", 60);

    typeWriter("교수님은 학생들에게 학점을 쉽게 주지 않기로 유명하다.\n", 60);
    typeWriter("매 시간마다 점점 더 어려워지는 문제를 내며,\n", 60);
    typeWriter("학생들의 정신과 체력을 갉아먹고 있다…\n\n", 60);

    typeWriter("하지만 이번 학기만큼은…\n", 60);
    typeWriter("당신의 학점을 지켜내기 위해 도전해야 한다!\n\n", 60);

    typeWriter("▶ 문제를 풀어 지식을 모아라!\n", 50);
    typeWriter("▶ 아이템을 획득해 위기를 넘겨라!\n", 50);
    typeWriter("▶ 교수님의 체력을 0으로 만들어 학점을 되찾아라!\n\n", 50);

    printf("==============================================================\n");
    printf("             계속하려면 Enter 키를 누르세요...\n");

    getchar();  // 엔터 입력 대기 (인트로 끝)
}

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
    bs->professor.maxHp = 30;
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
    //  한글 깨짐 해결 
    // ========================================
    setlocale(LC_ALL, "ko_KR.UTF-8");
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    // ========================================

    system("cls");
    showLoadingScene(); // 로딩 씬 출력
    Sleep(2000);
    system("cls");
    showIntro(); // 인트로 출력
    
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




