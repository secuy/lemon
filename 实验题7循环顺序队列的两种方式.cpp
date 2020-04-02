#include<stdio.h>
#include<stdlib.h>
#define MAXQSIZE 10  //����ѭ�������������
#define INCREMENT 10  //����������
typedef struct{
	char value;
}QElemType1,QElemType2;   //QElemType1�����һ�ַ�ʽ�µ��������ͣ�QElemType2����ڶ��ַ�ʽ�µ���������
typedef short Status;

//1.�Խṹ���Ա����tag,tag=0��ʾ�գ�tag=1��ʾ�ǿ�
typedef struct{
	QElemType1 *base;
	int front;
	int rear;
	int maxsize;   //ѭ�����е����ռ�
	short tag;
}SqQueue1;
//(1)��ʼ������
Status InitQueue1(SqQueue1 &Q)
{
	if(Q.base!=NULL)  return 0;  //���в�Ϊ��
	Q.base=(QElemType1*)malloc(sizeof(QElemType1)*MAXQSIZE);
	if(NULL==Q.base)  return -1;  //�����ڴ�ʧ��
	Q.front=Q.rear=0;   //��ʼ����β���ͷ
	Q.maxsize=MAXQSIZE;
	Q.tag=0;  //tagΪ0ʱ��ʾ��
	return 1;
}
//(2)��Ӳ���
Status EnQueue1(SqQueue1 &Q,QElemType1 e)
{
	if(Q.tag==1&&Q.front==Q.rear)  //���������������,���Ӵ洢
	{
		QElemType1*temp=(QElemType1 *)malloc(sizeof(QElemType1)*(Q.maxsize+INCREMENT));
		int i=0;
		while(i<Q.maxsize)   //���ж��и��Ʋ���
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
	(Q.base+Q.rear)->value=e.value;   //�ڶ�β��������
	Q.rear=(Q.rear+1)%(Q.maxsize);  //��βָ��ָ����һ��
	Q.tag=1;   //�����������ݽ��룬�ǿգ�tag=1
	return 1;
}
//(3)���Ӳ���
Status DeQueue1(SqQueue1 &Q,QElemType1 &e)
{
	if(Q.tag==0)   return 0;  //����Ϊ�գ����Ӳ���ʧ��
	e.value=(Q.base+Q.front)->value;   //��¼���ӵĶ�ͷԪ��
	Q.front=(Q.front+1)%(Q.maxsize);  //��ͷָ������ƶ�
	if(Q.front==Q.rear)
		Q.tag=0;   //���Ӳ����������ͷ���βָ����ͬ�����һ��Ϊ��
	else
		Q.tag=1;   //����Ϊ��
	return 1;
}
//(4)ѭ�����г���
int Length(SqQueue1 Q)
{
	int len=0;
	if(0==Q.tag)
		return len;
	else
		if(Q.front==Q.rear)   //ѭ����������ʱ��
		{
			len=Q.maxsize;
			return len;
		}
		else   //ѭ�����в�����ʱ��
		{
			len=(Q.rear-Q.front+Q.maxsize)%(Q.maxsize);
			return len;
		}
}

//2.����һ���ṹ�����length����lengthֵ����һϵ�в���
typedef struct{
	QElemType2 *base;
	int front;
	int rear;
	int maxsize;
	int length;   //ѭ�����г���ֵ
}SqQueue2;
//(1)��ʼ������
Status InitQueue2(SqQueue2 &Q)
{
	if(Q.base!=NULL)   return 0;
	Q.base=(QElemType2 *)malloc(sizeof(QElemType2)*MAXQSIZE);
	if(NULL==Q.base)   return -1;
	Q.front=Q.rear=0;
	Q.maxsize=MAXQSIZE;
	Q.length=0;  //��ʼ��
	return 1;
}
//(2)��Ӳ���
Status EnQueue2(SqQueue2 &Q,QElemType2 e)
{
	if(Q.length==Q.maxsize)  //ѭ������������������
	{
		QElemType2*temp=(QElemType2*)malloc(sizeof(QElemType2)*(Q.maxsize+INCREMENT));
		int i=0;
		while(i<Q.length)  //���и��Ʋ���
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
	Q.rear=(Q.rear+1)%(Q.maxsize);  //��βָ��ָ����һ��
	Q.length++;  //��������
	return 1;
}
//(3)���Ӳ���
Status DeQueue2(SqQueue2 &Q,QElemType2 &e)
{
	if(Q.length==0||Q.base==NULL)   return 0;
	e.value=(Q.base+Q.front)->value;
	Q.front=(Q.front+1)%Q.maxsize;
	Q.length--;  //���ȼ���
	return 1;
}
//(4)�ж�ѭ�������Ƿ�Ϊ��
void IsEmpty(SqQueue2 Q)
{
	if(NULL==Q.base)  return;
	if(Q.length==0)
		printf("��ѭ������Ϊ�գ�");
	else
		printf("��ѭ�����в�Ϊ�գ�");
}

void PrintQueue1(SqQueue1 Q)  //��ӡ��һ�ֲ�����ѭ�������е�����
{
	int len=Length(Q);
	if(len==0)
		printf("ѭ������Ϊ�գ�\n");
	else
	    for(int i=0;i<len;i++)
		    printf("ѭ�������е�%d��Ԫ�أ���%d�����ǣ�%c\n",i+1,len,(Q.base+((Q.front+i)%Q.maxsize))->value);
}
void PrintQueue2(SqQueue2 Q)  //��ӡ�ڶ��ֲ�����ѭ�������е�����
{
	if(Q.length==0)
		printf("ѭ������Ϊ�գ�\n");
	else
	    for(int i=0;i<Q.length;i++)
		    printf("ѭ�������е�%d��Ԫ�أ���%d�����ǣ�%c\n",i+1,Q.length,(Q.base+((Q.front+i)%Q.maxsize))->value);
}
void DestoryQueue1(SqQueue1 Q)  //�ݻٵ�һ�ֲ�����ѭ������
{
	free(Q.base);
	Q.base=NULL;
	Q.front=Q.rear=0;
	Q.tag=0; Q.maxsize=0;
}
void DestoryQueue2(SqQueue2 Q)  //�ݻٵڶ��ֲ�����ѭ������
{
	free(Q.base);
	Q.base=NULL;
	Q.front=Q.rear=0;
	Q.length=0; Q.maxsize=0;
}
void main()  //����
{
	SqQueue1 Q1; SqQueue2 Q2;
	Q1.base=NULL; Q2.base=NULL;
	if(InitQueue1(Q1)!=1||InitQueue2(Q2)!=1)
	{
		printf("��ʼ��ʧ�ܣ�\n");
		return;
	}
	printf("��ʼ���ɹ���\n");
	int i,num=0;
	QElemType1 data1; QElemType2 data2;
	printf("�������һ�ֲ�����ѭ�������е����ݸ�����");
	scanf("%d",&num);
	getchar();
	for(i=1;i<=num;i++)
	{
		printf("�������%d�����ݣ���%d������",i,num);
		scanf("%c",&data1.value);
		getchar();
		if(EnQueue1(Q1,data1)!=1)
		{
			printf("����ʧ�ܣ�\n");
			return;
		}
	}
	printf("------------------------------------------------------\n");
	printf("������ڶ��ֲ�����ѭ�������е����ݸ�����");
	scanf("%d",&num);
	getchar();
	for(i=1;i<=num;i++)
	{
		printf("�������%d�����ݣ���%d������",i,num);
		scanf("%c",&data2.value);
		getchar();
		if(EnQueue2(Q2,data2)!=1)
		{
			printf("����ʧ�ܣ�\n");
			return;
		}
	}
	printf("------------------------------------------------------\n");
	printf("��һ�ֲ����Ķ������£�����Ϊ%d\n",Length(Q1));
	PrintQueue1(Q1);
	printf("------------------------------------------------------\n");
	printf("�ڶ��ֲ����Ķ������£�����Ϊ%d\n",Q2.length);
	PrintQueue2(Q2);
	QElemType1 del1; QElemType2 del2;  //ɾ����������
	DeQueue1(Q1,del1); DeQueue2(Q2,del2);
    printf("------------------------------------------------------\n");
	printf("��һ�ֲ����Ķ���ɾ�������£�����Ϊ%d��ɾ��Ԫ��Ϊ��%c\n",Length(Q1),del1.value);
	PrintQueue1(Q1);
	printf("------------------------------------------------------\n");
	printf("�ڶ��ֲ����Ķ���ɾ�������£�����Ϊ%d��ɾ��Ԫ��Ϊ��%c\n",Q2.length,del2.value);
	PrintQueue2(Q2);
	DestoryQueue1(Q1);DestoryQueue2(Q2);
}
