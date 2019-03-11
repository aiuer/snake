#include<stdio.h>
#include<conio.h>
#include<windows.h>
#include<time.h> 
#include<stdlib.h>
#pragma comment(lib,"User32.lib")
#include <mmsystem.h> 
#pragma comment(lib, "winmm.lib")  //头文件 

#define ESC 0x011b
#define RIGHT 0x4d00
#define LEFT 0x4b00
#define DOWN 0x5000
#define UP 0x4800
#define U 1
#define D 2
#define L 3 
#define R 4//蛇的状态，U：上 ；D：下；L:左 R：右

void Back();//设置背景
void creatMap_1();//封面位置和模式1,2,3的围墙
void creatMap_2();//模式4的围墙及障碍
void Hello();//封面设计
void Modech();//模式选择
void Mode_1();//模式1
void Mode_2();//模式2
void Mode_3();//模式3
void Mode_4();//模式4
void Pos(int x, int y);//设置光标位置
void initsnake();//蛇的初始化
void CreateFood();//食物的随机显示
void Dir_124();//模式1,2,4的移动方向键盘输入控制
void Dir_3();//模式3的蛇的移动方向键盘输入控制
void Play();//游戏过程中
void move();//蛇的移动
int Biteitself();//判断是否咬到自己
void Eat();//吃食物
void Isdead();//模式1,2,3死亡判断
void Isdead_4();//模式4死亡判断
void Bye();//结束界面
void hidden();//隐藏光标
void pause();//暂停

typedef struct SNAKE//构造蛇的结构体
{
	int x;//保存蛇身每一节位于屏幕上的行坐标
	int y;//保存蛇身每一节位于屏幕上的列坐标
	struct SNAKE *next;
}snake;

int status;//status:蛇正在运动的方向,f为食物是否存在
snake *head,*q,*food;//head蛇头指针,q遍历蛇的时候用到的指针,food指针
int score=0,rank,t;//得分,模式,随机时间

int main()//主函数 
{
	Back();
	Hello();
	Modech();
	return 0;
}

void Back()//设置背景（颜色）
{
	system("color 4F");
}

void creatMap_1()//创建封面以及模式1,2,3的围墙
{
	int i;
	for(i=0;i<80;i+=2)
	{
		Pos(i,0);
		printf("※");
		Pos(i,26);
		printf("※");
	}//打印上下边框
	for(i=0;i<26;i++)
	{
		Pos(0,i);
		printf("※");
		Pos(78,i);
		printf("※");
	}//打印左右边框
}

void creatMap_2()//创建模式4的围墙及障碍
{
	int i;
	for(i=0;i<80;i+=2)
	{
		Pos(i,0);
		printf("●");
		Pos(i,26);
		printf("●");
	}//打印上下边框
	for(i=0;i<26;i++)
	{
		Pos(0,i);
		printf("●");
		Pos(78,i);
		printf("●");
	}//打印左右边框
	for(i=2;i<20;i+=2)//打印内部墙
	{
		Pos(i,18);
		printf("●");
	}
	for(i=54;i<77;i+=2)
	{
		Pos(i,8);
		printf("●");
	}
	for(i=1;i<11;i++)
	{
		Pos(20,i);
		printf("●");
	}
	for(i=17;i<26;i++)
	{
		Pos(43,i);
		printf("●");
	}
}

void Hello()
{
	creatMap_1();//创建封面围墙
	system("title 4班5组贪吃蛇小游戏");
	Pos(23,5);
	printf("欢迎来到贪吃蛇游戏世界(≧▽≦)\n");
	Pos(22,19);
	printf("使用↑，↓，←，→控制蛇的前进方向");
	Pos(25,9);
	printf("请输入：\n");
	Pos(33,11);
	printf("1:（普通模式）\n");
	Pos(33,12);
	printf("2:（极速模式）\n");
	Pos(33,13);
	printf("3:（自由模式）\n");
	Pos(33,14);
	printf("4:（迷宫模式）\n");
	Pos(24,15);
	printf("选择游戏模式，并按回车键进入游戏：\n");
	Pos(58,15);
	scanf_s("%d",&rank);//输入选择的关卡
	system("pause");
	system("cls");  //清屏
}            

