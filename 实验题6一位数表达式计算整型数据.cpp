#include<stdio.h>
#include<stdlib.h>
#define INIT_STACK_SIZE 100  //����ջ�ĳ�ʼ������
#define STACKINCREMENT 10    //������
typedef struct
{
	int value;  //���ｫ�������Ͷ���Ϊint
} Elemtype;   //������������
typedef struct
{
	Elemtype *base;
	Elemtype *top;
	int stacksize;   //ջ���������
}SqStack;   //����ջ

typedef short Status;  //����״ֵ̬

Status CreateStack(SqStack &S)   //����ջ
{
	S.base=(Elemtype *)malloc(sizeof(Elemtype)*INIT_STACK_SIZE);
	if(NULL==S.base)  return 0;   //����ʧ��
	S.top=S.base;
	S.stacksize=INIT_STACK_SIZE;
	return 1;
}

Status DestoryStack(SqStack &S)  //�ݻ�ջ
{
	if(NULL==S.base)  return 0;  //����ջΪ�գ�����ֵ0
	free(S.base);
	S.base=NULL;
	S.top=NULL;
	S.stacksize=0;
	return 1;
}

Elemtype GetTop(SqStack S)  //ȡ��ջ��Ԫ��
{
	return *(S.top-1);
}

Status Push(SqStack &S,Elemtype e)   //��eԪ�ؼ��뵽ջ��
{
	if(NULL==S.base)   return 0;  //����ջΪ��
	if(S.top-S.base>=S.stacksize)  //�ռ䲻�㣬���пռ�����
	{
		Elemtype *newbase=(Elemtype *)realloc(S.base,sizeof(Elemtype)*(INIT_STACK_SIZE+STACKINCREMENT));
		S.base=newbase;
		S.stacksize+=STACKINCREMENT;
		S.top=S.base+S.stacksize;
	}
	S.top->value=e.value;
	S.top++;
	return 1;
}

Status Pop(SqStack &S,Elemtype &e)  //����ջ��Ԫ��e,��ȡ��e
{
	if(NULL==S.base)   return 0;  //����ջΪ��
	e.value=(--S.top)->value;
	return 1;
}

Status IsNum(Elemtype e)
{
	if(e.value-48>=0&&e.value-48<=9)  //���ڴ�������������ַ�ת��Ϊ���ͣ���0����ASCII�����Ϊ48
		return 1;  //����Ԫ��Ϊ���֣�����1
	else
		return 0;  //����Ԫ�ز������֣�����0
}

Elemtype Operate(Elemtype num1,Elemtype Operator,Elemtype num2)  //�����������
{
	int i1,i2,i;
	Elemtype result;  //����������
	i1=num1.value-48;  //���ַ���ASCII��תΪ����
	i2=num2.value-48;
	switch(Operator.value)
	{
	case '+': i= i1+i2;break;
	case '-': i= i1-i2;break;
	case '*': i= i1*i2;break;
	case '/': i= i1/i2;break;
	}
	result.value=i+48;  //������Ϊ���ͣ���������48��Ϊ����ASCII�������ʵ������Ӧ�ü�ȥ48��48��'0'�ַ���ASCII�룩
	return result;
}

char form[7][7]=
{      //  +   -   *   /   (   )   #   //
/* + */	 {'>','>','<','<','<','>','>'},
/* - */	 {'>','>','<','<','<','>','>'},
/* * */	 {'>','>','>','>','<','>','>'},
/* / */  {'>','>','>','>','<','>','>'},
/* ( */	 {'<','<','<','<','<','=','\0'},
/* ) */	 {'>','>','>','>','\0','>','>'},
/* # */	 {'<','<','<','<','<', '\0','='}
};  //����������������ȼ�����>����ʾҪ���������������<����ʾ����������н�ջ������
    //��=����ʾ������ǰ���������һ���������������\0����ʾ��ǰ�������ǰһ������������ܴ���ǰ���ϵ
    //��������һ�����������������ĵ�ǰ�����
char Precede(Elemtype e,char indata)  //e����һ�������indata�ǵ�ǰ���������
{
	short m,n;
	switch ((char)e.value)  //ǿ��ת��Ϊ�ַ���
	{
	    case '+':m=0;break;
		case '-':m=1;break;
		case '*':m=2;break;
	    case '/':m=3;break;
		case '(':m=4;break;
		case ')':m=5;break;
		case '#':m=6;break;
	};
	switch (indata)
	{
	    case '+':n=0;break;
		case '-':n=1;break;
		case '*':n=2;break;
	    case '/':n=3;break;
		case '(':n=4;break;
		case ')':n=5;break;
		case '#':n=6;break;
	};
	return form[m][n];
}

void main()
{
	SqStack OPTR,OPND;  //��������ջ��OPTR����װ�������OPND����װ����
	OPTR.base=NULL;  OPND.base=NULL;
	OPTR.top=NULL;  OPND.top=NULL;
	OPTR.stacksize=0;   OPND.stacksize=0;  //��ʼ��
	if(CreateStack(OPTR)!=1||CreateStack(OPND)!=1)
	{
		printf("��ʼ��ʧ�ܣ�");
		return;
	}
	Elemtype scandata,deldata,data1,data2;  //����һ���������ݣ���һ��ɾ�����ݣ��Լ�������������
	scandata.value='#';   //����#����ASCII����Ŵ���
	Push(OPTR,scandata);  //���ʼ��'#'ѹ��ջ��
	printf("��������Ҫ����ı��ʽ���ԡ�#��Ϊ�����ַ�����\n");
	scandata.value=getchar();  //�����ʼ�����ݣ��������������ת������
	while(scandata.value!='#'||GetTop(OPTR).value!='#')
	{
		if(IsNum(scandata)==1)
		{
			Push(OPND,scandata);
			scandata.value=getchar();
		}
		else
			switch(Precede(GetTop(OPTR),scandata.value))
		{
			case '<' :  Push(OPTR,scandata); scandata.value=getchar();break;  //��ǰ��������ȼ�������һ��������򽫵�ǰ�����ѹ��ջ��

			case '=' :  Pop(OPTR,deldata);  scandata.value=getchar(); break;  //������������

			case '>' :  Pop(OPND,data2); Pop(OPND,data1);   //�Ȱ�װ�����ֵ�ջ��ǰ��������ȡ��
				        Push(OPND,Operate(data1,GetTop(OPTR),data2));  //��������������ѹ��ջ
						Pop(OPTR,deldata);  //�������ɾ��
		}
	}
	getchar();  //���ջس�
	printf("����Ϊ��%d\n",(GetTop(OPND).value)-48);
	DestoryStack(OPND);  DestoryStack(OPTR);  //�ݻ�ջ
}