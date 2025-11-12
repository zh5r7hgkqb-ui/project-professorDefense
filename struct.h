#ifndef STRUCT_H
#define STRUCT_H


//  플레이어(학생) 구조체
// ================================
typedef struct {
    char name[50];      // 학생 이름
    int grade;          // 학년 (1~4)
    int hp;             // 현재 체력
    int maxHp;          // 최대 체력
    int hintCount;      // 남은 힌트 개수
} Player;



//  교수님(적) 구조체
// ================================
typedef struct Professor{
    char name[50];      // 교수님 이름    
    int hp;             // 현재 체력
    int maxHp;          // 최대 체력
}; 



//  퀴즈(문제) 구조체
// ================================
// asset/quiz Lv1.txt 등에서 문제를 불러와 저장
typedef struct Quiz {
    char question[256]; // 문제 내용
    char answer[50];    // 정답
    char hint[100];     // 힌트 문구 (있을 경우)
    int used;         // 풀었는지 여부( 미사용 : 0, 사용 : 1)
    int difficulty;   // 난이도(학년) 추가
    struct Quiz *next;
} *pre, *cur, *newquiz, *first;



//  아이템 구조체 (확률 드롭용)
// ================================
typedef struct {
    char name[50];      // 아이템 이름
    char description[100]; // 아이템 설명
    int effectType;     // 1: HP 회복, 2: 힌트 추가, 3: 공격력 증가 등
    int effectValue;    // 효과 수치
} Item;



//  전투 상태 구조체
// ================================

// 현재 전투의 모든 정보를 관리
typedef struct {
    Player student;       // 플레이어 정보
    Professor professor;  // 교수님 정보
    Quiz* quizList;       // 퀴즈 배열 (파일에서 로드됨)
    int quizCount;        // 퀴즈 총 개수
    int currentQuiz;      // 현재 진행 중인 문제 인덱스
} BattleState;

#endif
