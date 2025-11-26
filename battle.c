#include "gameutils.h"
#include "MiniGame.h"
#include <stdio.h>
#include <string.h>
#pragma execution_character_set("utf-8")

// 미니게임 함수 
int sequenceMiniGame(Player *s);

// --------------------------------------------------
// HP 바 출력 함수
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
// 문제 출제 및 정답 판정
int askQuestion(BattleState *bs, int index)
{
    struct Quiz *q = bs->quizList;

    for (int i = 0; i < index; i++) {
        if (q == NULL) return 0;
        q = q->next;
    }
    if (q == NULL) return 0;

    printf("\n==============================\n");
    printf("문제 %d\n", index + 1);
    printf("Q: %s\n", q->question);

    if (bs->student.hintCount > 0) {
        printf("힌트를 사용하시겠습니까? (y/n): ");
        char c;
        scanf(" %c", &c);

        if (c == 'y') {
            useHint(&bs->student, q);
        }
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
// 전투 상태 출력
void printBattleStatus(const BattleState *bs)
{
    printf("\n==============================\n");

    printf("학생 HP: ");
    printHpBar(bs->student.hp, bs->student.maxHp);

    printf("힌트: %d\n", bs->student.hintCount);
    printf("------------------------------\n");

    printf("교수님 HP: ");
    printHpBar(bs->professor.hp, bs->professor.maxHp);

    printf("==============================\n");
}


// --------------------------------------------------
// 전투 결과 출력
void showResult(const BattleState *bs)
{
    printf("\n==============================\n");

    if (bs->student.hp <= 0) {
        FILE *failure=fopen("asset/failure.txt","r");
        char failurearr[4096];
        while (fgets(failurearr, sizeof(failurearr), failure)) {
            printf("%s", failurearr);
        }
        fclose(failure);
        printf("\n 패배... 교수님의 강의는 너무 어려웠다.\n");
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
    }
    else {
        printf("모든 문제를 풀었지만 교수님을 쓰러뜨리진 못했습니다.\n");
    }

    printf("==============================\n");
}


// --------------------------------------------------
// 전투 루프 (미니게임 포함 최종 버전)
void startBattle(BattleState *bs)
{
    printf("\n전투 시작! 교수님이 나타났다!\n");

    while (bs->student.hp > 0 && bs->professor.hp > 0)
    {
        printBattleStatus(bs);

        int correct = askQuestion(bs, bs->currentQuiz);

        // ------------------------------
        // 정답 처리 + streak 관리
        if (correct) {
            bs->correctStreak++;   //  연속 정답 증가

            bs->professor.hp -= 10;
            if (bs->professor.hp < 0) bs->professor.hp = 0;

            printf("정답! 교수님에게 10 데미지를 주었습니다!\n");

            int itemType = dropItem(&bs->student);
            if (itemType == 3) {
                bs->professor.hp -= 10;
                if (bs->professor.hp < 0) bs->professor.hp = 0;
                printf(" 아이템 효과! 교수님 추가 데미지 -10!\n");
            }
        }
        // ------------------------------
        // 오답 처리
        else {
            bs->correctStreak = 0; // ⭐ 연속 정답 초기화

            bs->student.hp -= 5;
            if (bs->student.hp < 0) bs->student.hp = 0;

            printf(" 오답! 학생이 5 데미지를 받았습니다!\n");
        }


        //  미니게임 등장 조건: 3회 연속 정답
        if (bs->correctStreak >= 3) {
            printf("\n✨ 3회 연속 정답! 미니게임이 등장합니다!\n");

            int randmini=rand()%5+1;
            int result;
            
            switch(randmini){
            case 1:
                 result = miniGame_Sequence(); 
               break;
            case 2:
                 result = miniGame2_UpDown(); 
               break;
            case 3:
                 result = minigame_minesweeper(); 
               break;
            case 4:
                 result = RockPaperScissor(); 
               break;
            case 5:
                 result = TimeGame(); 
               break;
            }   

            if (result == 1){
                printf("미니게임 성공!\n");
                dropItem(&bs->student);}
            else
                printf("미니게임 실패! 보상 없음.\n");

            bs->correctStreak = 0; //  streak 초기화
        }


        // 퀴즈 다음 문제로
        bs->currentQuiz++;

        if (bs->currentQuiz >= bs->quizCount) {
            printf("\n 모든 문제를 풀었습니다!\n");
            break;
        }
    }

    showResult(bs);
}

