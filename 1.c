#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <Windows.h>

//д�����ַ����ģ���ʵ���ʻ���һ�ַ��������û��ݽ��
//���Ǳ�����������ģ�����Ӵ�
//�ﵽ�˿ɹ۵�8^64��ģ��Ҳ����2^192�������ռ䣬����һ���൱�൱�ɹ۵����������ҵ�С�Ƶ������ܼ����ǲ����ܵ�
// ���ֻ���˶������ѡ����5*5������
// 
// 8x8 ����һ��Ҳû���ܳ���

//
//����ת�ַ���
#define INTERTOSTR(W) #W

//
//�ı���ʾ������ɫ������
#define SETCOLOR system("color fc");
#define SETCOLORNORMAL system("color 0f");
#define OPENCOLORSET system("color xx");
//
//��ͣ������
#define PAUSE system("pause");

//
//�ض�������
#define WRITEREOPEN freopen("input.txt","r+",stdin);

//
//�ض������
#define OUTTOFILE   freopen("output.txt","w+",stdout);

//
//�ر���������ض���
#define CLOSEREOPEN freopen("CON","w",stdout);\
freopen("CON","r",stdin);


//
//����
#define CLEANSCREEN system("cls");

//
//��ʾĿ¼�ṹ
#define SHOWDIR system("dir.");\
printf("\n\n");\
system("tree");
#define DEBUG 1
#if DEBUG==1
#define KEYBOARDSIZE 5
typedef struct Stack
{
	int x;
	int y;
	int Direction;
	//��Ӧ����
	//	0.	x+2,	y-1
	//	1.	x+2,	y+1
	//
	//	2.	x+1,	y-2
	//	3.	x+1		y+2
	// 
	//	4.	x-2		y-1
	//	5.	x-2		y+1
	// 
	//	6.	x-1		y+2
	//	7.	x-1		y-1	
	//
	int Count;
	struct Stack* Next;
}Stack;
Stack* UnitStack;
int KeyBoard [KEYBOARDSIZE][KEYBOARDSIZE];
int KeyLX;
int KeyLY;
int StartX;
int StartY;
int Times[65];
int InitStack(Stack **S);
int Push(Stack* S,int x,int y,int Direcction,int count);
int Pop(Stack* S, int* x, int* y, int* Direction, int* count);
int IfEmpty(Stack* S);
int ClearStack(Stack* S);
int InitKeyBoard();
int InputLocation();
int DirectionCalNext(int x,int y,int Direction);
int DFS(Stack *S);
int PrintKeyBoard();
int PrintPath(Stack *S);
int JudgeIfOver();
int Menu();
int adjustcolor();
int ExampleA();
int ExampleB();
int ExampleC();
int main(int argv, char* argc[])
{
	Menu();
	return 0;
}
int Menu()
{
		int c = 0;
		while (1)
		{
			printf("------------�鿴�˵�---------------\n");
			printf("\n");
			printf("\t1.��ʼ������\n");
			printf("\t2.��ʼ��һ��ջ\n");
			printf("\t3.������ʼ��(����������������ʱ�临�Ӷȷǳ������൱ʱ�����޷��ó����)\n");
			printf("\t4.����DFS�ӻ��ݷ��������̽��б���\n");
			printf("\t5.��ӡ��ǰ���̸��\n");
			printf("\t6.��ӡ·��\n");
			printf("\t7.������ʾ1\n");
			printf("\t8.������ʾ2\n");
			printf("\t9.������ʾ3\n");
			printf("\n");
			printf("\n");
			printf("\t10.ɫ�ʵ���\n");
			printf("\t11.��Ŀ�ṹ\n");
			printf("\t12.����\n");
			printf("\n");
			printf("\t0.�˳�\n");
			printf("|                               |\n");
			printf("     _____________________\n");
			printf("\n");
			printf("��ʾ:\t");
			printf("���ڽ�����������֮ǰ�����ջ�����̵Ƚṹ���г�ʼ�������������������\n");
			printf("����������ѡ��:\t");
			scanf("%d", &c);
			switch (c)
			{
			case 1:
				InitKeyBoard();
				printf("�����ɹ�!\n");
				PAUSE
					CLEANSCREEN
					break;
			case 2:
				InitStack(&UnitStack);
				printf("��ʼ���ɹ�!\n");
				PAUSE
					CLEANSCREEN
					break;
			case 3:
			{
				int x = 0;
				int y = 0;
				printf("�������ʼ������,(����-1��-1�ָ�Ĭ��ֵ)\n");
				printf("StartX=\t");
				scanf("%d", &x);
				printf("StartY=\t");
				scanf("%d", &y);
				if ((x < 0 || y < 0)&&x!=-1&&y!=-1)
				{
					printf("�����ֵ���Ϸ�!\n");
					break;
				}
				if (x > KEYBOARDSIZE || y > KEYBOARDSIZE)
				{
					printf("�����ֵ���Ϸ�!\n");
					break;
				}
				if (x == -1 && y == -1)
				{
					StartX = 2;
					StartY = 1;
					
					break;
				}
				StartX = x;
				StartY = y;
				PAUSE
					CLEANSCREEN
			}
					break;
			case 4:
				DFS(UnitStack);
				PAUSE
					CLEANSCREEN
					break;
			case 5:
				printf("\n");
				PrintKeyBoard();
				printf("\n");
				PAUSE
					CLEANSCREEN
					break;
			case 6:
				printf("\n");
				PrintPath(UnitStack);
				printf("\n");
				PAUSE
					CLEANSCREEN
					break;
			case 7:
				ExampleA();
				PAUSE
					CLEANSCREEN
					break;
			case 8:
				ExampleB();
				PAUSE
					CLEANSCREEN
					break;
			case 9:
				ExampleC();
				PAUSE
					CLEANSCREEN
					break;
			case 10:
				printf("���ڽ��еĲ�����\t");
				printf("------ɫ�ʵ���-------\n");
				adjustcolor();
				PAUSE
					CLEANSCREEN
					break;
			case 11:
				printf("���ڽ��еĲ�����\t");
				printf("-------��Ŀ�ṹ------\n");
				SHOWDIR
					PAUSE
					CLEANSCREEN
					break;
			case 12:
			{
				getchar();
				printf("ȷ��Ҫ������?(y/n)\n");
				char tag = getchar();
				if ('y' == tag || 'Y' == tag)
					CLEANSCREEN
			}
			break;
			case 0:
				printf("�˳�\n");
				PAUSE;
				CLEANSCREEN

					return 0;
			}
		}

}

