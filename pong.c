#include <math.h>
#include <stdio.h>

#define WIDTH 80
#define HEIGHT 25

void draw_field(int paddleR, int paddleL, int ballX, int ballY, int scoreR, int scoreL);
int check_balldirY(int ballY, int balldirY);
int check_paddleL(int ballX, int ballY, int balldirX, int paddleL, int paddleR);
int check_goalL(int ballX, int scoreR);
int check_goalR(int ballX, int scoreL);
int mv_ballY(int ballY, int balldirY);
int mv_ballX(int ballX, int balldirX);
int mv_paddleL(char key, int paddleL);
int mv_paddleR(char key, int paddleR);
void clear_field();
char user_key();

int main() {
    int ballX = WIDTH / 2;
    int ballY = HEIGHT / 2;
    int paddleL = HEIGHT / 2;
    int paddleR = HEIGHT / 2;
    int balldirY = 1;
    int balldirX = 1;
    int scoreL = 0;
    int scoreR = 0;

    while (1) {
        if ((ballX == 0) || (ballX == WIDTH - 1)) {
            ballX = WIDTH / 2;
            ballY = HEIGHT / 2;
            paddleL = HEIGHT / 2;
            paddleR = HEIGHT / 2;
        }

        draw_field(paddleR, paddleL, ballX, ballY, scoreR, scoreL);
        if (scoreL == 21 || scoreR == 21) {
            scoreL = 0;
            scoreR = 0;
        }
        char key = user_key();
        while (key != '\n') {
            paddleL = mv_paddleL(key, paddleL);
            paddleR = mv_paddleR(key, paddleR);
            key = user_key();
        }
        paddleL = mv_paddleL(key, paddleL);
        paddleR = mv_paddleR(key, paddleR);
        balldirX = check_paddleL(ballX, ballY, balldirX, paddleL, paddleR);
        balldirY = check_balldirY(ballY, balldirY);
        ballX = mv_ballX(ballX, balldirX);
        ballY = mv_ballY(ballY, balldirY);
        scoreL = check_goalL(ballX, scoreL);
        scoreR = check_goalR(ballX, scoreR);
        clear_field();
    }
}

void draw_field(int paddleR, int paddleL, int ballX, int ballY, int scoreL, int scoreR) {
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            if ((y == 0) || (y == HEIGHT - 1)) {
                printf("-");
            } else if (y == ballY && x == ballX) {
                printf("O");
            } else if ((x == 0) || (x == WIDTH - 1)) {
                printf("|");
            } else if (x == WIDTH / 2 - 1) {
                printf("|");
            } else if ((y == paddleL - 1 || y == paddleL || y == paddleL + 1) && x == 1) {
                printf("#");
            } else if ((y == paddleR - 1 || y == paddleR || y == paddleR + 1) && x == WIDTH - 2) {
                printf("#");
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }
    printf("                                   %d       %d                           \n", scoreL, scoreR);
    if (scoreL == 21) {
        printf("Игра окончена! Левый игрок победил!");
    }
    if (scoreR == 21) {
        printf("Игра окончена! Правый игрок победил!");
    }
}

int check_paddleL(int ballX, int ballY, int balldirX, int paddleL, int paddleR) {
    if (ballX == 2 && (ballY == paddleL || ballY == paddleL - 1 || ballY == paddleL + 1)) {
        balldirX = -balldirX;
    } else if (ballX == WIDTH - 3 && (ballY == paddleR || ballY == paddleR - 1 || ballY == paddleR + 1)) {
        balldirX = -balldirX;
    }
    return balldirX;
}

int check_goalL(int ballX, int scoreR) {
    if (ballX == 1) {
        scoreR += 1;
    }
    return scoreR;
}

int check_goalR(int ballX, int scoreL) {
    if (ballX == WIDTH - 2) {
        scoreL += 1;
    }
    return scoreL;
}

int mv_ballX(int ballX, int balldirX) {
    ballX -= balldirX;
    return ballX;
}

int check_balldirY(int ballY, int balldirY) {
    if (ballY <= 1 || ballY >= HEIGHT - 2) {
        balldirY = -balldirY;
    }
    return balldirY;
}

int mv_ballY(int ballY, int balldirY) {
    ballY += balldirY;
    return ballY;
}

int mv_paddleL(char key, int paddleL) {
    if (key == 'a') {
        if (paddleL - 1 > 1) {
            paddleL -= 1;
        } else {
            return paddleL;
        }
    } else if (key == 'z') {
        if (paddleL + 1 < HEIGHT - 2) {
            paddleL += 1;
        } else {
            return paddleL;
        }
    }
    return paddleL;
}

int mv_paddleR(char key, int paddleR) {
    if (key == 'k') {
        if (paddleR - 1 > 1) {
            paddleR -= 1;
        } else {
            return paddleR;
        }
    } else if (key == 'm') {
        if (paddleR + 1 < HEIGHT - 2) {
            paddleR += 1;
        } else {
            return paddleR;
        }
    }
    return paddleR;
}

void clear_field() { printf("\33[0d\33[2J"); }

char user_key() {
    char key;
    scanf("%c", &key);
    return key;
}
