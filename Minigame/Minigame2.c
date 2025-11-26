#include "MiniGame.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>

#pragma execution_character_set("utf-8")

// --------------------------------------------------
// 미니게임 2: UP & DOWN 숫자 맞추기
// 성공 기준: 8회 안에 정답 맞히기
// 성공/실패만 반환 (보상은 battle.c에서 처리)
// --------------------------------------------------

int miniGame2_UpDown()
{
    const int MAX_NUMBER = 100;
    const int MAX_ATTEMPTS = 8;

    int secretNumber;
    int guess;
    int attempts = 0;

    srand((unsigned)time(NULL));

    printf("======================================\n");
    printf("⬆️⬇️  UP & DOWN 숫자 맞추기 게임\n");
    printf("======================================\n");
    printf("1부터 %d까지 숫자 중 하나를 맞혀보세요! (시도 %d회)\n",
           MAX_NUMBER, MAX_ATTEMPTS);

    secretNumber = (rand() % MAX_NUMBER) + 1;

    while (attempts < MAX_ATTEMPTS)
    {
        printf("\n[%d/%d] 숫자를 입력 >> ", attempts + 1, MAX_ATTEMPTS);

        // 입력 오류 방지
        if (scanf("%d", &guess) != 1) {
            printf("⚠️ 잘못된 입력! 숫자를 입력하세요.\n");
            while (getchar() != '\n');
            continue;
        }
        while (getchar() != '\n');

        attempts++;

        if (guess == secretNumber) {
            printf("\n🎉 성공! %d번 만에 정답 %d을 맞혔습니다!\n",
                   attempts, secretNumber);

            return 1;   // ⭐ 성공 → 보상은 battle.c에서 처리
        }
        else if (guess < 1 || guess > MAX_NUMBER) {
            printf("🚫 범위를 벗어났습니다. (1~%d)\n", MAX_NUMBER);
            attempts--;   // 범위 오류는 시도 횟수 차감 X
        }
        else if (guess < secretNumber) {
            printf("⬆️ UP! 더 큽니다.\n");
        }
        else {
            printf("⬇️ DOWN! 더 작습니다.\n");
        }

        if (attempts < MAX_ATTEMPTS) {
            printf("남은 시도: %d\n", MAX_ATTEMPTS - attempts);
        }
    }

    printf("\n❌ 실패! %d번의 시도 내 정답을 맞히지 못했습니다.\n",
           MAX_ATTEMPTS);
    printf("정답은 %d이었습니다.\n", secretNumber);

    return 0;  // 실패
}