int adjustcolor()
{
	system("cls");
	while (1)
	{
		CLEANSCREEN
			printf("-----------��ѡ����Ҫ�ı�Ŀ���̨ɫ��ģʽ-----------\n");
		printf("\t1.�ڰ�ģʽ\n");
		printf("\t2.�׺�ģʽ\n");
		printf("\t3.�򿪲˵����鿴�Զ���ɫ��ģʽ\n");
		printf("\t0.�ҵ����/������ˣ���Ҫ����\n");
		int n = 1;
		scanf("%d", &n);
		switch (n)
		{
		case 1:
			SETCOLORNORMAL
				break;
		case 2:
			SETCOLOR
				break;
		case 3:
		{
			OPENCOLORSET
			char Colorstr[10] = "color ";
			char Mycolor[5];
			printf("����������Ҫ����ɫ:\tcolor ");
			scanf("%s", Mycolor);
			system(strcat(Colorstr, Mycolor));
		}
				break;
		case 0:
			return 0;
		default:
			break;
		}
		system("pause");
	}
	return 0;
}

int InitStack(Stack** S)
{
	Stack* stkPtr = NULL;
	stkPtr = (Stack*)malloc(sizeof(Stack));
	if (!stkPtr)
	{
		printf("In %s:\n", __func__);
		printf("Lines:%d\n", __LINE__);
		printf("This Might Be An Error!\n");
		printf("Malloc Failed!\n");

		return 0;
	}

	*S = stkPtr;

	stkPtr->Count = -1;
	stkPtr->Direction = -1;
	stkPtr->Next = NULL;
	stkPtr->x = -1;
	stkPtr->y = -1;
	return 0;
}

int Push(Stack* S, int x, int y, int Direcction, int count)
{
	Stack* stkPtr = NULL;
	stkPtr = (Stack*)malloc(sizeof(Stack));
	if (!stkPtr)
	{

		printf("In %s:\n", __func__);
		printf("Lines:%d\n", __LINE__);
		printf("This Might Be An Error!\n");
		printf("Malloc Failed!\n");
		return 0;
	}
	stkPtr->Count = count;
	stkPtr->Direction = Direcction;
	stkPtr->Next = NULL;
	stkPtr->x = x;
	stkPtr->y = y;
	stkPtr->Next = S->Next;
	S->Next = stkPtr;
	return 0;

}