void Pos(int x,int y)//设置光标位置
{
    COORD pos;
    HANDLE hOutput;
    pos.X=x;
    pos.Y=y;
    hOutput=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hOutput,pos);
}

void Modech()//模式选择
{
	switch(rank)
	{
	   case 1:Mode_1();
	   case 2:Mode_2();
	   case 3:Mode_3();
	   case 4:Mode_4();
	}
}

void Mode_1()//模式1：普通模式
{
	creatMap_1();//普通模式游戏封面
	//PlaySound(TEXT("普通.wav"),NULL,SND_LOOP|SND_ASYNC);//音乐播放
	t=200;//初始间隔时间为200
	Play();
}

void Mode_2()//模式2：极速模式
{
	creatMap_1();//极速模式游戏封面
	//PlaySound(TEXT("极速.wav"),NULL,SND_LOOP|SND_ASYNC);//音乐播放
	t=160;//初始间隔时间为100
	Play();
}
 
void Mode_3()//模式3：自由模式
{
	creatMap_1();//自由模式游戏封面
	//PlaySound(TEXT("自由.wav"),NULL,SND_LOOP|SND_ASYNC);//音乐播放
	t=200;//初始间隔时间为200
	Play();
}
 
void Mode_4()//模式4：迷宫模式
{
	creatMap_2();//迷宫模式游戏封面
	//PlaySound(TEXT("迷宫.wav"),NULL,SND_LOOP|SND_ASYNC);//音乐播放
	t=200;//初始间隔时间为200
	Play();
}

void Play()//开始游戏
{
	CreateFood();
	initsnake();
	hidden();
	Pos(90,10);
 	printf("得分：%d ",score);
	status = R;	//初始状态 
	while (1) 
	{
		if(rank==4)//判断死亡
		{
			Isdead_4();
		}
		else
		{
			Isdead();
		}
		if(rank==1||rank==2||rank==4)//方向改变
		{
			Dir_124();
		}
		else
		{
	        Dir_3();
		}
		Sleep(t);//产生时间间隔
		move();//移动
		hidden();//隐藏光标
	}
} 

void initsnake()//初始化蛇身
{
	int a, b;//随机横纵坐标
    snake *tail;
	int i;
	tail = (snake *)malloc(sizeof(snake));
	if (NULL == tail) 
	{ 
        printf("申请空间内存失败！");
		tail = (snake *)malloc(sizeof(snake));
     } 
	srand((unsigned) time(NULL));
	a = rand() %74 + 2;//随机产生一个横坐标
	b = rand() % 21+ 2;//随机产生一个横坐标

	for(i=2;i<20;i++)
	{
		if((a==i&&b==17)||(a==i&&b==18)||(a==i&&b==19))
		{
			Bye();
		}
	}
	for(i=54;i<78;i++)
	{
		if((a==i&&b==8)||(a==i&&b==7)||(a==i&&b==9))
		{
			Bye();
		}
	}
	for(i=1;i<11;i++)
	{
		if((a==19&&b==i)||(a==20&&b==i)||(a==21&&b==i)||(a==22&&b==i))
		{
			Bye();
		}
	}
	for(i=16;i<26;i++)
	{
		if((a==42&&b==i)||(a==43&&b==i)||(a==44&&b==i)||(a==45&&b==i))
		{
			Bye();
		}
	}

	tail->x = a;
	tail->y = b;
	tail->next = NULL;//从蛇尾开始，头插法，以x,y设定开始的位置//
	for (i = 1; i <= 4; i++)
	{
		head = (snake*)malloc(sizeof(snake));
		head->next = tail;
		head->x = a + 1*i;
		head->y = b;
		tail = head;
	}
	while (tail != NULL)//从头到尾，输出蛇身
	{
		Pos(tail->x, tail->y);
		printf("@");
		tail = tail->next;
	}
}

