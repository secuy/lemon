#include<stdio.h>
#include<stdlib.h>
#define STACK_INIT_SIZE 100  //初始栈空间分配能够存储的ElementType元素个数
#define STACKINCREMENT 10  //站空间不够用后每次增加的存储量
typedef struct 
{
	char value;
}ElementType;
typedef struct
{
	ElementType *base;  //栈底指针
	ElementType *top;  //栈顶指针
	int stacksize;   //当前栈总共能容纳多少个ElementType元素（最大容量）
}SqStack;
typedef short Status;  //返回值状态

//实验一（顺序栈）
//1.构造空栈，分配空间
Status InitStack(SqStack &S)
{
	S.base=(ElementType*)malloc(sizeof(ElementType)*STACK_INIT_SIZE);
	if(S.base==NULL)  return 0;  //内存分配失败，返回0
	S.top=S.base;
	S.stacksize=STACK_INIT_SIZE;
	return 1;
}

//2.销毁已分配的栈，回收栈空间
Status DestoryStack(SqStack &S)
{
	if(S.base==NULL)  return -1;  //传入的栈不存在，失败
	free(S.base);
	S.base=NULL;
	S.top=NULL;
	S.stacksize=0;
	return 1;
}

//3.判断S是否为空栈，是返回1，否则返回0
Status StackEmpty(SqStack S)
{
	if(S.base==NULL)   return -1;  //传入栈不存在
	if(S.base==S.top)
		return 1;   //若栈顶指针与栈底指针指向同一元素，则为空栈，返回1
	else
		return 0;   //S不为空栈，返回0
}

//4.返回S中元素个数
int StackLength(SqStack S)
{
	if(S.base==NULL)  return -1;  //传入的栈不存在，返回值-1
	int length=0;
	while(S.base!=S.top)
	{
		length++;
		S.base++;
	}
	return length;
}

//5.返回栈顶元素给e,如果空栈函数返回-1,正常返回1
Status GetTop(SqStack S,ElementType &e)
{
	if(S.base==S.top)
		return -1;  //空栈返回-1
	else
	{
		e.value=(S.top-1)->value;
		return 1;   //正常返回1
	}
}

//6.插入e为新的栈顶元素，如果栈空间不够，自动扩充（realloc函数）
Status Push(SqStack &S,ElementType e)
{
	if(StackLength(S)>=S.stacksize)
	{
		ElementType*newbase=(ElementType*)realloc(S.base,(S.stacksize+STACKINCREMENT)*sizeof(ElementType));
		if(newbase==NULL)   return 0;  //增加空间失败，返回值为0
		S.base=newbase;
		S.top=S.base+S.stacksize;  //对增加后的空间，栈底栈顶指针重新设定
		S.stacksize+=STACKINCREMENT;  //栈总容量增加
	}
	S.top->value=e.value;
	S.top++;
	return 1;
}

//7.从栈中删除栈顶元素，并放在e中，空栈函数返回-1，正常返回1
Status Pop(SqStack &S,ElementType &e)
{
	if(S.base==S.top)  return -1;  //为空栈，返回-1
	S.top--;
	e.value=S.top->value;  //取栈顶元素放在e中,并将S.top指针向下降
	return 1;
}

//实验二
void main()
{
	SqStack S1,S2;   //定义两个顺序栈
	S1.base=NULL;    S2.base=NULL;
	S1.top=NULL;     S2.top=NULL;
	S1.stacksize=0;  S2.stacksize=NULL;  // 进行初始化
	if(InitStack(S1)!=1||InitStack(S2)!=1)
	{
		printf("初始化失败！");
		return;
	}
	int num;
	ElementType inputdata,movedata,s1data,s2data;   //定义输入数据，元素移动数据，栈1的数据，栈2的数据
	printf("请输入字符串长度（回车符结束）:");
	scanf("%d",&num);
	getchar();
	printf("请输入需要判断的一个字符串，输入格式为序列1&序列2（回车符结束）：");
	for(int i=0;i<=num-1;i++)
	{
		scanf("%c",&inputdata.value);
		Push(S1,inputdata);   //将输入的数据放入栈S1中
	}
	if(StackEmpty(S1)!=0)
	{
		printf("输入数据失败！");
		return;
	}
	while((S1.top-1)->value!='&')
	{
		Pop(S1,movedata);
		Push(S2,movedata);  //进行&右方的序列放入另一栈中
	}
	Pop(S1,movedata);  //将第一个栈中的&删除
	while(StackLength(S1)!=0&&StackLength(S2)!=0)
	{
		Pop(S1,s1data);
		Pop(S2,s2data);
		if(s1data.value!=s2data.value)
		{
			printf("该字符不符合逆序要求！\n");
			DestoryStack(S1);  DestoryStack(S2);  //摧毁栈，回收空间
			return;
		}
	}
	if(StackLength(S1)!=StackLength(S2))  //如果剩下的序列长度不同，则两序列不同
	{
		printf("该字符不符合逆序要求！\n");
		DestoryStack(S1);  DestoryStack(S2);  //摧毁栈，回收空间
		return;
	}
	printf("该字符符合逆序要求！\n");
	DestoryStack(S1);  DestoryStack(S2);  //摧毁栈，回收空间
}