int Pop(Stack* S, int* x, int* y, int* Direction, int* count)
{
	Stack* stkptr = NULL;
	stkptr = S->Next;
	*x = stkptr->x;
	*y = stkptr->y;
	*count = stkptr->Count;
	*Direction = stkptr->Direction;
	S->Next = stkptr->Next;
	free(stkptr);
	return 0;
}

int IfEmpty(Stack* S)
{
	if (!S)
	{
		return 1;
	}
	if (!(S->Next))
	{
		return 1;
	}
	return 0;
}

int ClearStack(Stack* S)
{
	int Num;
	Num = 0;
	int *NumPtr = NULL;
	NumPtr = &Num;
	Stack* stkptr = NULL;
	while (S->Next)
	{
		stkptr = S->Next;
		*NumPtr = stkptr->x;
		*NumPtr = stkptr->y;
		*NumPtr = stkptr->Count;
		*NumPtr = stkptr->Direction;
		S->Next = stkptr->Next;
		free(stkptr);
	}
	return 0;
}

int InitKeyBoard()
{
	for (int i = 0; i < KEYBOARDSIZE; i++)
	{
		for (int j = 0; j < KEYBOARDSIZE; j++)
		{
			KeyBoard[i][j] = -1;
		}
	}
	KeyLX = KEYBOARDSIZE;
	KeyLY = KEYBOARDSIZE;
	return 0;
}

int InputLocation()
{
	int LocationX = 0;
	int LocationY = 0;
	printf("��������ʼ�������:\t");
	scanf("%d", &LocationX);
	printf("��������ʼ��������:\t");
	scanf("%d", &LocationY);
	KeyBoard[LocationY][LocationY] = 0;
	StartX = LocationX;
	StartY = LocationY;
	return 0;
}

int DirectionCalNext(int x, int y, int dir)
{
	switch (dir)
	{
	case 0:
		x + 2;
		y - 1;
		break;
	case 1:
		x + 2;
		y + 1;
		break;
	case 2:
		x + 1;
		y - 2;
		break;
	case 3:
		x + 1;
		y + 2;
		break;
	case 4:
		x - 2;
		y - 1;
		break;
	case 5:
		x - 2;
		y + 1;
		break;
	case 6:
		x - 1;
		y + 2;
		break;
	case 7:
		x - 1;
		y - 2;
	default:
		printf("Out Of Range!\n");
		return 0;
		break;
	}
	return x*10+y*100+dir;
}

int NextLoc(Stack* S)
{
	Stack* stkptr = NULL;
	stkptr = S->Next;
	int x = stkptr->x;
	int y = stkptr->y;
	int dir = stkptr->Direction;
	int count = stkptr->Count;
	int flag = 0;
	for (int i = dir; i < 8; i++)
	{
		x = stkptr->x;
		y = stkptr->y;
		switch (i)
		{
			case 0:
				x += 2;
				y -= 1;
				break;
			case 1:
				x += 2;
				y += 1;
				break;
			case 2:
				x += 1;
				y -= 2;
				break;
			case 3:
				x += 1;
				y += 2;
				break;
			case 4:
				x -= 2;
				y -= 1;
				break;
			case 5:
				x -= 2;
				y += 1;
				break;
			case 6:
				x -= 1;
				y += 2;
				break;
			case 7:
				x -= 1;
				y -= 2;
			default:
				//printf("Out Of Range!\n");
				break;
		}
		if (x >= 0 && x < KEYBOARDSIZE && y >= 0 && y < KEYBOARDSIZE && KeyBoard[y][x] == -1)
		{
			flag = 1;
			KeyBoard[y][x] = ++count;
			dir = i;
			break;
		}
	}
	if (flag)
	{
		stkptr = S->Next;
		stkptr->Direction = dir;
		Push(S, x, y, 0, count);
		Times[count]++;
		return 0;
	}
	Pop(S, &x, &y, &dir, &count);
	KeyBoard[y][x] = -1;
	stkptr = S->Next;
	stkptr->Direction++;
	return 0;
}
int DFS(Stack *S)
{
	int Times = 0;
	int Num;
	Num = 0;
	int* NumPtr = NULL;
	NumPtr = &Num;
	Stack* stkptr = NULL;
	while (S->Next)
	{
		stkptr = S->Next;
		*NumPtr = stkptr->x;
		*NumPtr = stkptr->y;
		*NumPtr = stkptr->Count;
		*NumPtr = stkptr->Direction;
		S->Next = stkptr->Next;
		free(stkptr);
	}
	
	int count = 0;
	Push(S, StartX, StartY, 0, 1);
	count++;
	KeyBoard[StartY][StartX] = 1;
	while (count != KEYBOARDSIZE*KEYBOARDSIZE)
	{
		Times++;
		NextLoc(S);
		stkptr = S->Next;
		count = stkptr->Count;
		//printf("%4d,%-4d\n", stkptr->x, stkptr->y);
		//printf("count:%d\n", count);
		if (Times > 5000)
		{
			printf("��ǰ�����ռ����\n");
			return -1;
		}
	}
	return 0;
}

