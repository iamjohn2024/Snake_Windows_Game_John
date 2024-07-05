//和snake头文件绑定
//头文件声明函数存在性，但具体定义是在c里面完成的。执行是在Test和这里的主程序中。 
//注意：如果从dev c++粘贴代码，有可能提示行尾不一样。一定要选择“否”！
// ‘\r’ 回车，回到当前行的行首，而不会换到下一行，如果接着输出的话，本行以前的内容会被逐一覆盖；
//‘\n’ 换行，换到当前位置的下一行，而不会回到行首；
//这里不像word一样可以看到隐形的符号，所以你都不知道，注释和代码里面的换行，是用什么方式保存到c文件里面的！！

#define _CRT_SECURE_NO_WARNINGS
#include "snake.h" //注意必须用双引号

//设置为全局变量，供主程序调用

//当前得分
int score = 0;

//最高得分
int highScore = 0; 
//这是我和老师不一样的地方
//我在showscoretips和endgame里面调用的都是这个全局变量。前面已经读过一次，所以endgame不需要再读

//吃掉每一份食物的得分
int add = 1;

//蛇的移动方向
int direction = RIGHT;//RIGHT已经被定义为4

//睡眠时间
int sleepTime = 250;

//结束标志
int endStatus = 0;

//链表的头指针
snake_t *head = NULL;

//食物结点指针
snake_t *foodNode = NULL;


//设置字体颜色 
int setColor(int c)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c); //十进制颜色对照表 
	return 0;
}

//设置光标坐标 
int gotoXY(int x, int y)
{
	//建立坐标结构体类型变量
	COORD c; //COORD是windows.h中已经定义好了的结构体，拿来直接用
	c.X = x;//横坐标
	c.Y = y;//纵坐标 
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);

	return 0;
}

//绘制字符串蛇
int printSnake(void)
{
	system("cls");

	gotoXY(35, 1);
	setColor(6);
	printf("/^\\/^\\");

	gotoXY(34, 2);
	printf("|__|  O|");

	gotoXY(33, 2);
	setColor(2);
	printf("_");

	gotoXY(25, 3);
	setColor(12);
	printf("\\/");

	gotoXY(31, 3);
	setColor(2);
	printf("/");

	gotoXY(37, 3);
	setColor(6);
	printf(" \\_/");

	gotoXY(41, 3);
	setColor(10);
	printf(" \\");

	gotoXY(26, 4);
	setColor(12);
	printf("\\____");

	gotoXY(32, 4);
	printf("_________/");

	gotoXY(31, 4);
	setColor(2);
	printf("|");

	gotoXY(43, 4);
	setColor(10);
	printf("\\");

	gotoXY(32, 5);
	setColor(2);
	printf("\\_______");

	gotoXY(44, 5);
	setColor(10);
	printf("\\");

	gotoXY(39, 6);
	printf("|     |                  \\");

	gotoXY(38, 7);
	printf("/      /                   \\");

	gotoXY(37, 8);
	printf("/      /                    \\ \\");

	gotoXY(35, 9);
	printf("/      /                       \\ \\");

	gotoXY(34, 10);
	printf("/     /                          \\  \\");

	gotoXY(33, 11);
	printf("/     /             _----_         \\   \\");

	gotoXY(32, 12);
	printf("/     /           _-~      ~-_         |  |");

	gotoXY(31, 13);
	printf("(      (        _-~    _--_    ~-_     _/  |");

	gotoXY(32, 14);
	printf("\\     ~-____-~    _-~    ~-_    ~-_-~    /");

	gotoXY(33, 15);
	printf("~-_           _-~          ~-_       _-~");

	gotoXY(35, 16);
	printf("~--______-~                ~-___-~");

	return 0;
}

