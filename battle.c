#include "gameutils.h"
#include <stdio.h>
#include <string.h>


// --------------------------------------------------
// HP 바 출력 함수 (■ = 채워진칸, □ = 빈칸)

void printHpBar(int current, int max)
{
    int barLength = 20;  // 표시할 전체 길이
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

    // index번째 문제까지 이동
    for (int i = 0; i < index; i++) {
        if (q == NULL) return 0;
        q = q->next;
    }
    if (q == NULL) return 0;

    printf("\n==============================\n");
    printf("📘 문제 %d\n", index + 1);
    printf("Q: %s\n", q->question);

    // 힌트 기능
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
        printf("⭕ 정답!\n");
        q->used = 1;
        return 1;
    }
    else {
        printf("❌ 오답! (정답: %s)\n", q->answer);
        q->used = 1;
        return 0;
    }
}


// --------------------------------------------------
// 전투 상태 출력

void printBattleStatus(const BattleState *bs)
{
    printf("\n==============================\n");

    // 학생 HP 바 출력
    printf("👨‍🎓 학생 HP: ");
    printHpBar(bs->student.hp, bs->student.maxHp);

    printf("💡 힌트: %d\n", bs->student.hintCount);
    printf("------------------------------\n");

    // 교수님 HP 바 출력
    printf("👨‍🏫 교수님 HP: ");
    printHpBar(bs->professor.hp, bs->professor.maxHp);

    printf("==============================\n");
}


// --------------------------------------------------
// 전투 결과 출력

void showResult(const BattleState *bs)
{
    printf("\n==============================\n");

    if (bs->student.hp <= 0) {
        printf("💀 패배... 교수님의 강의는 너무 어려웠다.\n");
    }
    else if (bs->professor.hp <= 0) {
        printf("🎉 승리! 교수님을 무찔렀다!\n");
        printf("📚 당신의 학점을 지켜냈습니다!\n");
    }
    else {
        printf("📘 모든 문제를 풀었지만 교수님을 쓰러뜨리진 못했습니다.\n");
    }

    printf("==============================\n");
}


// --------------------------------------------------
// 전투 루프 

void startBattle(BattleState *bs)
{
    printf("\n⚔️ 전투 시작! 교수님이 나타났다!\n");

    while (bs->student.hp > 0 && bs->professor.hp > 0)
    {
        printBattleStatus(bs);

        int correct = askQuestion(bs, bs->currentQuiz);

        // ------------------------------
        // 정답 처리 과정
        
        if (correct) {
            bs->professor.hp -= 10;
            if (bs->professor.hp < 0) bs->professor.hp = 0;

            printf("⚔️ 정답! 교수님에게 10 데미지를 주었습니다!\n");

            // 아이템 드랍
            int itemType = dropItem(&bs->student);

            // 효과Type 3 = 교수님 추가 데미지
            if (itemType == 3) {
                bs->professor.hp -= 10;
                if (bs->professor.hp < 0) bs->professor.hp = 0;
                printf("💥 아이템 효과! 교수님 추가 데미지 -10!\n");
            }
        }

        // ------------------------------
        // 오답 처리
        
        else {
            bs->student.hp -= 5;
            if (bs->student.hp < 0) bs->student.hp = 0;

            printf("💥 오답! 학생이 5 데미지를 받았습니다!\n");
        }

        bs->currentQuiz++;

        // 끝 
        if (bs->currentQuiz >= bs->quizCount) {
            printf("\n📘 모든 문제를 풀었습니다!\n");
            break;
        }
    }

    showResult(bs);
}