int TryASingleStep(Stack *S)
{
	int x = 0;
	int y = 0;
	int dir=0;
	Stack* stkptr;
	stkptr = NULL;
	stkptr = S->Next;
	x = S->x;
	y = S->y;
	return 0;
}

int PrintKeyBoard()
{
	for (int i = 0; i < KEYBOARDSIZE; i++)
	{
		for (int j = 0; j < KEYBOARDSIZE; j++)
		{
			printf("%3d", KeyBoard[i][j]);
		}
		printf("\n");
	}
	return 0;
}

int PrintPath(Stack* S)
{
	Stack* stkptr = NULL;
	stkptr = S->Next;
	int i = 0;
	while (stkptr)
	{
		printf("%2d,%-4d",stkptr->x,stkptr->y);
		if ((i++) % 5 == 0)
		printf("\n");
		stkptr = stkptr->Next;
	}
	return 0;
}

int JudgeIfOver()
{
	int count = 0;
	count = (UnitStack->Next)->Count;
	if ( count == KEYBOARDSIZE * KEYBOARDSIZE)
	{
		return 1;
	}

	return 0;
}

int ExampleA()
{
	StartX = 0;
	StartY = 0;
	InitStack(&UnitStack);
	InitKeyBoard();
	if(	DFS(UnitStack)==-1)return -1;
	printf("\n\n");
	PrintKeyBoard();
	printf("\n");
	PrintPath(UnitStack);
	return 0;
}

int ExampleB()
{
	StartX = 4;
	StartY = 1;
	InitStack(&UnitStack);
	InitKeyBoard();
	if (DFS(UnitStack) == -1)return -1;
	printf("\n\n");
	PrintKeyBoard();
	printf("\n");
	PrintPath(UnitStack);
	return 0;
}

int ExampleC()
{
	StartX = 3;
	StartY = 1;
	InitStack(&UnitStack);
	InitKeyBoard();
	if (DFS(UnitStack) == -1)return -1;
	printf("\n\n");
	PrintKeyBoard();
	printf("\n");
	PrintPath(UnitStack);
	return 0;

}

#endif

#if DEBUG==2

//�ò��ֳ�����������һ���ֳ������������Ӵ�
//���ǵ�ʱ�临�ӶȵĹ�ģ��
//���д��һ���򻯰汾�ĳ���
//���ֳ���ĺ���˼�붼����ͬ��

//ֻ���������û������ʵ��ջ�Ľṹ

//������������ķ��������˹滮

