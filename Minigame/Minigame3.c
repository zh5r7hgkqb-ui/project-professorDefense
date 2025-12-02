#include "MiniGame.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>


#define SIZE 5
#define MINES 3

// ---------------------------
// 지뢰찾기 게임 구조체
// ---------------------------
typedef struct {
    int board[SIZE][SIZE];  
    int opened[SIZE][SIZE];
} Minesweeper;

// ---------------------------
// 함수 선언 (모듈용)
// ---------------------------
void mines_init(Minesweeper *g);
void mines_placeMines(Minesweeper *g);
void mines_calcNumbers(Minesweeper *g);
int  mines_count(Minesweeper *g, int r, int c);
void mines_print(Minesweeper *g);
int  mines_open(Minesweeper *g, int r, int c);
int  mines_checkWin(Minesweeper *g);

// ---------------------------
// 모듈 형태의 미니게임 엔트리
// ---------------------------
int minigame_minesweeper() {
    Minesweeper g;
    int r, c;
    int gameOver = 0;

    srand(time(NULL));
 
    // ⭐⭐ ASCII 넣는 부분 ⭐⭐
    system("cls");
    printAscii("asset/minesweeper.txt");
    Sleep(1500);
    system("cls");
    // ⭐⭐ 끝 ⭐⭐

    mines_init(&g);
    mines_placeMines(&g);
    mines_calcNumbers(&g);

    printf("----- 지뢰찾기 미니게임 -----\n");

    while (!gameOver) {
        mines_print(&g);
        printf("행 열 입력: ");
        scanf("%d %d", &r, &c);

        if (r < 0 || r >= SIZE || c < 0 || c >= SIZE) {
            printf("잘못된 좌표입니다!\n");
            continue;
        }

        if (!mines_open(&g, r, c)) {
            printf("\n 지뢰를 밟았습니다! (Game Over)\n");
            gameOver = 1;
            return 0;
        }

        if (mines_checkWin(&g)) {
            printf("\n 승리했습니다!(Win!)\n");
            return 1;
        }
    }

    // 정답판 출력
    printf("\n=== 실제 지뢰판 ===\n");
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (g.board[i][j] == -1)
                printf(" * ");
            else
                printf(" %d ", g.board[i][j]);
        }
        printf("\n");
    }

    return 0;
}

// ---------------------------
// 모듈 내부 함수
// ---------------------------
void mines_init(Minesweeper *g) {
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            g->board[i][j] = g->opened[i][j] = 0;
}

void mines_placeMines(Minesweeper *g) {
    int count = 0;
    while (count < MINES) {
        int r = rand() % SIZE;
        int c = rand() % SIZE;
        if (g->board[r][c] != -1) {
            g->board[r][c] = -1;
            count++;
        }
    }
}

void mines_calcNumbers(Minesweeper *g) {
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            if (g->board[i][j] != -1)
                g->board[i][j] = mines_count(g, i, j);
}

int mines_count(Minesweeper *g, int r, int c) {
    int cnt = 0;
    for (int dr = -1; dr <= 1; dr++)
        for (int dc = -1; dc <= 1; dc++) {
            int nr = r + dr;
            int nc = c + dc;
            if (nr >= 0 && nr < SIZE && nc >= 0 && nc < SIZE)
                if (g->board[nr][nc] == -1)
                    cnt++;
        }
    return cnt;
}

void mines_print(Minesweeper *g) {
    printf("\n   ");
    for (int i = 0; i < SIZE; i++)
        printf(" %d ", i);
    printf("\n");

    for (int i = 0; i < SIZE; i++) {
        printf("%d: ", i);
        for (int j = 0; j < SIZE; j++) {
            if (g->opened[i][j])
                printf(" %d ", g->board[i][j]);
            else
                printf(" # ");
        }
        printf("\n");
    }
    printf("\n");
}

int mines_open(Minesweeper *g, int r, int c) {
    if (g->opened[r][c]) return 1;
    g->opened[r][c] = 1;
    if (g->board[r][c] == -1)
        return 0;
    return 1;
}

int mines_checkWin(Minesweeper *g) {
    int safeCells = SIZE * SIZE - MINES;
    int openedCount = 0;

    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            if (g->opened[i][j] && g->board[i][j] != -1)
                openedCount++;

    return openedCount == safeCells;
}