//欢迎界面
int welcomeGame(void)
{

	//1.绘制字符画-蛇
	printSnake();

	//2.输出标题
	setColor(11);//蓝色
	gotoXY(45, 18);
	printf("贪吃蛇游戏\n");

	//3.绘制边框
	setColor(14);//黄色
	//从第20行到第26行
	for (int i = 20; i <= 26; i++)
	{
		//从第27列到第74列
		for (int j = 27; j <= 74; j++)
		{
			//第20行和第26行是上下边界，用-连接
			//特别提示：gotoXY和coord结构体，横纵坐标和数学直觉是一样的，但是在循环的时候要反过来
			//循环体的行是纵坐标，列是横坐标！
			if (i == 20 || i == 26)
			{
				gotoXY(j, i);
				printf("-");
			}
			//对于中间几行，不是所有的j都要输出。只有左右边框用|输出
			else if (j == 27 || j == 74)
			{
				gotoXY(j, i);
				printf("|");
			}
			/*课上这几句不写无所谓。
			else
			{
			printf(" ");
			}
			*/

		}
	}

	//4.输出菜单选项
	//确定文本属性
	setColor(12);
	//顺序：开始游戏，游戏说明，退出游戏
	gotoXY(35, 22);
	printf("1.开始游戏");
	gotoXY(55, 22);
	printf("2.游戏说明");
	gotoXY(35, 24);
	printf("3.退出游戏");

	//5.输出提示信息，提醒交互
	int choice;
	gotoXY(27, 27);
	printf("请选择[1 2 3]：");
	scanf("%d", &choice);
	//注意把换行符本身清掉
	getchar();

	return choice;//如果不把choice返回，就没办法交互了

}


//游戏帮助界面
int aboutGame(void)
{

	//1.清屏
	system("cls");

	//2.输出标题
	setColor(13);
	gotoXY(44, 3);
	printf("游戏说明");

	//3.绘制上下左右边框，方法和欢迎界面一样，经济双循环
	//控制行by纵坐标
	for (int i = 6; i <= 22; i++)
	{
		//控制列by横坐标
		for (int j = 20; j <= 75; j++)
		{
			if (i == 6 || i == 22)
			{
				//提示：如果不选坐标，默认是在原来的字符串后面加，所以你看到的是两排连在一起的===，而不是我们要的方框
				gotoXY(j, i);
				printf("=");
			}
			else if (j == 20 || j == 75)
			{
				gotoXY(j, i);
				printf("|");
			}
			//else也可以象征性地留着，但是要注意不能打括号，否则无法编译	
		}

	}

	//4.输出菜单选项
	//真的，不加注释你会疯掉的……
	setColor(3);
	gotoXY(30, 8);
	printf("★ 1. 不能撞到墙，不能咬到自己");

	setColor(5);
	gotoXY(30, 11);
	printf("★ 2. F8加速前进，F9减速前进");

	setColor(11);
	gotoXY(30, 14);
	printf("★ 3. 使用空格暂停游戏或者继续游戏");

	setColor(13);
	gotoXY(30, 17);
	printf("★ 4. 使用方向键控制前进的方向");

	setColor(14);
	gotoXY(30, 20);
	printf("★ 5. 按下ESC键退出游戏");

	//5.输出提示信息
	setColor(12);
	gotoXY(20, 24);
	printf("按回车键返回主菜单");

	return 0;
}


//绘制游戏地图
int printMap(void)
{
	//清屏
	system("cls");

	//控制行by纵坐标
	for (int i = 0; i <= 26; i++)
	{
		//控制列by横坐标
		for (int j = 0; j <= 56; j = j + 2)
			//提示：行列宽不一样，所以j+2才正常。
		{
			//简化算法，可以用分配律，先定位光标，再考虑输出。
			gotoXY(j, i);
			if (i == 0 || i == 26 || j == 0 || j == 56)
			{
				setColor(5);//红色
				printf("□");
			}
			else
			{
				setColor(3);//蓝色
				printf("■");
			}
		}
	}

	return 0;
}

//显示分数和提示信息
//在蛇随键盘指令移动的时候，这个函数也会被调用
int showScoreTips(void)
{
	//0.从文件中读取最高分
	highScore = readFile(); //如果没有读取到文件，默认使用return的0.

	//1.显示最高分
	setColor(3);//绿色
	gotoXY(64, 4);
	printf("☆☆最高分记录☆☆：%d", highScore);

	//2.显示当前得分
	setColor(14);//黄色
	gotoXY(64, 8);
	printf("得分：%d", score);

	//3.显示温馨提示
	setColor(12);//红色
	gotoXY(72, 11);
	printf("温 馨 提 示");

	//4.绘制上下边框
	setColor(10);
	gotoXY(60, 13);
	printf("==================================");

	gotoXY(60, 25);
	printf("==================================");

	//5.输出提示信息
	setColor(13);//粉红色
	gotoXY(64, 14);
	printf("※ 吃掉每个食物得分：%d分", add);

	gotoXY(64, 16);//当前在第i行，下一排在第i+2行输出
	printf("※ 不能撞到墙壁，不能咬到自己");

	gotoXY(64, 18);
	printf("※ F8加速前进，F9减速前进");

	gotoXY(64, 20);
	printf("※ 使用空格暂停或继续游戏");

	gotoXY(64, 22);
	printf("※ 使用↑↓←→控制前进方向");

	gotoXY(64, 24);
	printf("※ 按下ESC键退出游戏");

	return 0;
}

