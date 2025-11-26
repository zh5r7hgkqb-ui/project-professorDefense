#include "MiniGame.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <windows.h>   // Sleep() 사용

// --------------------------------------------------
//  순서 기억 미니게임 (Sequence Memory Game)
//  - 랜덤 문자 3개 제시 후 숨김
//  - 그대로 입력하면 성공
//  - 성공 시 HP +5 회복
// --------------------------------------------------

int sequenceMiniGame(Player *s)
{
    char seq[4];        
    char user[20];

    const char pool[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    int poolSize = strlen(pool);

    srand((unsigned)time(NULL));

    // 1) 3글자 랜덤 생성
    for (int i = 0; i < 3; i++) {
        seq[i] = pool[rand() % poolSize];
    }
    seq[3] = '\0';

    printf("\n========================================\n");
    printf("           🎮 순서 기억 미니게임\n");
    printf("========================================\n");
    printf("화면에 잠깐 보이는 3글자를 그대로 입력하세요!\n\n");

    // 2) 1초간 제시
    printf(">>> 제시 문자:  %s\n", seq);
    Sleep(1200);

    // 3) 화면 지우기 효과
    for (int i = 0; i < 25; i++) printf("\n");

    // 4) 입력 요청
    printf("입력>> ");
    scanf("%s", user);

    // 5) 판정
    if (strcmp(seq, user) == 0) {
        printf("\n🎉 성공했습니다!\n");
        printf("보상: HP +5 회복!\n");

        s->hp += 5;
        if (s->hp > s->maxHp)
            s->hp = s->maxHp;

        return 1;
    }
    else {
        printf("\n❌ 실패했습니다!\n");
        printf("정답은 %s 였습니다.\n", seq);
        return 0;
    }
}
