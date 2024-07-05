//������ɫ�Ⱥ�������װ�����ͷ�ļ�����
//ͷ�ļ���snake.h�����װ�󣬾Ͳ�������snake.c�����ظ�д�� 

#include <stdio.h> //printf
#include <string.h> //strlen, atoi
#include <stdlib.h> //system
#include <Windows.h> //setconsoletextattribute
#include <time.h> //srand

//direction��������
#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4

//����ڵ���������
typedef struct _snake_t {
	//������
	int x;
	int y;
	//ָ����
	struct _snake_t *next;
}snake_t;
//�ܽ᣺��Ȼ��һ�����һ��д���룬������Ҫ�Ѷ������ݵ�д�ں���ǰ�棡����ϰ�ߣ�

//�����ı���ɫ
int setColor(int c);

//���ù��λ�� 
int gotoXY(int x, int y);

//�����ַ���-��
int printSnake(void);

//��ӭ����
int welcomeGame(void);

//��Ϸ��������
int aboutGame(void);

//������Ϸ��ͼ
int printMap(void);

//��ʾ��������ʾ��Ϣ
int showScoreTips(void);

//��ȡ�ļ��е���߷�
int readFile(void);

//��ʼ������
int initSnake(void);

//�������ʳ��
int randFood(void);

//�ƶ�����
int moveSnake(void);

//ͨ�����������ߵ��ƶ�
int moveKeyControl(void);

//�����ߵ��ƶ�
int speedUp(void);

//�����ߵ��ƶ�
int speedDown(void);

//�ж��Ƿ�ײǽ ײ���˷���1 ���򷵻�0
int isHitWall(void);

//�ж��Ƿ�ҧ�����Լ� ҧ���˷���1 ���򷵻�0
int isBitSelf(void);

//��ʾ��Ϸʧ�ܵĽ���
void failGameUI(void);

//������Ϸ
int endGame(void);

//����߷�д���ļ�
int writeFile(int score);

//������
int destroySnake(void);