#include "snake.h"
//主文件只有一个作用：执行主程序，并反复调用其他源文件里面的函数


int main(void)//c语言要在括号里加void，表示没有参数；c++不用加。如果不是设计单片机，无所谓
{
	
	//I.设置控制台宽高
	system("mode con cols=100 lines=30");
	//进入游戏的时候，随机生成食物需要Rand，因此在主程序调用rand前设置随机种子
	srand(time(NULL));
	
	//增加一步：如果没有文件，就自动创建一个save.txt
	FILE *seekFile = NULL;
	int tmp = 0;
	seekFile = fopen("save.txt", "r");
	if (seekFile == NULL)
	{
		seekFile = fopen("save.txt", "w");
		fprintf(seekFile, "%d", tmp);
	}
	fclose(seekFile);

	//II.循环接受用户的选择
	int choice = 0;
	while (1)
	{
		//1.显示欢迎界面
		choice = welcomeGame();

		switch (choice)
		{
		case 1:
			//绘制地图
			printMap();

			//显示分数和提示
			showScoreTips(); 	//隐藏了一步读取历史记录，镶嵌在展示分数的这个函数里。
			
			//初始化蛇
			initSnake();

			//随机生成食物
			randFood();

			//通过方向键控制蛇的运动
			moveKeyControl();//调试时可以改上下左右

			//正常会一直执行moveKeyControl函数里面的读取键盘状态的代码
			//如果用户按下Esc,就会结束moveKeyControl，从而进入下面这行
			//
			break;

		case 2:
			aboutGame();
			break;
			//提示：按回车键后，正常应该清屏并重新打一遍主菜单。
			//如果没有清屏，就是因为一开始没写蛇的代码！蛇的代码第一句就是清屏！

		case 3:
			exit(0); //c语言自带函数
			//提示：ctrl+f5调试的时候，启动了编译器，为了方便逐句检查，会出现press any key to continue的提示。
			//事实上，编译完的Exe文件，执行的时候根本不会出现这行提示，所以放心写！
			//实在不放心，就直接编译或者f5调试
			break;

		default:
			setColor(12);
			gotoXY(45, 28);
			printf("重新输入，请按下回车键继续");
			//getchar();
		
		}//注意里面的break不是结束永续循环while，而是结束当前的case，重新加载主菜单。
		//实质是用getchar，重新进入永续循环

		//2.按回车键继续
		getchar();

	}

	//printf("\n");
	system("pause");

	return 0;
}