//读取文件中的最高分，读取的结果return到showscoretips函数里
//最高分保存在save.txt文件中
int readFile(void) 
{
	int ret = -1;
	char buf[32];
	FILE * fp = NULL;

	//1.以只读方式打开文件
	fp = fopen("save.txt", "r"); 
	//关于历史记录位置：放在项目文件夹，和项目debug文件夹同级
	if (fp == NULL)
	{
		printf("文件打开失败...\n");
		return 0;
	}

	//2.读取文件
	memset(buf, 0, sizeof(buf));
	ret = fread(buf, sizeof(char), sizeof(buf), fp);
	if (ret <= 0)
	{
		printf("文件读取失败...\n");
		return 0;
	}

	//3.关闭文件
	fclose(fp);
	
	return atoi(buf); //ascii to integer，将文件中的字符串转换为可以运算的整数
}


int initSnake(void) //不带头结点的非循环单链表
{
	//system("cls");

	snake_t *new = NULL;
	snake_t *tmp = NULL;
	//项目设计：默认的蛇占四个格子，其中头结点坐标是（24,5）,剩下的按头插法新建。

	//1.循环创建四个节点
	/*先解释下链表的逻辑。
	蛇的坐标：24,26 28 30
	链表的x坐标：24 26 28 30
	打印的时候：	从30 28 26 24开始倒序打印
	所以，如果是延长了，就是从32 30开始打印
	坐标最高的就是蛇的头，而且这个就是头结点！
	
	循环下来，四个结点的坐标：
	i=0. x=24, y=5
	i=1. x=26, y=5
	i=2. x=28, y=5
	i=3. x=30, y=5
	head.x:30
	*/
	for (int i = 0; i < 4; i++)
	{
		//1.1创建节点并初始化
		new = (snake_t*)malloc(sizeof(snake_t));
		if (new == NULL)
		{
			printf("malloc initSnake failed...\n");
			return -1;
		}
		memset(new, 0, sizeof(snake_t)); //不管是真的数，还是地址，全部初始化为0。反正cpu和ram都是一次传送处理
		
		//1.2数据域赋值
		//设计的蛇是从24,5位置开始往右延长身体。纵坐标不变，横坐标递增。
		new->x = 24 + i * 2;
		new->y = 5;
		//printf("i=%d. x=%d, y=%d\n", i, new->x, new->y);

		//1.3指针域赋值
		//使用头插法。想不通逻辑的时候，把链表的箭头往左画，把蛇循着横坐标往右画
		new->next = head; //head必须以不受函数影响的全部变量存在
		head = new;
		
	}
	//printf("head.x=%d", head->x);

	//2.遍历链表并绘制图案
	//不要改动链表。通过临时指针找到坐标后画图！这两个是分开的动作
	tmp = head;
	while (tmp != NULL)
	{
		setColor(14); //蛇身颜色设置为黄色
		gotoXY(tmp->x, tmp->y); //定位光标
		
		if (tmp == head)
			printf("●");//头结点是坐标值最大的、最后插进来的
		else
			printf("★");

		tmp = tmp->next;
	}

	return 0;
}