//#include<stdio.h>
//#include<stdlib.h>
#include<time.h>
#define X 6
#define Y 6
int chess[X][Y];
//�ҵ�����λ��(x��y)λ�õ�ʱ����һ�����ߵ�λ��
int nextxy(int* x, int* y, int count)
{
	switch (count) 
	{
		case 0:
			if (*x + 2 < X && *y - 1 >= 0 && !chess[*x + 2][*y - 1]) 
			{
				*x += 2;
				*y -= 1;
				return 1;
			}
			return 0;
			break;

		case 1:
			if (*x + 2 < X && *y + 1 < Y && !chess[*x + 2][*y + 1])
			{
				*x += 2;
				*y += 1;
				return 1;
			}
			return 0;
			break;
		case 2:
			if (*x + 1 < X && *y - 2 >= 0 && !chess[*x + 1][*y - 2]) 
			{
				*x += 1;
				*y -= 2;
				return 1;
			}
			return 0;
			break;
		case 3:

			if (*x + 1 < X && *y + 2 < Y && !chess[*x + 1][*y + 2]) 
			{
				*x += 1;
				*y += 2;
				return 1;
			}
			return 0;
			break;
		case 4:
			if (*x - 2 >= 0 && *y - 1 >= 0 && !chess[*x - 2][*y - 1])
			{
				*x -= 2;
				*y -= 1;
				return 1;
			}
			return 0;
			break;
		case 5:
			if (*x - 2 >= 0 && *y + 1 < Y && !chess[*x - 2][*y + 1]) 
			{
				*x -= 2;
				*y += 1;
				return 1;
			}
			return 0;
			break;
		case 6:
			if (*x - 1 >= 0 && *y - 2 >= 0 && !chess[*x - 1][*y - 2])
			{
				*x -= 1;
				*y -= 2;
				return 1;
			}
			return 0;
			break;
		case 7:

			if (*x - 1 >= 0 && *y + 2 < Y && !chess[*x - 1][*y + 2])
			{
				*x -= 1;
				*y += 2;
				return 1;
			}
			return 0;

			break;
		default:
			return 0;
			break;
	}
}

// ������ȱ���
// (x,y)Ϊλ������
// 
// tag��һ����Ǳ�����ÿ��һ����tag+1

int travel(int x, int y, int tag)
{
	int x1 = x, y1 = y, flag = 0, count = 0;
	chess[x][y] = tag;
	if (tag == X * Y) 
	{ 
		//�������Ѿ�������ʱ��
		// ��ӡ����
		for (int i = 0; i < X; i++) 
		{
			for (int j = 0; j < Y; j++)
			
			{
				printf("%2d ", chess[i][j]);
			}
			printf("\n");
		}
		printf("\n");
		return 1;
	}
	//����8��λ��
	flag = nextxy(&x1, &y1, count);
	while (0 == flag && count < 7)
	{
		count++;
		flag = nextxy(&x1, &y1, count);
	}
	while (flag) 
	{
		if (travel(x1, y1, tag + 1))
		{
			return 1;
		}
		//������һ���㣬���ԡ�
		x1 = x;
		y1 = y;
		count++;
		flag = nextxy(&x1, &y1, count);
		while (0 == flag && count < 7) 
		{
			count++;
			flag = nextxy(&x1, &y1, count);
		}
		//�ҵ������һ���������꣬��flag = 1������Ϊ0��
	}
	if (flag == 0)
	{
		chess[x][y] = 0;
	}
	return 0;
}

void main() 
{
	clock_t start, finish;
	start = clock();
	for (int i = 0; i < X; i++)
	{
		for (int j = 0; j < Y; j++)
		{
			chess[i][j] = 0;
		}
	}
	if (!travel(2, 0, 1)) 
	{
		printf("����ʼ���޷�����ȫ�֡�");
	}
	for (int i = 0; i < X; i++)
	{
		for (int j = 0; j < Y; j++) 
		{
			printf("%2d ", chess[i][j]);
		}
		printf("\n");
	}
	printf("\n");

	finish = clock();
	printf("���μ��㹲��%f", double(finish - start) / CLOCKS_PER_SEC);

}
#endif	

#if DEBUG==0
#define EXTRELINES 4
int getlength();
int main()
{
	SETCOLOR

		printf("\n������Ϣ:   %s\n", "�˶������ϵͳ");
	printf("��ǰ״̬:   %s\n", RUNNING ? "����" : "����");
	printf("��������:   %s\n", __DATE__);
	printf("����ʱ��:   %s\n", __TIME__);
	printf("����ļ�:   %s\n", __FILE__);
	printf("��ǰ�к�:   %d\n", __LINE__);
	printf("\n");

	int main_c = 0;
	main_c = getlength();
	printf("�ܹ�����:   %d\n", main_c);
	printf("\n");
	printf("��ǰĿ¼�ṹ:\n\n");
	system("tree");
	printf("\n");
	system("dir\n");
	printf("˵��: ���Ҫ���иó��������������ļ��н��� \"RUNNING\" ��ֵ����Ϊ1(��0ֵ)\n\n");
	system("pause");
	return 0;
}
int getlength()
{
	return __LINE__ + EXTRELINES;
}

#endif // DEBUG

