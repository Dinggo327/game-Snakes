#define  _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>

// 定义游戏区域大小
#define WIDTH 20
#define HEIGHT 20

// 定义蛇的最大长度
#define MAX_LENGTH WIDTH*HEIGHT

// 定义蛇的方向
enum Direction { UP, DOWN, LEFT, RIGHT };

// 定义蛇的结构体
struct Snake {
    int x, y;
};

int main() {
    struct Snake snake[MAX_LENGTH];
    int length = 1;
    int fruitX, fruitY;
    int score = 0;
    enum Direction dir = RIGHT;

    // 初始化蛇的位置
    snake[0].x = WIDTH / 2;
    snake[0].y = HEIGHT / 2;

    // 随机生成果实位置
    fruitX = rand() % WIDTH;
    fruitY = rand() % HEIGHT;

    while (1) {
        // 清空屏幕
        system("cls");

        // 绘制游戏区域
        for (int i = 0; i < WIDTH + 2; i++)
            printf("#");
        printf("\n");

        for (int i = 0; i < HEIGHT; i++) {
            for (int j = 0; j < WIDTH; j++) {
                if (j == 0)
                    printf("#");
                if (i == snake[0].y && j == snake[0].x)
                    printf("O");  // 蛇头
                else if (i == fruitY && j == fruitX)
                    printf("F");  // 果实
                else {
                    int isTail = 0;
                    for (int k = 1; k < length; k++) {
                        if (i == snake[k].y && j == snake[k].x) {
                            printf("o");  // 蛇身
                            isTail = 1;
                            break;
                        }
                    }
                    if (!isTail)
                        printf(" ");
                }
                if (j == WIDTH - 1)
                    printf("#");
            }
            printf("\n");
        }

        for (int i = 0; i < WIDTH + 2; i++)
            printf("#");
        printf("\n");

        // 控制蛇移动
        if (_kbhit()) {
            switch (_getch()) {
            case 'w':
                dir = UP;
                break;
            case 's':
                dir = DOWN;
                break;
            case 'a':
                dir = LEFT;
                break;
            case 'd':
                dir = RIGHT;
                break;
            case 'x':
                return 0;
            }
        }

        // 更新蛇的位置
        int prevX = snake[0].x;
        int prevY = snake[0].y;
        int prev2X, prev2Y;
        snake[0].x += (dir == RIGHT) ? 1 : (dir == LEFT) ? -1 : 0;
        snake[0].y += (dir == DOWN) ? 1 : (dir == UP) ? -1 : 0;

        // 检查蛇是否吃到果实
        if (snake[0].x == fruitX && snake[0].y == fruitY) {
            // 生成新的果实位置
            score++;
            length++;

            // 生成新的果实位置
            fruitX = rand() % WIDTH;
            fruitY = rand() % HEIGHT;
        }

        // 更新蛇身体的位置
        for (int i = 1; i < length; i++) {
            prev2X = snake[i].x;
            prev2Y = snake[i].y;
            snake[i].x = prevX;
            snake[i].y = prevY;
            prevX = prev2X;
            prevY = prev2Y;
        }

        // 检查蛇是否撞墙或撞到自己的身体
        if (snake[0].x >= WIDTH || snake[0].x < 0 || snake[0].y >= HEIGHT || snake[0].y < 0) {
            printf("\n游戏结束！得分：%d\n", score);
            break;
        }

        for (int i = 1; i < length; i++) {
            if (snake[0].x == snake[i].x && snake[0].y == snake[i].y) {
                printf("\n游戏结束！得分：%d\n", score);
                break;
            }
        }

        // 控制游戏速度
        Sleep(100);
    }

    return 0;
}
