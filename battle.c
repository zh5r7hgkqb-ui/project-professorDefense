#include "gameutils.h"
#include "MiniGame.h"
#include <stdio.h>
#include <string.h>
#include <Windows.h>
#pragma execution_character_set("utf-8")

// 미니게임 함수 
int sequenceMiniGame(Player *s);

// --------------------------------------------------
//  문제(Q:)만 줄바꿈하는 함수
void printWrapped(const char* text, int width) {
    int lineLen = 0;

    while (*text) {
        putchar(*text);
        lineLen++;

        if (lineLen >= width && *text == ' ') {
            putchar('\n');
            lineLen = 0;
        }
        text++;
    }
    putchar('\n');
}

// --------------------------------------------------
// HP 바 출력
void printHpBar(int current, int max)
{
    int barLength = 20;
    int filled = (current * barLength) / max;
    int empty = barLength - filled;

    printf("[");
    for (int i = 0; i < filled; i++) printf("■");
    for (int i = 0; i < empty; i++) printf("□");
    printf("] %d/%d\n", current, max);
}

// --------------------------------------------------
// 전투 상태 출력
void printBattleStatus(const BattleState *bs)
{
    printf("\n===========================================================\n");

    printf("학생 HP: ");
    printHpBar(bs->student.hp, bs->student.maxHp);

    printf("힌트: %d\n", bs->student.hintCount);
    printf("------------------------------\n");

    printf("교수님 HP: ");
    printHpBar(bs->professor.hp, bs->professor.maxHp);

    printf("===========================================================\n");
}

// --------------------------------------------------
// 전투 결과 출력
void showResult(const BattleState *bs)
{
    system("cls");
    printf("\n=======================================\n");

    if (bs->student.hp <= 0) {
        FILE *failure=fopen("asset/failure.txt","r");
        char failurearr[4096];
        while (fgets(failurearr, sizeof(failurearr), failure)) {
            printf("%s", failurearr);
        }
        fclose(failure);
        printf("\n 패배... 교수님의 강의는 너무 어려웠다.\n");
        Sleep(3000);
        
        system("cls");
    }
    else if (bs->professor.hp <= 0) {
        FILE *success=fopen("asset/success.txt","r");
        char successarr[4096];
        while (fgets(successarr, sizeof(successarr), success)) {
            printf("%s", successarr);
        }
        fclose(success);
        printf("\n 승리! 교수님을 무찔렀다!\n");
        printf(" 당신의 학점을 지켜냈습니다!\n");

     
        Sleep(3000);
        
        system("cls");
    }
    else {
        printf("모든 문제를 풀었지만 교수님을 쓰러뜨리진 못했습니다!\n");
        Sleep(3000);
        
        system("cls");
    }

    
    printf("=======================================\n");
    printf("   게임이 종료되었습니다.\n");
    printf("=======================================\n");
    printf("엔터를 누르면 종료됩니다...");

    getchar();  
    getchar();
}


// --------------------------------------------------
// 학년 필터 + 랜덤 문제 추출
struct Quiz* getRandomQuiz(BattleState *bs)
{
    struct Quiz *q = bs->quizList;
    struct Quiz *candidates[200]; 
    int count = 0;

    int targetGrade = bs->student.grade;

    while (q != NULL) {
        if (q->difficulty == targetGrade && q->used == 0) {
            candidates[count++] = q;
        }
        q = q->next;
    }

    if (count == 0) return NULL;

    int idx = rand() % count;
    return candidates[idx];
}

// --------------------------------------------------
// 특정 문제 출제
int askQuizDirectly(BattleState *bs, struct Quiz *q)
{
    printf("Q: ");
    printWrapped(q->question, 45);

    FILE* prnormal = fopen("asset/pro_normal.txt", "r");
    char prnprint[100];
    while (fgets(prnprint, sizeof(prnprint), prnormal)) printf("%s", prnprint);
    fclose(prnormal);

    if (bs->student.hintCount > 0) {
        printf("힌트를 사용하시겠습니까? (y/n): ");
        char c;
        scanf(" %c", &c);
        while (getchar() != '\n');

        if (c == 'y' || c == 'Y')
            useHint(&bs->student, q);
    }

    char ans[100];
    printf("정답 입력: ");
    scanf("%s", ans);

    if (strcmp(ans, q->answer) == 0) {
        printf("정답!\n");
        q->used = 1;
        return 1;
    }
    else {
        printf("오답! (정답: %s)\n", q->answer);
        q->used = 1;
        return 0;
    }
}

// --------------------------------------------------
// 전투 루프
void startBattle(BattleState *bs)
{
    // 🔥 교수 HP 30 고정
    bs->professor.maxHp = 30;
    bs->professor.hp    = 30;

    bs->correctStreak = 0;
    printf("\n전투 시작! 교수님이 나타났다!\n");
    
    while (bs->student.hp > 0 && bs->professor.hp > 0)
    {
        Sleep(3000);
        system("cls");
        printBattleStatus(bs);

        struct Quiz *selected = getRandomQuiz(bs);
        if (selected == NULL) break;

        int correct = askQuizDirectly(bs, selected);
        system("cls");

        if (correct) {
            bs->correctStreak++;
            bs->professor.hp -= 5;
            if (bs->professor.hp < 0) bs->professor.hp = 0;

            printBattleStatus(bs);

            FILE* prangry = fopen("asset/pro_angry.txt", "r");
            char praprint[100];
            while (fgets(praprint, sizeof(praprint), prangry)) printf("%s", praprint);
            fclose(prangry);

            printf("정답! 교수님에게 5 데미지를 주었습니다!\n");
        }
        else {
            bs->correctStreak = 0;
            bs->student.hp -= 5;
            if (bs->student.hp < 0) bs->student.hp = 0;

            printBattleStatus(bs);

            FILE* prhappy = fopen("asset/pro_happy.txt", "r");
            char prhprint[100];
            while (fgets(prhprint, sizeof(prhprint), prhappy)) printf("%s", prhprint);
            fclose(prhappy);

            printf(" 오답! 학생이 5 데미지를 받았습니다!\n");
        }

        if (bs->correctStreak >= 3 && bs->professor.hp > 0) {
            system("cls");
            printf("\n✨ 3회 연속 정답! 미니게임이 등장합니다!\n");
            Sleep(4000);
            system("cls");

            int randmini = rand() % 5 + 1;
            int result;

            switch(randmini){
            case 1: result = miniGame_Sequence(); break;
            case 2: result = miniGame2_UpDown(); break;
            case 3: result = minigame_minesweeper(); break;
            case 4: result = RockPaperScissor(); break;
            case 5: result = TimeGame(); break;
            }

            if (result == 1) {
                printf("미니게임 성공!\n");
                dropItem(&bs->student);
            }
            else {
                printf("미니게임 실패! 보상 없음.\n");
            }

            bs->correctStreak = 0;
        }

        bs->currentQuiz++;
        if (bs->currentQuiz >= bs->quizCount) break;
    }

    showResult(bs);
}