void CreateFood()
{
	int i;
	srand((unsigned)time(NULL));
	food = (snake*)malloc(sizeof(snake));
	if (NULL == food) 
	{ 
        printf("申请空间内存失败！");
		food = (snake *)malloc(sizeof(snake));
     } 
	food->x = rand() % 76 + 2;
	food->y = rand() % 25 + 1;
	for(i=2;i<20;i++)
	{
		if((food->x==i&&food->y==17)||(food->x==i&&food->y==18)||(food->x==i&&food->y==19))
		{
			CreateFood();
		}
	}
	for(i=54;i<78;i++)
	{
		if((food->x==i&&food->y==8)||(food->x==i&&food->y==7)||(food->x==i&&food->y==9))
		{
			CreateFood();
		}
	}
	for(i=1;i<11;i++)
	{
		if((food->x==19&&food->y==i)||(food->x==20&&food->y==i)||(food->x==21&&food->y==i)||(food->x==22&&food->y==i))
		{
			CreateFood();
		}
	}
	for(i=16;i<26;i++)
	{
		if((food->x==42&&food->y==i)||(food->x==43&&food->y==i)||(food->x==44&&food->y==i)||(food->x==45&&food->y==i))
		{
			CreateFood();
		}
	}
	if (food->x>0 && food->y>0 && food->x<80 && food->y<26)
	{
		Pos(food->x, food->y);
		printf("*");
	}
}

void Dir_124()//模式1,2,4键盘控制
{
	if(GetAsyncKeyState(VK_UP) && status!=D)
	{
		status=U;
	}//输入向上方向时
	else if(GetAsyncKeyState(VK_DOWN) && status!=U)
	{
		status=D;
	}//输入向下方向时
	else if(GetAsyncKeyState(VK_LEFT)&& status!=R)
	{
		status=L;
	}//输入向左方向时
	else if(GetAsyncKeyState(VK_RIGHT)&& status!=L)
	{
		status=R;
	}//输入向右方向时
	else if(GetAsyncKeyState(VK_SPACE))
	{
		pause();
	}
}

void Dir_3()//模式3键盘控制
{
	if(GetAsyncKeyState(VK_UP) && status!=D)
	{
		status=U;
	}//输入向上方向时
	else if(GetAsyncKeyState(VK_DOWN) && status!=U)
	{
		status=D;
	}//输入向下方向时
	else if(GetAsyncKeyState(VK_LEFT)&& status!=R)
	{
		status=L;
	}//输入向左方向时
	else if(GetAsyncKeyState(VK_RIGHT)&& status!=L)
	{
		status=R;
	}//输入向右方向时
	else if(GetAsyncKeyState(VK_F1))
	{
		if(t>50)
		{
			t-=50;
		}
	 } //点击 F1 键加速
	 else if(GetAsyncKeyState(VK_F2))
	{
		if(t>50&&t<1000)
		{
			t+=50;
		}
	 } //点击 F2 键减速
	else if(GetAsyncKeyState(VK_SPACE))
	{
		pause();
	}

}

void  move() //蛇的移动 
{
	snake *p;
	p = (snake*)malloc(sizeof(snake));
	if (NULL == p) 
	{ 
        printf("申请空间内存失败！");
		p = (snake *)malloc(sizeof(snake));
     } 
	if (status == U)        //蛇向上时 
	{
		p->x = head->x;
		p->y = head->y - 1;
		if (p->x == food->x && p->y == food->y)//如果下一个有食物
		{
			food->next = head;
			head = food;
			Eat();
			CreateFood();
		}
		else            //如果下一个不是食物
		{
			p->next = head;
			head = p;
			q = head;
			while (q->next->next != NULL)
			{
				Pos(q->x, q->y);
				printf("@");
				q = q->next;
			}
			Pos(q->next->x, q->next->y);
			printf(" ");
			free(q->next);
			q->next = NULL;
		}
	}
	if (status == D)       //蛇向下时 
	{
		p->x = head->x;
		p->y = head->y + 1;
		if (p->x == food->x && p->y == food->y)//如果下一个有食物
		{
			food->next = head;
			head = food;
			Eat();
			CreateFood();
		}
		else//如果下一个没有食物
		{
			p->next = head;
			head = p;
			q = head;
			while (q->next->next != NULL)
			{
				Pos(q->x, q->y);
				printf("@");
				q = q->next;
			}
			Pos(q->next->x, q->next->y);
			printf(" ");
			free(q->next);
			q->next = NULL;
		}
	}
	if (status == L)         //蛇向左时 
	{
		p->x = head->x - 1;
		p->y = head->y;
		if (p->x == food->x && p->y == food->y)//如果下一个有食物
		{
			food->next = head;
			head = food;
			Eat();
			CreateFood();
		}
		else//如果下一个没有食物
		{
			p->next = head;
			head = p;
			q = head;
			while (q->next->next != NULL)
			{
				Pos(q->x, q->y);
				printf("@");
				q = q->next;
			}
			Pos(q->next->x, q->next->y);
			printf(" ");
			free(q->next);
			q->next = NULL;
		}
	}
	if (status == R)          //蛇向右时 
	{
		p->x = head->x + 1;
		p->y = head->y;
		if (p->x == food->x && p->y == food->y)//如果有食物
		{
			food->next = head;
			head = food;
			Eat();
			CreateFood();
		}
		else//如果没有食物
		{
			p->next = head;
			head = p;
			q = head;
			while (q->next->next != NULL)
			{
				Pos(q->x, q->y);
				printf("@");
				q = q->next;
			}
			Pos(q->next->x, q->next->y);
			printf(" ");
			free(q->next);
			q->next = NULL;
		}
	}
}

