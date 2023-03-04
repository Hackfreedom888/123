#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <Windows.h>

//写了两种方法的，其实本质还是一种方法，利用回溯解决
//但是本问题的问题规模过于庞大
//达到了可观的8^64规模，也就是2^192可搜索空间，这是一个相当相当可观的数量，在我的小破电脑上跑几乎是不可能的
// 因此只能退而求其次选择了5*5的棋盘
// 
// 8x8 跑了一宿也没有跑出来

//
//数字转字符串
#define INTERTOSTR(W) #W

//
//改变显示主题颜色的命令
#define SETCOLOR system("color fc");
#define SETCOLORNORMAL system("color 0f");
#define OPENCOLORSET system("color xx");
//
//暂停的命令
#define PAUSE system("pause");

//
//重定义输入
#define WRITEREOPEN freopen("input.txt","r+",stdin);

//
//重定义输出
#define OUTTOFILE   freopen("output.txt","w+",stdout);

//
//关闭输入输出重定义
#define CLOSEREOPEN freopen("CON","w",stdout);\
freopen("CON","r",stdin);


//
//清屏
#define CLEANSCREEN system("cls");

//
//显示目录结构
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
	//对应方向；
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
			printf("------------查看菜单---------------\n");
			printf("\n");
			printf("\t1.初始化棋盘\n");
			printf("\t2.初始化一个栈\n");
			printf("\t3.输入起始点(谨慎操作，该问题时间复杂度非常大，在相当时间内无法得出结果)\n");
			printf("\t4.利用DFS加回溯方法对棋盘进行遍历\n");
			printf("\t5.打印当前棋盘格局\n");
			printf("\t6.打印路径\n");
			printf("\t7.案例演示1\n");
			printf("\t8.案例演示2\n");
			printf("\t9.案例演示3\n");
			printf("\n");
			printf("\n");
			printf("\t10.色彩调整\n");
			printf("\t11.项目结构\n");
			printf("\t12.清屏\n");
			printf("\n");
			printf("\t0.退出\n");
			printf("|                               |\n");
			printf("     _____________________\n");
			printf("\n");
			printf("提示:\t");
			printf("您在进行其他操作之前必须对栈、棋盘等结构进行初始化，否则可能引起意外\n");
			printf("请输入您的选择:\t");
			scanf("%d", &c);
			switch (c)
			{
			case 1:
				InitKeyBoard();
				printf("创建成功!\n");
				PAUSE
					CLEANSCREEN
					break;
			case 2:
				InitStack(&UnitStack);
				printf("初始化成功!\n");
				PAUSE
					CLEANSCREEN
					break;
			case 3:
			{
				int x = 0;
				int y = 0;
				printf("请输入初始的坐标,(输入-1，-1恢复默认值)\n");
				printf("StartX=\t");
				scanf("%d", &x);
				printf("StartY=\t");
				scanf("%d", &y);
				if ((x < 0 || y < 0)&&x!=-1&&y!=-1)
				{
					printf("输入的值不合法!\n");
					break;
				}
				if (x > KEYBOARDSIZE || y > KEYBOARDSIZE)
				{
					printf("输入的值不合法!\n");
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
				printf("现在进行的操作是\t");
				printf("------色彩调整-------\n");
				adjustcolor();
				PAUSE
					CLEANSCREEN
					break;
			case 11:
				printf("现在进行的操作是\t");
				printf("-------项目结构------\n");
				SHOWDIR
					PAUSE
					CLEANSCREEN
					break;
			case 12:
			{
				getchar();
				printf("确定要清屏吗?(y/n)\n");
				char tag = getchar();
				if ('y' == tag || 'Y' == tag)
					CLEANSCREEN
			}
			break;
			case 0:
				printf("退出\n");
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
			printf("-----------请选择您要改变的控制台色彩模式-----------\n");
		printf("\t1.黑白模式\n");
		printf("\t2.白红模式\n");
		printf("\t3.打开菜单，查看自定义色彩模式\n");
		printf("\t0.我点错了/我完成了，我要返回\n");
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
			printf("请输入您想要的颜色:\tcolor ");
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
	printf("请输入起始点横坐标:\t");
	scanf("%d", &LocationX);
	printf("请输入起始点纵坐标:\t");
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
			printf("当前搜索空间过大\n");
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

//该部分程序是由于上一部分程序体量过于庞大，
//考虑到时间复杂度的规模，
//因此写了一个简化版本的程序，
//两种程序的核心思想都是相同的

//只不过下面的没有明显实现栈的结构

//而是利用数组的方法进行了规划

//#include<stdio.h>
//#include<stdlib.h>
#include<time.h>
#define X 6
#define Y 6
int chess[X][Y];
//找到当马位于(x，y)位置的时候，下一个可走的位置
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

// 深度优先遍历
// (x,y)为位置坐标
// 
// tag是一个标记变量，每走一步，tag+1

int travel(int x, int y, int tag)
{
	int x1 = x, y1 = y, flag = 0, count = 0;
	chess[x][y] = tag;
	if (tag == X * Y) 
	{ 
		//当棋盘已经布满的时候
		// 打印棋盘
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
	//尝试8个位置
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
		//返回上一个点，重试。
		x1 = x;
		y1 = y;
		count++;
		flag = nextxy(&x1, &y1, count);
		while (0 == flag && count < 7) 
		{
			count++;
			flag = nextxy(&x1, &y1, count);
		}
		//找到马的下一步可走坐标，则flag = 1，否则为0。
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
		printf("该起始点无法遍历全局。");
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
	printf("本次计算共用%f", double(finish - start) / CLOCKS_PER_SEC);

}
#endif	

#if DEBUG==0
#define EXTRELINES 4
int getlength();
int main()
{
	SETCOLOR

		printf("\n程序信息:   %s\n", "运动会管理系统");
	printf("当前状态:   %s\n", RUNNING ? "管理" : "运行");
	printf("编译日期:   %s\n", __DATE__);
	printf("运行时刻:   %s\n", __TIME__);
	printf("入口文件:   %s\n", __FILE__);
	printf("当前行号:   %d\n", __LINE__);
	printf("\n");

	int main_c = 0;
	main_c = getlength();
	printf("总共行数:   %d\n", main_c);
	printf("\n");
	printf("当前目录结构:\n\n");
	system("tree");
	printf("\n");
	system("dir\n");
	printf("说明: 如果要运行该程序，请在主函数文件中将宏 \"RUNNING\" 的值设置为1(非0值)\n\n");
	system("pause");
	return 0;
}
int getlength()
{
	return __LINE__ + EXTRELINES;
}

#endif // DEBUG

