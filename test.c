#include "snake.h"
//���ļ�ֻ��һ�����ã�ִ�������򣬲�������������Դ�ļ�����ĺ���


int main(void)//c����Ҫ���������void����ʾû�в�����c++���üӡ����������Ƶ�Ƭ��������ν
{
	
	//I.���ÿ���̨���
	system("mode con cols=100 lines=30");
	//������Ϸ��ʱ���������ʳ����ҪRand����������������randǰ�����������
	srand(time(NULL));
	
	//����һ�������û���ļ������Զ�����һ��save.txt
	FILE *seekFile = NULL;
	int tmp = 0;
	seekFile = fopen("save.txt", "r");
	if (seekFile == NULL)
	{
		seekFile = fopen("save.txt", "w");
		fprintf(seekFile, "%d", tmp);
	}
	fclose(seekFile);

	//II.ѭ�������û���ѡ��
	int choice = 0;
	while (1)
	{
		//1.��ʾ��ӭ����
		choice = welcomeGame();

		switch (choice)
		{
		case 1:
			//���Ƶ�ͼ
			printMap();

			//��ʾ��������ʾ
			showScoreTips(); 	//������һ����ȡ��ʷ��¼����Ƕ��չʾ��������������
			
			//��ʼ����
			initSnake();

			//�������ʳ��
			randFood();

			//ͨ������������ߵ��˶�
			moveKeyControl();//����ʱ���Ը���������

			//������һֱִ��moveKeyControl��������Ķ�ȡ����״̬�Ĵ���
			//����û�����Esc,�ͻ����moveKeyControl���Ӷ�������������
			//
			break;

		case 2:
			aboutGame();
			break;
			//��ʾ�����س���������Ӧ�����������´�һ�����˵���
			//���û��������������Ϊһ��ʼûд�ߵĴ��룡�ߵĴ����һ�����������

		case 3:
			exit(0); //c�����Դ�����
			//��ʾ��ctrl+f5���Ե�ʱ�������˱�������Ϊ�˷�������飬�����press any key to continue����ʾ��
			//��ʵ�ϣ��������Exe�ļ���ִ�е�ʱ������������������ʾ�����Է���д��
			//ʵ�ڲ����ģ���ֱ�ӱ������f5����
			break;

		default:
			setColor(12);
			gotoXY(45, 28);
			printf("�������룬�밴�»س�������");
			//getchar();
		
		}//ע�������break���ǽ�������ѭ��while�����ǽ�����ǰ��case�����¼������˵���
		//ʵ������getchar�����½�������ѭ��

		//2.���س�������
		getchar();

	}

	//printf("\n");
	system("pause");

	return 0;
}
