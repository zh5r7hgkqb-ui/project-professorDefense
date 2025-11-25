#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h> 

#pragma execution_character_set("utf-8")

void startUpDownGameFixed();

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    // 난수 생성을 위해 시간을 시드로 사용
    srand(time(NULL)); 
    startUpDownGameFixed();

    printf("\n\n결과 확인 후 아무 키나 눌러 종료하세요...");
    _getch(); // 키 입력을 기다림 (버퍼를 무시하고 즉시 키를 받음)

    return 0;
}

void startUpDownGameFixed() {
    
    const int MAX_NUMBER = 100; 
    const int MAX_ATTEMPTS = 8; 
    
    int secretNumber; 
    int guess; 
    int attempts = 0; 

    printf("======================================\n");
    printf("⬆️⬇️ UP & DOWN 숫자 맞추기 게임 \n");
    printf("======================================\n");

    // 1부터 MAX_NUMBER 사이의 비밀 숫자 생성
    secretNumber = (rand() % MAX_NUMBER) + 1;
    
    printf("\n💡 1부터 %d까지의 숫자 중 하나를 맞혀보세요. 시도 횟수: %d회\n", MAX_NUMBER, MAX_ATTEMPTS);

    while (attempts < MAX_ATTEMPTS) {
        printf("\n[%d/%d] 숫자를 입력하세요: ", attempts + 1, MAX_ATTEMPTS);
        
        if (scanf("%d", &guess) != 1) {
            printf("⚠️ 잘못된 입력입니다. 숫자를 입력해주세요.\n");
            // 입력 버퍼를 비워 무한 루프에 빠지는 것을 방지
            while (getchar() != '\n');
            continue;
        }

        // scanf 직후에 남아있는 개행 문자(\n)를 소비하여 다음 반복에서 입력을 막는 것을 방지
        while (getchar() != '\n'); 

        attempts++; 

        if (guess == secretNumber) {
            printf("\n🎉 성공! **%d**를 %d번 만에 맞혔습니다!\n", secretNumber, attempts);
            return; 
        } 
        
        else if (guess < 1 || guess > MAX_NUMBER) {
             printf("🚫 범위 (1~%d)를 벗어난 숫자입니다. 다시 입력해주세요.\n", MAX_NUMBER);
             attempts--; // 범위 오류는 시도 횟수에서 제외
        }
        else if (guess < secretNumber) {
            printf("⬆️ UP! 비밀 숫자는 더 큽니다.\n");
        } 
        else { 
            printf("⬇️ DOWN! 비밀 숫자는 더 작습니다.\n");
        }
        
        if (attempts < MAX_ATTEMPTS) {
            printf("남은 시도 횟수: %d회\n", MAX_ATTEMPTS - attempts);
        }
    }

    printf("\n❌ 실패! 모든 시도 횟수 (%d회)를 소진했습니다.\n", MAX_ATTEMPTS);
    printf("정답은 **%d**였습니다.\n", secretNumber);
    printf("======================================\n");
}
