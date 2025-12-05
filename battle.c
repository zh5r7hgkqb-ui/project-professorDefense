#include "gameutils.h"
#include "MiniGame.h"
#include <stdio.h>
#include <string.h>
#include <Windows.h>
#pragma execution_character_set("utf-8")

int main(void);   // 🔥 재도전 위해 main() 미리 선언

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
// 전투 결과 + 엔딩 + 재도전
void showResult(const BattleState *bs)
{
    system("cls");

    // ============================
    // 1) 승리 / 패배 아스키아트 + 감성 문구
    // ============================
    if (bs->student.hp <= 0) {
        // 패배 아스키아트
        FILE *failure = fopen("asset/failure.txt","r");
        if (failure) {
            char failurearr[4096];
            while (fgets(failurearr, sizeof(failurearr), failure)) {
                printf("%s", failurearr);
            }
            fclose(failure);
        }

        printf("\n==============================================================\n");
        printf("                     교수님 : \"학점? 글쎄요~^^\"\n");
        printf("==============================================================\n\n");

        printf("최선을 다했지만...  \n");
        printf("교수님의 냉정함 앞에서 힘을 잃고 말았다.\n\n");

        printf("하지만 실망하긴 이르다.\n");
        printf("다음 번엔 더 똑똑해진 당신이  \n");
        printf("교수님을 향해 미소 지을지도 모른다.\n\n");
    }
    else if (bs->professor.hp <= 0) {
        // 승리 아스키아트
        FILE *success = fopen("asset/success.txt","r");
        if (success) {
            char successarr[4096];
            while (fgets(successarr, sizeof(successarr), success)) {
                printf("%s", successarr);
            }
            fclose(success);
        }

        printf("\n==============================================================\n");
        printf("                     승리! 학점을 지켜냈다!\n");
        printf("==============================================================\n\n");

        printf("오늘도 교수님의 강의는 만만치 않았지만  \n");
        printf("당신은 끝까지 포기하지 않았습니다.\n\n");

        printf("지식으로 쌓은 노력,  \n");
        printf("집중력으로 버틴 시간들,\n");
        printf("그 모든 것들이 하나 되어  \n");
        printf("드디어 교수님을 쓰러뜨렸습니다!\n\n");

        printf("당신의 학점은...  \n");
        printf("지켜냈습니다.\n\n");

        printf("이 승리는 절대 우연이 아닙니다.\n");
        printf("당신의 노력의 결과입니다.\n\n");
    }
    else {
        // 둘 다 안 죽은 애매한 경우(문제 다 소진 등)
        printf("\n모든 문제를 풀었지만 교수님을 쓰러뜨리진 못했습니다...\n\n");
    }

    // ============================
    // 2) 재도전 / 종료 선택 메뉴
    // ============================
    int choice;

    printf("==============================================================\n");
    printf("            [ 1. 다시 도전하기 ]    [ 2. 종료하기 ]\n");
    printf("==============================================================\n");
    printf("선택: ");

    if (scanf("%d", &choice) != 1) {
        choice = 2;
    }
    while (getchar() != '\n');  // 버퍼 비우기

    if (choice == 1) {
        // 다시 게임 전체 재시작
        system("cls");
        main();        // 🔥 메인 함수 다시 호출해서 로딩/인트로/전투 전부 처음부터
    } else {
        // 바로 종료
        exit(0);
    }
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
    if (prnormal) {
        char prnprint[100];
        while (fgets(prnprint, sizeof(prnprint), prnormal)) printf("%s", prnprint);
        fclose(prnormal);
    }

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
            if (prangry) {
                char praprint[100];
                while (fgets(praprint, sizeof(praprint), prangry)) printf("%s", praprint);
                fclose(prangry);
            }

            printf("정답! 교수님에게 5 데미지를 주었습니다!\n");
        }
        else {
            bs->correctStreak = 0;
            bs->student.hp -= 5;
            if (bs->student.hp < 0) bs->student.hp = 0;

            printBattleStatus(bs);

            FILE* prhappy = fopen("asset/pro_happy.txt", "r");
            if (prhappy) {
                char prhprint[100];
                while (fgets(prhprint, sizeof(prhprint), prhappy)) printf("%s", prhprint);
                fclose(prhappy);
            }

            printf(" 오답! 학생이 5 데미지를 받았습니다!\n");
        }

        if (bs->correctStreak >= 3 && bs->professor.hp > 0) {
            system("cls");
            printf("\n✨ 3회 연속 정답! 미니게임이 등장합니다!\n");
            
             FILE *mg = fopen("asset/minigame.txt", "r");
             if (mg) {
             char line[4096];
             while (fgets(line, sizeof(line), mg)) {
            printf("%s", line);
             }
             fclose(mg);
           } else {
             printf("[minigame.txt 파일을 찾을 수 없습니다]\n\n");
           }

            printf("\n잠시 후 미니게임이 시작됩니다...\n");
            Sleep(3500);

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

    // 🔥 전투 끝나면 엔딩 + 재도전 처리
    showResult(bs);
}

