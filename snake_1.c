#include<stdio.h>
#include<conio.h>
#include<windows.h>
#include<time.h> 
#include<stdlib.h>
#pragma comment(lib,"User32.lib")
#include <mmsystem.h> 
#pragma comment(lib, "winmm.lib")  //ͷ�ļ� 

#define ESC 0x011b
#define RIGHT 0x4d00
#define LEFT 0x4b00
#define DOWN 0x5000
#define UP 0x4800
#define U 1
#define D 2
#define L 3 
#define R 4//�ߵ�״̬��U���� ��D���£�L:�� R����

void Back();//���ñ���
void creatMap_1();//����λ�ú�ģʽ1,2,3��Χǽ
void creatMap_2();//ģʽ4��Χǽ���ϰ�
void Hello();//�������
void Modech();//ģʽѡ��
void Mode_1();//ģʽ1
void Mode_2();//ģʽ2
void Mode_3();//ģʽ3
void Mode_4();//ģʽ4
void Pos(int x, int y);//���ù��λ��
void initsnake();//�ߵĳ�ʼ��
void CreateFood();//ʳ��������ʾ
void Dir_124();//ģʽ1,2,4���ƶ���������������
void Dir_3();//ģʽ3���ߵ��ƶ���������������
void Play();//��Ϸ������
void move();//�ߵ��ƶ�
int Biteitself();//�ж��Ƿ�ҧ���Լ�
void Eat();//��ʳ��
void Isdead();//ģʽ1,2,3�����ж�
void Isdead_4();//ģʽ4�����ж�
void Bye();//��������
void hidden();//���ع��
void pause();//��ͣ

typedef struct SNAKE//�����ߵĽṹ��
{
	int x;//��������ÿһ��λ����Ļ�ϵ�������
	int y;//��������ÿһ��λ����Ļ�ϵ�������
	struct SNAKE *next;
}snake;

int status;//status:�������˶��ķ���,fΪʳ���Ƿ����
snake *head,*q,*food;//head��ͷָ��,q�����ߵ�ʱ���õ���ָ��,foodָ��
int score=0,rank,t;//�÷�,ģʽ,���ʱ��

int main()//������ 
{
	Back();
	Hello();
	Modech();
	return 0;
}

void Back()//���ñ�������ɫ��
{
	system("color 4F");
}

void creatMap_1()//���������Լ�ģʽ1,2,3��Χǽ
{
	int i;
	for(i=0;i<80;i+=2)
	{
		Pos(i,0);
		printf("��");
		Pos(i,26);
		printf("��");
	}//��ӡ���±߿�
	for(i=0;i<26;i++)
	{
		Pos(0,i);
		printf("��");
		Pos(78,i);
		printf("��");
	}//��ӡ���ұ߿�
}

void creatMap_2()//����ģʽ4��Χǽ���ϰ�
{
	int i;
	for(i=0;i<80;i+=2)
	{
		Pos(i,0);
		printf("��");
		Pos(i,26);
		printf("��");
	}//��ӡ���±߿�
	for(i=0;i<26;i++)
	{
		Pos(0,i);
		printf("��");
		Pos(78,i);
		printf("��");
	}//��ӡ���ұ߿�
	for(i=2;i<20;i+=2)//��ӡ�ڲ�ǽ
	{
		Pos(i,18);
		printf("��");
	}
	for(i=54;i<77;i+=2)
	{
		Pos(i,8);
		printf("��");
	}
	for(i=1;i<11;i++)
	{
		Pos(20,i);
		printf("��");
	}
	for(i=17;i<26;i++)
	{
		Pos(43,i);
		printf("��");
	}
}

void Hello()
{
	creatMap_1();//��������Χǽ
	system("title 4��5��̰����С��Ϸ");
	Pos(23,5);
	printf("��ӭ����̰������Ϸ����(�R���Q)\n");
	Pos(22,19);
	printf("ʹ�á������������������ߵ�ǰ������");
	Pos(25,9);
	printf("�����룺\n");
	Pos(33,11);
	printf("1:����ͨģʽ��\n");
	Pos(33,12);
	printf("2:������ģʽ��\n");
	Pos(33,13);
	printf("3:������ģʽ��\n");
	Pos(33,14);
	printf("4:���Թ�ģʽ��\n");
	Pos(24,15);
	printf("ѡ����Ϸģʽ�������س���������Ϸ��\n");
	Pos(58,15);
	scanf_s("%d",&rank);//����ѡ��Ĺؿ�
	system("pause");
	system("cls");  //����
}            

