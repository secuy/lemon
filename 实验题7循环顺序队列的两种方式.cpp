#include<stdio.h>
#include<stdlib.h>
#define MAXQSIZE 10  //定义循环队列最大容量
#define INCREMENT 10  //定义增加量
typedef struct{
	char value;
}QElemType1,QElemType2;   //QElemType1代表第一种方式下的数据类型，QElemType2代表第二种方式下的数据类型
typedef short Status;

//1.对结构体成员变量tag,tag=0表示空，tag=1表示非空
typedef struct{
	QElemType1 *base;
	int front;
	int rear;
	int maxsize;   //循环队列的最大空间
	short tag;
}SqQueue1;
//(1)初始化队列
Status InitQueue1(SqQueue1 &Q)
{
	if(Q.base!=NULL)  return 0;  //队列不为空
	Q.base=(QElemType1*)malloc(sizeof(QElemType1)*MAXQSIZE);
	if(NULL==Q.base)  return -1;  //分配内存失败
	Q.front=Q.rear=0;   //初始化队尾与队头
	Q.maxsize=MAXQSIZE;
	Q.tag=0;  //tag为0时表示空
	return 1;
}
//(2)入队操作
Status EnQueue1(SqQueue1 &Q,QElemType1 e)
{
	if(Q.tag==1&&Q.front==Q.rear)  //当队列满的情况下,增加存储
	{
		QElemType1*temp=(QElemType1 *)malloc(sizeof(QElemType1)*(Q.maxsize+INCREMENT));
		int i=0;
		while(i<Q.maxsize)   //进行队列复制操作
		{
			(temp+i)->value=(Q.base+Q.front)->value;
			Q.front=(Q.front+1)%(Q.maxsize);
			i++;
		}
		free(Q.base);
		Q.base=temp;
		Q.front=0;
		Q.rear=i;
		Q.maxsize+=INCREMENT;
	}
	(Q.base+Q.rear)->value=e.value;   //在队尾插入数据
	Q.rear=(Q.rear+1)%(Q.maxsize);  //队尾指针指向下一个
	Q.tag=1;   //队列中有数据进入，非空，tag=1
	return 1;
}
//(3)出队操作
Status DeQueue1(SqQueue1 &Q,QElemType1 &e)
{
	if(Q.tag==0)   return 0;  //队列为空，出队操作失败
	e.value=(Q.base+Q.front)->value;   //记录出队的队头元素
	Q.front=(Q.front+1)%(Q.maxsize);  //队头指针进行移动
	if(Q.front==Q.rear)
		Q.tag=0;   //出队操作后如果队头与队尾指针相同则队列一定为空
	else
		Q.tag=1;   //否则不为空
	return 1;
}
//(4)循环队列长度
int Length(SqQueue1 Q)
{
	int len=0;
	if(0==Q.tag)
		return len;
	else
		if(Q.front==Q.rear)   //循环队列满的时候
		{
			len=Q.maxsize;
			return len;
		}
		else   //循环队列不满的时候
		{
			len=(Q.rear-Q.front+Q.maxsize)%(Q.maxsize);
			return len;
		}
}

//2.增加一个结构体变量length，以length值进行一系列操作
typedef struct{
	QElemType2 *base;
	int front;
	int rear;
	int maxsize;
	int length;   //循环队列长度值
}SqQueue2;
//(1)初始化队列
Status InitQueue2(SqQueue2 &Q)
{
	if(Q.base!=NULL)   return 0;
	Q.base=(QElemType2 *)malloc(sizeof(QElemType2)*MAXQSIZE);
	if(NULL==Q.base)   return -1;
	Q.front=Q.rear=0;
	Q.maxsize=MAXQSIZE;
	Q.length=0;  //初始化
	return 1;
}
//(2)入队操作
Status EnQueue2(SqQueue2 &Q,QElemType2 e)
{
	if(Q.length==Q.maxsize)  //循环队列已满进行扩增
	{
		QElemType2*temp=(QElemType2*)malloc(sizeof(QElemType2)*(Q.maxsize+INCREMENT));
		int i=0;
		while(i<Q.length)  //进行复制操作
		{
			(temp+i)->value=(Q.base+Q.front)->value;
			Q.front=(Q.front+1)%Q.maxsize;
			i++;
		}
		free(Q.base);
		Q.base=temp;
		Q.front=0;
		Q.rear=i;
		Q.maxsize+=INCREMENT;
	}
	(Q.base+Q.rear)->value=e.value;
	Q.rear=(Q.rear+1)%(Q.maxsize);  //队尾指针指向下一个
	Q.length++;  //长度增加
	return 1;
}
//(3)出队操作
Status DeQueue2(SqQueue2 &Q,QElemType2 &e)
{
	if(Q.length==0||Q.base==NULL)   return 0;
	e.value=(Q.base+Q.front)->value;
	Q.front=(Q.front+1)%Q.maxsize;
	Q.length--;  //长度减少
	return 1;
}
//(4)判断循环队列是否为空
void IsEmpty(SqQueue2 Q)
{
	if(NULL==Q.base)  return;
	if(Q.length==0)
		printf("该循环队列为空！");
	else
		printf("该循环队列不为空！");
}

