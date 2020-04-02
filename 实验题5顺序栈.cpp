#include<stdio.h>
#include<stdlib.h>
#define STACK_INIT_SIZE 100  //��ʼջ�ռ�����ܹ��洢��ElementTypeԪ�ظ���
#define STACKINCREMENT 10  //վ�ռ䲻���ú�ÿ�����ӵĴ洢��
typedef struct 
{
	char value;
}ElementType;
typedef struct
{
	ElementType *base;  //ջ��ָ��
	ElementType *top;  //ջ��ָ��
	int stacksize;   //��ǰջ�ܹ������ɶ��ٸ�ElementTypeԪ�أ����������
}SqStack;
typedef short Status;  //����ֵ״̬

//ʵ��һ��˳��ջ��
//1.�����ջ������ռ�
Status InitStack(SqStack &S)
{
	S.base=(ElementType*)malloc(sizeof(ElementType)*STACK_INIT_SIZE);
	if(S.base==NULL)  return 0;  //�ڴ����ʧ�ܣ�����0
	S.top=S.base;
	S.stacksize=STACK_INIT_SIZE;
	return 1;
}

//2.�����ѷ����ջ������ջ�ռ�
Status DestoryStack(SqStack &S)
{
	if(S.base==NULL)  return -1;  //�����ջ�����ڣ�ʧ��
	free(S.base);
	S.base=NULL;
	S.top=NULL;
	S.stacksize=0;
	return 1;
}

//3.�ж�S�Ƿ�Ϊ��ջ���Ƿ���1�����򷵻�0
Status StackEmpty(SqStack S)
{
	if(S.base==NULL)   return -1;  //����ջ������
	if(S.base==S.top)
		return 1;   //��ջ��ָ����ջ��ָ��ָ��ͬһԪ�أ���Ϊ��ջ������1
	else
		return 0;   //S��Ϊ��ջ������0
}

//4.����S��Ԫ�ظ���
int StackLength(SqStack S)
{
	if(S.base==NULL)  return -1;  //�����ջ�����ڣ�����ֵ-1
	int length=0;
	while(S.base!=S.top)
	{
		length++;
		S.base++;
	}
	return length;
}

//5.����ջ��Ԫ�ظ�e,�����ջ��������-1,��������1
Status GetTop(SqStack S,ElementType &e)
{
	if(S.base==S.top)
		return -1;  //��ջ����-1
	else
	{
		e.value=(S.top-1)->value;
		return 1;   //��������1
	}
}

//6.����eΪ�µ�ջ��Ԫ�أ����ջ�ռ䲻�����Զ����䣨realloc������
Status Push(SqStack &S,ElementType e)
{
	if(StackLength(S)>=S.stacksize)
	{
		ElementType*newbase=(ElementType*)realloc(S.base,(S.stacksize+STACKINCREMENT)*sizeof(ElementType));
		if(newbase==NULL)   return 0;  //���ӿռ�ʧ�ܣ�����ֵΪ0
		S.base=newbase;
		S.top=S.base+S.stacksize;  //�����Ӻ�Ŀռ䣬ջ��ջ��ָ�������趨
		S.stacksize+=STACKINCREMENT;  //ջ����������
	}
	S.top->value=e.value;
	S.top++;
	return 1;
}

//7.��ջ��ɾ��ջ��Ԫ�أ�������e�У���ջ��������-1����������1
Status Pop(SqStack &S,ElementType &e)
{
	if(S.base==S.top)  return -1;  //Ϊ��ջ������-1
	S.top--;
	e.value=S.top->value;  //ȡջ��Ԫ�ط���e��,����S.topָ�����½�
	return 1;
}

//ʵ���
void main()
{
	SqStack S1,S2;   //��������˳��ջ
	S1.base=NULL;    S2.base=NULL;
	S1.top=NULL;     S2.top=NULL;
	S1.stacksize=0;  S2.stacksize=NULL;  // ���г�ʼ��
	if(InitStack(S1)!=1||InitStack(S2)!=1)
	{
		printf("��ʼ��ʧ�ܣ�");
		return;
	}
	int num;
	ElementType inputdata,movedata,s1data,s2data;   //�����������ݣ�Ԫ���ƶ����ݣ�ջ1�����ݣ�ջ2������
	printf("�������ַ������ȣ��س���������:");
	scanf("%d",&num);
	getchar();
	printf("��������Ҫ�жϵ�һ���ַ����������ʽΪ����1&����2���س�����������");
	for(int i=0;i<=num-1;i++)
	{
		scanf("%c",&inputdata.value);
		Push(S1,inputdata);   //����������ݷ���ջS1��
	}
	if(StackEmpty(S1)!=0)
	{
		printf("��������ʧ�ܣ�");
		return;
	}
	while((S1.top-1)->value!='&')
	{
		Pop(S1,movedata);
		Push(S2,movedata);  //����&�ҷ������з�����һջ��
	}
	Pop(S1,movedata);  //����һ��ջ�е�&ɾ��
	while(StackLength(S1)!=0&&StackLength(S2)!=0)
	{
		Pop(S1,s1data);
		Pop(S2,s2data);
		if(s1data.value!=s2data.value)
		{
			printf("���ַ�����������Ҫ��\n");
			DestoryStack(S1);  DestoryStack(S2);  //�ݻ�ջ�����տռ�
			return;
		}
	}
	if(StackLength(S1)!=StackLength(S2))  //���ʣ�µ����г��Ȳ�ͬ���������в�ͬ
	{
		printf("���ַ�����������Ҫ��\n");
		DestoryStack(S1);  DestoryStack(S2);  //�ݻ�ջ�����տռ�
		return;
	}
	printf("���ַ���������Ҫ��\n");
	DestoryStack(S1);  DestoryStack(S2);  //�ݻ�ջ�����տռ�
}