void Pos(int x,int y)//���ù��λ��
{
    COORD pos;
    HANDLE hOutput;
    pos.X=x;
    pos.Y=y;
    hOutput=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hOutput,pos);
}

void Modech()//ģʽѡ��
{
	switch(rank)
	{
	   case 1:Mode_1();
	   case 2:Mode_2();
	   case 3:Mode_3();
	   case 4:Mode_4();
	}
}

void Mode_1()//ģʽ1����ͨģʽ
{
	creatMap_1();//��ͨģʽ��Ϸ����
	//PlaySound(TEXT("��ͨ.wav"),NULL,SND_LOOP|SND_ASYNC);//���ֲ���
	t=200;//��ʼ���ʱ��Ϊ200
	Play();
}

void Mode_2()//ģʽ2������ģʽ
{
	creatMap_1();//����ģʽ��Ϸ����
	//PlaySound(TEXT("����.wav"),NULL,SND_LOOP|SND_ASYNC);//���ֲ���
	t=160;//��ʼ���ʱ��Ϊ100
	Play();
}
 
void Mode_3()//ģʽ3������ģʽ
{
	creatMap_1();//����ģʽ��Ϸ����
	//PlaySound(TEXT("����.wav"),NULL,SND_LOOP|SND_ASYNC);//���ֲ���
	t=200;//��ʼ���ʱ��Ϊ200
	Play();
}
 
void Mode_4()//ģʽ4���Թ�ģʽ
{
	creatMap_2();//�Թ�ģʽ��Ϸ����
	//PlaySound(TEXT("�Թ�.wav"),NULL,SND_LOOP|SND_ASYNC);//���ֲ���
	t=200;//��ʼ���ʱ��Ϊ200
	Play();
}

void Play()//��ʼ��Ϸ
{
	CreateFood();
	initsnake();
	hidden();
	Pos(90,10);
 	printf("�÷֣�%d ",score);
	status = R;	//��ʼ״̬ 
	while (1) 
	{
		if(rank==4)//�ж�����
		{
			Isdead_4();
		}
		else
		{
			Isdead();
		}
		if(rank==1||rank==2||rank==4)//����ı�
		{
			Dir_124();
		}
		else
		{
	        Dir_3();
		}
		Sleep(t);//����ʱ����
		move();//�ƶ�
		hidden();//���ع��
	}
} 

