#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "struct.h"

// ----------------------------------------------------------
// 1. 아이템 생성 함수, effectType에 따라 아이템 이름 또는 설명 설정

Item createItem(int type) {
    Item item;

    if (type == 1) {   // 학생 HP 회복
        sprintf(item.name, "회복 물약");
        sprintf(item.description, "학생 HP를 회복시켜주는 아이템");
        item.effectType = 1;
        item.effectValue = 5;   // 회복량
    }
    else if (type == 2) {  // 교수 HP 감소
        sprintf(item.name, "급습의 단검");
        sprintf(item.description, "교수님의 HP를 감소시키는 아이템");
        item.effectType = 2;
        item.effectValue = 5;   // 감소량
    }
    else {  // type == 3, 힌트 추가권
        sprintf(item.name, "힌트 스크롤");
        sprintf(item.description, "힌트 1개를 추가로 제공");
        item.effectType = 3;
        item.effectValue = 1;   // 힌트 +1
    }

    return item;
}

// ----------------------------------------------------------
// 2. 아이템 드랍 확률 계산: 20% 확률로 드랍

int dropItemChance() {
    int r = rand() % 100;  
    return (r < 20);        // 20% 확률로 설정
}

// ----------------------------------------------------------
// 3. 랜덤 아이템 생성: 1~3 중 하나

Item getRandomItem() {
    int type = (rand() % 3) + 1;   // 1, 2, 3 중 랜덤으로..
    return createItem(type);
}

// ----------------------------------------------------------
//  아이템 효과 적용

void applyItemEffect(BattleState* state, Item item) {

    if (item.effectType == 1) {
        // 학생 HP 회복
        state->student.hp += item.effectValue;
        if (state->student.hp > state->student.maxHp)
            state->student.hp = state->student.maxHp;

        printf("[아이템 효과] 학생 HP가 %d만큼 회복되었습니다!\n",
            item.effectValue);
    }

    else if (item.effectType == 2) {
        // 교수님 HP 감소
        state->professor.hp -= item.effectValue;
        if (state->professor.hp < 0)
            state->professor.hp = 0;

        printf("[아이템 효과] 교수님의 HP가 %d만큼 감소했습니다!\n",
            item.effectValue);
    }

    else if (item.effectType == 3) {
        // 힌트 +1
        state->student.hintCount += item.effectValue;

        printf("<아이템 효과> 힌트 사용권이 %d개 증가했습니다!\n",
            item.effectValue);
    }
}


// ----------------------------------------------------------
//  전투 중 아이템 처리 절차
//    구조: 문제 정답 → 아이템 드랍 여부 → 효과 적용

void tryDropItem(BattleState* state) {

    if (!dropItemChance()) {
        // 아이템이 드랍되지 않은 경우
        printf("이번에는 아이템이 드랍되지 않았습니다.\n");
        return;
    }

    // 아이템 드랍!
    Item item = getRandomItem();

    printf("\n*** 아이템 획득! ***\n");
    printf("아이템 이름 : %s\n", item.name);
    printf("설명 : %s\n", item.description);

    // 효과 적용
    applyItemEffect(state);
}