//随机生成食物
int randFood(void)
{
	//三条原则：
	//随机的食物不能出现在墙壁上
	//随机的食物不能出现在蛇身上
	//随机的食物x坐标必须为偶数
	snake_t *tmp = NULL;

	//1.分配空间
	foodNode = (snake_t*)malloc(sizeof(snake_t));
	if (foodNode == NULL)
	{
		gotoXY(1, 28);
		printf("foodNode malloc failed...\n");
		return -1;
	}
	memset(foodNode, 0, sizeof(snake_t));

	while (1)
	{
		//2.确定食物横坐标
		//保证x坐标是偶数，且包含在墙里面
		//墙的横坐标是0和56，所以生成的随机数在2到54之间
		while (1)//因为不知道要生成几次，索性写个死循环
		{
			foodNode->x = rand() % 53 + 2; //[2,54]，百分号后面的参数是：54-2+1=53
			//提示：完整的随机数函数
			//int num = (rand() % (upper - lower + 1)) + lower
			//%包含首尾的数字个数 - 闭区间的下限

			//特别提醒：横坐标步进为2，所以必须判断是不是偶数。纵坐标步进为1，所以不用增加这个步骤
			if (foodNode->x % 2 == 0)
			{
				break;
			}
		}

		//3.同理设置纵坐标
		foodNode->y = rand() % 25 + 1;//[0,26]->[1,25]

		//4.判断食物不能在蛇身上
		//实质就是遍历链表
		tmp = head;
		while (tmp != NULL)
		{
			if ((foodNode->x == tmp->x) && (foodNode->y == tmp->y))
				//如果在身上，就终止循环。对最后一个结点，也是跳出循环，这样就不会往下让tmp变成null
				break;
			tmp = tmp->next;
		}

		//5.食物不在身上，就可以显示
		if (tmp == NULL)
		{
			gotoXY(foodNode->x, foodNode->y);
			setColor(12); //红色
			printf("●");
			break;//显示食物后，跳出最外面的循环，完成整个生成函数
		}
		else
			continue;//重新生成合法的坐标，如果还不行，就无穷继续

	}

	return 0;
}

//移动蛇身，整体在moveKeyControl函数中调用
int moveSnake(void) //食物和蛇头都是全局变量，放心调用
{
	snake_t *new = NULL;//在移动过程中的局部变量，不可改动
	snake_t *tmp = NULL;//类似循环体的i，是个标记位置的临时变量
	snake_t *save = NULL;

	//1.数据结构：链表头插+尾删
	new = (snake_t*)malloc(sizeof(snake_t));
	if (new == NULL)
	{
		printf("malloc moveSnake failed...\n");
		return -1;
	}
	memset(new, 0, sizeof(snake_t));

	//头插法-数据域：根据方向变量，确定新的头结点坐标
	if (direction == UP)//特别提示：如果使用Switch语句，这里只会代入全局变量执行movekeycontrol，所以蛇只会往右移动
	{
		new->x = head->x;
		new->y = head->y - 1;
	}
	if (direction == DOWN)
	{
		new->x = head->x;
		new->y = head->y + 1;
	}
	if (direction == LEFT)
	{
		new->x = head->x - 2;
		new->y = head->y;
	}
	if (direction == RIGHT)
	{
		new->x = head->x + 2;
		new->y = head->y;
	}

	//头插法-指针域
	new->next = head;
	head = new;

	//2.系统：默认可以吃到食物，于是直接延长身体，加分
	tmp = head;
	setColor(14);
	if ((new -> x == foodNode -> x) && (new -> y == foodNode -> y))
	{
		//循环画出蛇身
		while (tmp != NULL)
		{
			gotoXY(tmp->x, tmp->y);
			//分类讨论画图
			if (tmp == head)
				printf("●");
			else
				printf("★");

			tmp = tmp->next;
		}
		//加分
		score = score + add;
		//重新分配食物
		randFood();
	}
	else //没有吃到食物，身体长度不变，链表的尾结点要销毁
	{
		//启动条件：不是尾结点，就打印。尾结点恰好是指向nullspace的
		while (tmp->next != NULL)
		{
			gotoXY(tmp->x, tmp->y);
			if (tmp == head)
				printf("●");
			else
				printf("★");
			save = tmp;
			tmp = tmp->next;
		}
		//释放尾结点
		gotoXY(tmp->x, tmp->y);//定位到多余的第五个结点
		setColor(3);
		printf("■"); //把原来的蛇身图案还原成地图的方块
		save->next = NULL; //save就是尾结点，指向nullspace
		free(tmp);
	}
	
	return 0;
}