void PrintQueue1(SqQueue1 Q)  //打印第一种操作的循环队列中的数据
{
	int len=Length(Q);
	if(len==0)
		printf("循环队列为空！\n");
	else
	    for(int i=0;i<len;i++)
		    printf("循环队列中第%d个元素（共%d个）是：%c\n",i+1,len,(Q.base+((Q.front+i)%Q.maxsize))->value);
}
void PrintQueue2(SqQueue2 Q)  //打印第二种操作的循环队列中的数据
{
	if(Q.length==0)
		printf("循环队列为空！\n");
	else
	    for(int i=0;i<Q.length;i++)
		    printf("循环队列中第%d个元素（共%d个）是：%c\n",i+1,Q.length,(Q.base+((Q.front+i)%Q.maxsize))->value);
}
void DestoryQueue1(SqQueue1 Q)  //摧毁第一种操作的循环队列
{
	free(Q.base);
	Q.base=NULL;
	Q.front=Q.rear=0;
	Q.tag=0; Q.maxsize=0;
}
void DestoryQueue2(SqQueue2 Q)  //摧毁第二种操作的循环队列
{
	free(Q.base);
	Q.base=NULL;
	Q.front=Q.rear=0;
	Q.length=0; Q.maxsize=0;
}
void main()  //测试
{
	SqQueue1 Q1; SqQueue2 Q2;
	Q1.base=NULL; Q2.base=NULL;
	if(InitQueue1(Q1)!=1||InitQueue2(Q2)!=1)
	{
		printf("初始化失败！\n");
		return;
	}
	printf("初始化成功！\n");
	int i,num=0;
	QElemType1 data1; QElemType2 data2;
	printf("请输入第一种操作的循环队列中的数据个数：");
	scanf("%d",&num);
	getchar();
	for(i=1;i<=num;i++)
	{
		printf("请输入第%d个数据（共%d个）：",i,num);
		scanf("%c",&data1.value);
		getchar();
		if(EnQueue1(Q1,data1)!=1)
		{
			printf("输入失败！\n");
			return;
		}
	}
	printf("------------------------------------------------------\n");
	printf("请输入第二种操作的循环队列中的数据个数：");
	scanf("%d",&num);
	getchar();
	for(i=1;i<=num;i++)
	{
		printf("请输入第%d个数据（共%d个）：",i,num);
		scanf("%c",&data2.value);
		getchar();
		if(EnQueue2(Q2,data2)!=1)
		{
			printf("输入失败！\n");
			return;
		}
	}
	printf("------------------------------------------------------\n");
	printf("第一种操作的队列如下，长度为%d\n",Length(Q1));
	PrintQueue1(Q1);
	printf("------------------------------------------------------\n");
	printf("第二种操作的队列如下，长度为%d\n",Q2.length);
	PrintQueue2(Q2);
	QElemType1 del1; QElemType2 del2;  //删除操作测试
	DeQueue1(Q1,del1); DeQueue2(Q2,del2);
    printf("------------------------------------------------------\n");
	printf("第一种操作的队列删除后如下，长度为%d，删除元素为：%c\n",Length(Q1),del1.value);
	PrintQueue1(Q1);
	printf("------------------------------------------------------\n");
	printf("第二种操作的队列删除后如下，长度为%d，删除元素为：%c\n",Q2.length,del2.value);
	PrintQueue2(Q2);
	DestoryQueue1(Q1);DestoryQueue2(Q2);
}
