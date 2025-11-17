#include "gameutils.h"

// -------------------------------------------
// 📌 퀴즈 파일 불러오기 
// 한개의 파일(문제 앞에 학년을 쓰는것으로 변경함)
// -------------------------------------------
// 파일 형식 예시 (quiz.txt):
// 학년,문제,정답,힌트
// 1,5 + 3 = ?,8,덧셈 문제입니다.
// -------------------------------------------

// 파일 열기
int loadQuizFile(const char *filename, Quiz **quizList, int grade) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        printf("❌ 파일을 열 수 없습니다: %s\n", filename);
        return 0;
    }

    //연결 리스트의 head와 tail 초기화
    Quiz *head = NULL, *tail = NULL; 
    //불러온 문제 개수를 세는 변수
    int count = 0;
    //한줄씩 읽어올 버퍼
    char line[512];

    while (fgets(line, sizeof(line), fp)) {           // 파일에서 문제 한 줄 읽기
        Quiz *newNode = (Quiz *)malloc(sizeof(Quiz)); // 그 문제를 저장할 새 구조체 생성
        if (!newNode) {                               // 메모리 확보 실패시 종료
            printf("❌ 메모리 할당 실패!\n");
            fclose(fp);
            return count;
        }

        int diff;
        // 학년,문제,정답,힌트 순으로 읽기
        if (sscanf(line, "%d,%255[^,],%49[^,],%99[^\n]",
                   &diff, newNode->question, newNode->answer, newNode->hint) == 4) {
            if (diff == grade) {
                newNode->difficulty = diff;
                newNode->used = 0;     // 아직 풀지 않은 문제
                newNode->next = NULL;

                // 연결 리스트에 추가
                if (head == NULL)
                    head = tail = newNode;
                else {
                    tail->next = newNode;
                    tail = newNode;
                }
                count++;
            } else {
                free(newNode); // 학년이 다르면 버림
            }
        } else {
            free(newNode); // 형식이 잘못된 줄 무시
        }
    }

    fclose(fp);
    *quizList = head; // 불러온 리스트를 반환
    printf("✅ %d개의 문제를 불러왔습니다.\n", count);
    return count;
}

// -------------------------------------------
// 📌 퀴즈 메모리 해제
// -------------------------------------------
void freeQuizList(Quiz *quizList) {
    Quiz *temp;
    while (quizList != NULL) {
        temp = quizList;
        quizList = quizList->next;
        free(temp);
    }
}