//通过按键控制蛇的移动
int moveKeyControl(void)
{
	//下面的代码仅用于调试移动功能，后续已被getasynckeystate替换
	//默认方向向右
	//direction = DOWN;//提示：只有前面的moveSnake启用if语句的时候，这句才生效
	//调试说明：有时候会越界，有时候不会。多调试几次就OK了
	
	while (1)
	{
		//1.显示右侧小提示
		showScoreTips();//必须写，不然无法更新得分

		//2.确定移动方向
		//向上
		if (GetAsyncKeyState(VK_UP) && direction != DOWN) //提示：操作系统可以设置虚拟映射，但async是读取物理键的返回值
		{
			direction = UP;
		}

		//向下
		if (GetAsyncKeyState(VK_DOWN) && direction != UP)
		{
			direction = DOWN;
		}

		//向左
		if (GetAsyncKeyState(VK_LEFT) && direction != RIGHT)//易错提示：这里要是写的上下，左右方向键就无法读取
		{
			direction = LEFT;
		}

		//向右
		if (GetAsyncKeyState(VK_RIGHT) && direction != LEFT)
		{
			direction = RIGHT;
		}
		
		//按空格键暂停或继续游戏
		if (GetAsyncKeyState(VK_SPACE))
		{
			//第一次：直接暂停
			//第二次：继续
			//第三次：重复第一步
			//因此是个无穷循环语句
			while (1)
			{
				Sleep(300);
				if (GetAsyncKeyState(VK_SPACE))
					break;//偶数次，后面没语句了，跳出这个if判断
			}
		}
		
		//F8=加速
		if (GetAsyncKeyState(VK_F8))
		{
			speedUp();
		}//易错提示：不要把这个判断语句写在上一条里面！不然无法更新add!

		//F9=减速
		if (GetAsyncKeyState(VK_F9))
		{
			speedDown();
		}

		//按esc结束游戏
		if (GetAsyncKeyState(VK_ESCAPE)) //易错提示：这里的VK码是完整的escape，不能简写成esc
		{

			//状态标志3：用户按esc结束，弹出结束动画
			endStatus = 3;
			endGame();
			break;//跳出moveKeyControl的永续循环，不再读取键盘状态，也不再重新画蛇
		}

		//3.更新链表，重新画图。
		Sleep(sleepTime);
		moveSnake();

		//4.判断合规性。这个是每次移动都要执行的，所以放入永续循环中
		//判断是否撞墙
		//撞到了，状态码更新为1，退出moveKeyControl的循环，游戏不玩了
		if (isHitWall())//默认都是0，不执行。一旦返回1，必然执行。
		{
			endStatus = 1;
			//failGameUI();
			endGame();
			break;
		}
		//咬到了，状态码更新为2，退出moveKeyControl的循环，游戏不玩了
		if (isBitSelf())//默认都是0，不执行。一旦返回1，必然执行。
		{
			endStatus = 2;
			endGame();
			break;
		}


	}//用户按Esc的时候，从这里break
	//提示：这里的代码和主程序相连，Esc后续操作要一起改掉

	return 0;
}

//加速蛇的移动，整体在moveKeyControl函数中调用
int speedUp(void)
{
	//最短睡眠时间为50ms
	if (sleepTime > 50)
	{
		sleepTime = sleepTime - 20;
		add = add + 2;
	}
	return 0;
}

//减速蛇的移动
int speedDown(void)
{
	//最长睡眠时间为400ms
	if (sleepTime < 400)
	{
		sleepTime = sleepTime + 20;
		add = add - 2;
	}

	//优化：设置add最低值为1
	if (add <= 0)
		add = 1;

	return 0;
}

//判断是否撞墙 
//本函数需要在moveKeyControl移动蛇的时候就调用
int isHitWall(void)
{
	//撞墙的实质，就是碰到了坐标轴。
	//只需要对head数据域的x和y分类讨论，因为指针调用成员代码有点不同。其实这个函数小儿科
	if ((head->x == 0) || (head->x == 56) || (head->y == 0) || (head->y == 26))
		//易错提示：横轴用x，但数的是列数。纵轴用y，但数的是行。行列的辩证统一，自己去翻线性代数基本定理的笔记！
	{
		return 1;
	}
	return 0;//默认没撞墙
}

//判断是否咬到了自己
//同理在moveKeyControl函数中调用本函数
int isBitSelf(void)
{
	//业务逻辑：头咬到身子任何一个结点都要结束游戏
	//数学建模：遍历链表，只要有一个结点的横纵坐标都和头结点完全一样，就算是失败。
	//说白了就是把DSA第一次课的再复习一遍。。
	snake_t *tmp = head -> next;
	
	//数据结构是不带头结点的非循环单链表，所以从第二个结点开始就行
	while (tmp != NULL)
	//易错提示：不要混淆while和if的判断条件！
	//尾结点必须加入判断，所以循环终止条件是进入尾结点之后的空
	{
		if ((tmp->x == head->x) && (tmp->y == head->y))
		//易错提示：函数是用来判错的，所以返回1的条件是=头结点坐标，不能写≠，否则刚开始游戏就结束了
		{
			//system("pause");
			//printf("head->x:%d, head->y:%y,head: %p", head->x, head->y, head);
			//system("cls");
			return 1;//注意这里不用改endstatus...你得在moveKeyControl里面，让人家知道咬到了
		}
		tmp = tmp->next;
	}
	return 0;
}