void initsnake()//��ʼ������
{
	int a, b;//�����������
    snake *tail;
	int i;
	tail = (snake *)malloc(sizeof(snake));
	if (NULL == tail) 
	{ 
        printf("����ռ��ڴ�ʧ�ܣ�");
		tail = (snake *)malloc(sizeof(snake));
     } 
	srand((unsigned) time(NULL));
	a = rand() %74 + 2;//�������һ��������
	b = rand() % 21+ 2;//�������һ��������

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
	tail->next = NULL;//����β��ʼ��ͷ�巨����x,y�趨��ʼ��λ��//
	for (i = 1; i <= 4; i++)
	{
		head = (snake*)malloc(sizeof(snake));
		head->next = tail;
		head->x = a + 1*i;
		head->y = b;
		tail = head;
	}
	while (tail != NULL)//��ͷ��β���������
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
        printf("����ռ��ڴ�ʧ�ܣ�");
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

void Dir_124()//ģʽ1,2,4���̿���
{
	if(GetAsyncKeyState(VK_UP) && status!=D)
	{
		status=U;
	}//�������Ϸ���ʱ
	else if(GetAsyncKeyState(VK_DOWN) && status!=U)
	{
		status=D;
	}//�������·���ʱ
	else if(GetAsyncKeyState(VK_LEFT)&& status!=R)
	{
		status=L;
	}//����������ʱ
	else if(GetAsyncKeyState(VK_RIGHT)&& status!=L)
	{
		status=R;
	}//�������ҷ���ʱ
	else if(GetAsyncKeyState(VK_SPACE))
	{
		pause();
	}
}

void Dir_3()//ģʽ3���̿���
{
	if(GetAsyncKeyState(VK_UP) && status!=D)
	{
		status=U;
	}//�������Ϸ���ʱ
	else if(GetAsyncKeyState(VK_DOWN) && status!=U)
	{
		status=D;
	}//�������·���ʱ
	else if(GetAsyncKeyState(VK_LEFT)&& status!=R)
	{
		status=L;
	}//����������ʱ
	else if(GetAsyncKeyState(VK_RIGHT)&& status!=L)
	{
		status=R;
	}//�������ҷ���ʱ
	else if(GetAsyncKeyState(VK_F1))
	{
		if(t>50)
		{
			t-=50;
		}
	 } //��� F1 ������
	 else if(GetAsyncKeyState(VK_F2))
	{
		if(t>50&&t<1000)
		{
			t+=50;
		}
	 } //��� F2 ������
	else if(GetAsyncKeyState(VK_SPACE))
	{
		pause();
	}

}

void  move() //�ߵ��ƶ� 
{
	snake *p;
	p = (snake*)malloc(sizeof(snake));
	if (NULL == p) 
	{ 
        printf("����ռ��ڴ�ʧ�ܣ�");
		p = (snake *)malloc(sizeof(snake));
     } 
	if (status == U)        //������ʱ 
	{
		p->x = head->x;
		p->y = head->y - 1;
		if (p->x == food->x && p->y == food->y)//�����һ����ʳ��
		{
			food->next = head;
			head = food;
			Eat();
			CreateFood();
		}
		else            //�����һ������ʳ��
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
	if (status == D)       //������ʱ 
	{
		p->x = head->x;
		p->y = head->y + 1;
		if (p->x == food->x && p->y == food->y)//�����һ����ʳ��
		{
			food->next = head;
			head = food;
			Eat();
			CreateFood();
		}
		else//�����һ��û��ʳ��
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
	if (status == L)         //������ʱ 
	{
		p->x = head->x - 1;
		p->y = head->y;
		if (p->x == food->x && p->y == food->y)//�����һ����ʳ��
		{
			food->next = head;
			head = food;
			Eat();
			CreateFood();
		}
		else//�����һ��û��ʳ��
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
	if (status == R)          //������ʱ 
	{
		p->x = head->x + 1;
		p->y = head->y;
		if (p->x == food->x && p->y == food->y)//�����ʳ��
		{
			food->next = head;
			head = food;
			Eat();
			CreateFood();
		}
		else//���û��ʳ��
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

void Bye() //��������
{
	char ch;
	system("cls");
	creatMap_1();
	system("title ��Ϸ����");
	Pos(18,7);
	printf("Ŷ��������(�i_�i)\n");
	Pos(18,11);
	printf("��ķ����ǣ�%d\n",score);
	Pos(15,17);
	printf("��ENTER�����¿�ʼ��Ϸ����ESC�˳���Ϸ"); 
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

void Isdead_4()//ģʽ���ж�����
{
	int i;
	if(head->x==0 || head->x==80 ||head->y==0 || head->y==27||Biteitself())//�ж��Ƿ�ײ��߿���Լ�
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

void Isdead()//ģʽ1.2.3�ж�����
{
	if(head->x==1 || head->x==78 ||head->y==0 || head->y==26||Biteitself())//�ж��Ƿ�ײ��߿���Լ�
	{
        Bye();
	}
}

int Biteitself()//�ж��Ƿ�ҧ���Լ�
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

void Eat()//��ʳ��
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
 	printf("�÷֣�%d ",score);
}

void hidden()//���ع��
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cci;
	GetConsoleCursorInfo(hOut,&cci);
	cci.bVisible=0;//��ֵ1Ϊ��ʾ��0������
	SetConsoleCursorInfo(hOut,&cci);
}

void pause()//��ͣ
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







