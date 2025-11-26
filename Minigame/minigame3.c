#include "MiniGame.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 5
#define MINES 3

int board[SIZE][SIZE];        // 실제 지뢰판 (-1 = mine, 0~8 = 주변 지뢰 수)
int opened[SIZE][SIZE];       // 플레이어가 연 칸 (0=닫힘, 1=열림)

void initBoard();
void placeMines();
void calculateNumbers();
int countMines(int r, int c);
void printBoard();
int openCell(int r, int c);
int checkWin();

int minigame_minesweeper() {
    int r, c;
    int gameOver = 0;

    srand(time(NULL));
    initBoard();
    placeMines();
    calculateNumbers();

    printf("-----지뢰찾기 미니게임-----\n");

    while (!gameOver) {
        printBoard();
        printf("열 좌표 입력 (행 열): ");
        scanf("%d %d", &r, &c);

        if (r < 0 || r >= SIZE || c < 0 || c >= SIZE) {
            printf("잘못된 좌표입니다!\n");
            continue;
        }

        if (!openCell(r, c)) {  
            printf("\n 지뢰를 밟았습니다!(Game Over)\n");
            gameOver = 1;
            break;
        }

        if (checkWin()) {
            printf("\n 모든 칸을 열었습니다!(Win!)\n");
            break;
        }
    }

    // 최종 지뢰판 공개
    printf("\n=== 실제 지뢰판 ===\n");
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == -1)
                printf(" * ");
            else
                printf(" %d ", board[i][j]);
        }
        printf("\n");
    }

    return 0;
}

void initBoard() {
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            board[i][j] = opened[i][j] = 0;
}

void placeMines() {
    int count = 0;
    while (count < MINES) {
        int r = rand() % SIZE;
        int c = rand() % SIZE;

        if (board[r][c] != -1) {
            board[r][c] = -1;
            count++;
        }
    }
}

void calculateNumbers() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == -1) continue;
            board[i][j] = countMines(i, j);
        }
    }
}

int countMines(int r, int c) {
    int cnt = 0;
    for (int dr = -1; dr <= 1; dr++) {
        for (int dc = -1; dc <= 1; dc++) {
            int nr = r + dr;
            int nc = c + dc;
            if (nr >= 0 && nr < SIZE && nc >= 0 && nc < SIZE) {
                if (board[nr][nc] == -1)
                    cnt++;
            }
        }
    }
    return cnt;
}

void printBoard() {
    printf("\n   ");
    for (int i = 0; i < SIZE; i++)
        printf(" %d ", i);
    printf("\n");

    for (int i = 0; i < SIZE; i++) {
        printf("%d: ", i);
        for (int j = 0; j < SIZE; j++) {
            if (opened[i][j])
                printf(" %d ", board[i][j]);
            else
                printf(" # ");
        }
        printf("\n");
    }
    printf("\n");
}

int openCell(int r, int c) {
    if (opened[r][c]) return 1; // 이미 열림

    opened[r][c] = 1;

    if (board[r][c] == -1)  
        return 0;   // 지뢰 → 게임오버

    return 1;
}

int checkWin() {
    int safeCells = SIZE * SIZE - MINES;
    int openedCount = 0;

    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            if (opened[i][j] && board[i][j] != -1)
                openedCount++;

    return openedCount == safeCells;
}