//显示游戏失败的界面
//调试的时候，撞墙自残选一个就行
//正式运行，需要在endGame函数里调用
void failGameUI(void)
{
	//清屏
	system("cls");

	//GAME OVER!!
	setColor(12); //红色
	gotoXY(46, 3);
	printf("GAME OVER!!!");

	//画边框
	setColor(11); //蓝色
	gotoXY(17, 5);
	printf("+----------------------------------------------------------------+");
	//别想多了，就这么简单粗暴
	gotoXY(17, 20);
	printf("+----------------------------------------------------------------+");
	for (int i = 6; i < 20; i++)
	{
		//只有行，只打印左右两个边界
		gotoXY(17, i);
		printf("|");

		gotoXY(82, i);
		printf("|");
	}
}

//结束游戏
int endGame(void)
{
	int n = 0; //用于最后接收用户的选择

	while (1) //为最后的键盘交互设计永续循环
	{
		//1.显示游戏结束界面
		failGameUI();

		//2.说明结束原因
		setColor(12);
		gotoXY(40, 9);
		switch (endStatus)
		{
			//撞墙
		case 1:
			printf("撞到墙了，游戏结束！！！");
			break;
			//自残
		case 2:
			printf("咬到自己了，游戏结束！！！");
			break;
			//不玩了
		case 3:
			printf("不玩了，游戏结束！！！");
			break;
		default:
			;
		}

		//3.显示游戏分数
		setColor(13);
		gotoXY(45, 12);
		printf("您的得分： %d", score);

		//4.显示最高分
		//注意：课上的最高分并不是全局变量，而是需要读文件读取的。
		//showscoretips已经调用过一次，这里没必要再写
		//highScore = readFile();
		if (score > highScore)
		{
			setColor(10); //绿色
			gotoXY(38, 16);
			printf("恭喜！您已经破纪录啦！");

			//将最高分写入文件
			writeFile(score);
		}
		else
		{
			setColor(10); //绿色
			gotoXY(38, 16);
			printf("加油哦，离历史最高分还差%d分", highScore - score);
		}

		//5.让用户选择收场方式
		gotoXY(25, 23);
		setColor(12); //红色
		printf("再玩一次请输入：1");

		gotoXY(52, 23); //提示：延续前面的颜色，所以不用再写setcolor
		printf("直接退出请输入：2");

		gotoXY(46, 25);
		setColor(11); //蓝色
		printf("请选择：");

		scanf("%d", &n);
		getchar();

		if (n == 1)
		{
			score = 0; //新游戏要重新计数
			sleepTime = 250;//全局变量不会自动还原
			add = 1;
			//如果不销毁原来的链表，两个链表就会共存，新游戏无法真正开始
			destroySnake();
			break;
		}
		else if (n == 2)
		{
			exit(0);
		}
		else
		{
			gotoXY(30, 27);
			setColor(12); //红色
			printf("请输入有效代号，按回车键继续");
			getchar();
		}
	}

	return 0;
}

//将最高分写入文件
//不用担心这里没有判断语句，因为这个函数整体就是在结束游戏的界面调用的
//只有在当前分高于历史最高分的时候，才会调用本函数
int writeFile(int score)
{
	FILE *fp = NULL;
	//1.打开文件
	fp = fopen("save.txt", "w+");
	//w+代表不存在时创建文档，存在时把内容清空，所以后面才能直接fprintf
	if (fp == NULL)
	{
		printf("fopen for writing failed...\n");
		return -1;
	}

	//2.将最高分写入文件
	fprintf(fp, "%d", score);
	//复习计算机组成课知识：
	//printf输出到标准输出设备stdout
	//fprintf输出到流（文件）中

	//3.关闭文件
	fclose(fp);

	return 0;
}

//销毁蛇
//这个是408选择题考过的，很简单
int destroySnake(void)
{
	snake_t *p;
	snake_t *q;

	p = head;

	while (p != NULL)
	{
		q = p->next;
		free(p);
		p = q;
	}
	
	//head在一开始就被释放了
	//这里还要指定为NULL,是为了继续玩游戏的时候，让头指针的next为NULL.
	//全局变量定义只有在刚开始玩游戏的时候才会加载，这里必须手工重置
	head = NULL;

	return 0;
}