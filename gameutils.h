#ifndef GAMEUTILS_H
#define GAMEUTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "struct.h"  


// 초기화 및 설정 함수

// 난수 시드 초기화 (프로그램 시작 시 1회 실행)
void initRandomSeed(void);

// 게임 시작 시 초기 세팅 (이름, 학년 입력, 초기 HP 등)
void initGame(BattleState *bs);

// 퀴즈 파일 불러오기
//  - filename: 파일 경로 (예: "quiz.txt")
//  - quizList: 퀴즈 배열을 저장할 포인터
//  - grade: 현재 플레이어 학년
//  - 반환값: 로드된 문제 수
int loadQuizFile(const char *filename, struct Quiz **quizList, int grade);

// 메모리 해제 (종료 시 퀴즈 배열 free)
void freeQuizList(struct Quiz *quizList);



//  전투 및 퀴즈 진행 함수
//------------------------------------

// 전투 시작 루프 (메인 게임 흐름)
void startBattle(BattleState *bs);

// 한 문제 출제 및 정답 판정
//  - 정답이면 1, 오답이면 0 반환
int askQuestion(BattleState *bs, int index);

// 현재 전투 상태 출력 (HP, 힌트, 남은 문제 등)
void printBattleStatus(const BattleState *bs);

// 게임 결과 출력 (승리 / 패배)
void showResult(const BattleState *bs);



//  아이템 및 힌트 시스템
// -------------------------------------

// 일정 확률(10~20%)로 아이템 드롭 
// 일정 확률(10~20%)로 아이템 드롭 
int dropItem(Player *player);

// 아이템 효과 적용
void useItem(Player *player, const Item *item);

// 힌트 사용 (힌트 출력 및 힌트 수 감소)
void useHint(Player *player, const struct Quiz *quiz);


// 미니게임 시스템 
// -------------------------------------
Item createItem(int type);
int dropItemChance(void);
Item getRandomItem(void);
void applyItemEffect(BattleState *state, Item item);
void tryDropItem(BattleState *state);

#endif



