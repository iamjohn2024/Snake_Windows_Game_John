//字体颜色等函数，封装到这个头文件里面
//头文件在snake.h里面封装后，就不用再在snake.c里面重复写了 

#include <stdio.h> //printf
#include <string.h> //strlen, atoi
#include <stdlib.h> //system
#include <Windows.h> //setconsoletextattribute
#include <time.h> //srand

//direction变量引用
#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4

//链表节点类型声明
typedef struct _snake_t {
	//数据域
	int x;
	int y;
	//指针域
	struct _snake_t *next;
}snake_t;
//总结：虽然是一边设计一边写代码，但还是要把定义数据的写在函数前面！养成习惯！

//设置文本颜色
int setColor(int c);

//设置光标位置 
int gotoXY(int x, int y);

//绘制字符画-蛇
int printSnake(void);

//欢迎界面
int welcomeGame(void);

//游戏帮助界面
int aboutGame(void);

//绘制游戏地图
int printMap(void);

//显示分数和提示信息
int showScoreTips(void);

//读取文件中的最高分
int readFile(void);

//初始化蛇身
int initSnake(void);

//随机生成食物
int randFood(void);

//移动蛇身
int moveSnake(void);

//通过按键控制蛇的移动
int moveKeyControl(void);

//加速蛇的移动
int speedUp(void);

//减速蛇的移动
int speedDown(void);

//判断是否撞墙 撞到了返回1 否则返回0
int isHitWall(void);

//判断是否咬到了自己 咬到了返回1 否则返回0
int isBitSelf(void);

//显示游戏失败的界面
void failGameUI(void);

//结束游戏
int endGame(void);

//将最高分写入文件
int writeFile(int score);

//销毁蛇
int destroySnake(void);