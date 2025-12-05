#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "struct.h"

// ----------------------------------------------
// 아이템 효과 타입 (battle.c 기준으로 통일)
// 1 = 학생 HP 회복
// 2 = 힌트 추가
// 3 = 교수님 데미지 아이템 (실제 데미지는 battle.c에서 처리)
// ----------------------------------------------

static Item itemList[3] = {
    {"회복 물약", "학생 HP를 회복합니다.", 1, 5},   // HP +5
    {"힌트 스크롤", "힌트 1개를 추가로 제공합니다.", 2, 1}, // 힌트 +1
    {"급습의 단검", "교수님에게 추가 데미지를 줄 수 있습니다.", 3, 10} // 교수 데미지 10
};


// -------------------------------------------------------
//설명:
// 20% 확률로 아이템 드랍 + 효과 즉시 적용 후 effectType 반환
// return값:
// 0 = 드랍 없음
// 1 = HP 회복
// 2 = 힌트 추가
// 3 = 교수님 추가 데미지 (battle.c에서 처리)



int dropItem(Player *player)
{
   

    // 랜덤 아이템 선택
    int idx = rand() % 3;
    Item *drop = &itemList[idx];

    printf("\n🎁 아이템 드랍! → %s\n", drop->name);

    // -----------------------------------
    // 아이템 효과 적용(학생 관련만 처리)
    // 교수님 데미지는 battle.c에서 따로 처리
    switch (drop->effectType)
    {
        case 1: // HP 회복
            player->hp += drop->effectValue;
            if (player->hp > player->maxHp)
                player->hp = player->maxHp;
            printf("❤️ HP +%d → 현재 HP: %d\n", drop->effectValue, player->hp);
            break;

        case 2: // 힌트 +1
            player->hintCount += drop->effectValue;
            printf("💡 힌트 +%d → 현재 힌트: %d\n",
                   drop->effectValue, player->hintCount);
            break;

        case 3:
            // battle.c에서 교수 HP 감소 처리
            printf("⚔️ 교수님에게 %d 추가 데미지를 줄 수 있는 아이템 획득!\n",
                   drop->effectValue);
            break;

        default:
            printf("❓ 알 수 없는 아이템 효과\n");
            break;
    }

    return drop->effectType;
}

void useHint(Player *player, const struct Quiz *quiz){
    if (player->hintCount > 0) {
        printf("힌트: %s\n", quiz->hint);
        player->hintCount--;
    } else {
        printf("사용 가능한 힌트가 없습니다!\n");
    }
}