void Bye() //结束界面
{
	char ch;
	system("cls");
	creatMap_1();
	system("title 游戏结束");
	Pos(18,7);
	printf("哦豁，你死了(╥_╥)\n");
	Pos(18,11);
	printf("你的分数是：%d\n",score);
	Pos(15,17);
	printf("按ENTER键重新开始游戏，按ESC退出游戏"); 
	getchar();
	//while(!GetAsyncKeyState(VK_ESCAPE))
	//{
	//	score=0;
	//	system("cls");
	//	Back();
	//	Hello();
	//	Modech();
	//}
	while (1) 
	{
		ch = _getch();
		if (ch == 13)
		{
			exit(1);
		}
		else if(ch != 13 && ch != 27) 
		{
			score = 0;
			system("cls");
			hidden();
			Back();
			Hello();
			Modech();
			Bye();
		}
	}
}    

void Isdead_4()//模式四判断死亡
{
	int i;
	if(head->x==0 || head->x==80 ||head->y==0 || head->y==27||Biteitself())//判断是否撞外边框和自己
	{
       Bye();
	}
	for(i=2;i<20;i++)
	{
		if((head->x==i&&head->y==17)||(head->x==i&&head->y==18)||(head->x==i&&head->y==19))
		{
			Bye();
		}
	}
	for(i=54;i<78;i++)
	{
		if((head->x==i&&head->y==8)||(head->x==i&&head->y==7)||(head->x==i&&head->y==9))
		{
			Bye();
		}
	}
	for(i=1;i<11;i++)
	{
		if((head->x==19&&head->y==i)||(head->x==20&&head->y==i)||(head->x==21&&head->y==i)||(head->x==22&&head->y==i))
		{
			Bye();
		}
	}
	for(i=16;i<26;i++)
	{
		if((head->x==42&&head->y==i)||(head->x==43&&head->y==i)||(head->x==44&&head->y==i)||(head->x==45&&head->y==i))
		{
			Bye();
		}
	}

}

void Isdead()//模式1.2.3判断死亡
{
	if(head->x==1 || head->x==78 ||head->y==0 || head->y==26||Biteitself())//判断是否撞外边框和自己
	{
        Bye();
	}
}

int Biteitself()//判断是否咬到自己
{
	snake *self;
	self=head->next;
	while(self!=NULL)
	{
		if(head->x==self->x && head->y==self->y)
			{
				return 1;
		    }
		self=self->next;
	}
	return 0;
}

void Eat()//吃食物
{
	q = head;
	while (q != NULL)
	{
		Pos(q->x, q->y);
		printf("@");
		q = q->next;
	}
	score+=10;
	if(rank==2)
	{
		t-=10;
	}
	else
	{
		t-=0;
	}
	Pos(90,10);
 	printf("得分：%d ",score);
}

void hidden()//隐藏光标
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cci;
	GetConsoleCursorInfo(hOut,&cci);
	cci.bVisible=0;//赋值1为显示，0是隐藏
	SetConsoleCursorInfo(hOut,&cci);
}

void pause()//暂停
{
	while(1)
	{
		Sleep(300);
		if(GetAsyncKeyState(VK_SPACE))
		{
			break;
		}
	}
}







