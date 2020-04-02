#include<stdio.h>
#include<stdlib.h>
#define INIT_STACK_SIZE 100  //定义栈的初始分配量
#define STACKINCREMENT 10    //增加量
typedef struct
{
	int value;  //这里将数据类型定义为int
} Elemtype;   //定义数据类型
typedef struct
{
	Elemtype *base;
	Elemtype *top;
	int stacksize;   //栈的最大容量
}SqStack;   //定义栈

typedef short Status;  //定义状态值

Status CreateStack(SqStack &S)   //创建栈
{
	S.base=(Elemtype *)malloc(sizeof(Elemtype)*INIT_STACK_SIZE);
	if(NULL==S.base)  return 0;   //创建失败
	S.top=S.base;
	S.stacksize=INIT_STACK_SIZE;
	return 1;
}

Status DestoryStack(SqStack &S)  //摧毁栈
{
	if(NULL==S.base)  return 0;  //传入栈为空，返回值0
	free(S.base);
	S.base=NULL;
	S.top=NULL;
	S.stacksize=0;
	return 1;
}

Elemtype GetTop(SqStack S)  //取得栈顶元素
{
	return *(S.top-1);
}

Status Push(SqStack &S,Elemtype e)   //将e元素加入到栈顶
{
	if(NULL==S.base)   return 0;  //传入栈为空
	if(S.top-S.base>=S.stacksize)  //空间不足，进行空间增加
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

Status Pop(SqStack &S,Elemtype &e)  //弹出栈顶元素e,并取得e
{
	if(NULL==S.base)   return 0;  //传入栈为空
	e.value=(--S.top)->value;
	return 1;
}

Status IsNum(Elemtype e)
{
	if(e.value-48>=0&&e.value-48<=9)  //由于传入的数据是由字符转换为整型，‘0’的ASCII码序号为48
		return 1;  //传入元素为数字，返回1
	else
		return 0;  //传入元素不是数字，返回0
}

Elemtype Operate(Elemtype num1,Elemtype Operator,Elemtype num2)  //进行运算操作
{
	int i1,i2,i;
	Elemtype result;  //定义运算结果
	i1=num1.value-48;  //将字符的ASCII码转为数字
	i2=num2.value-48;
	switch(Operator.value)
	{
	case '+': i= i1+i2;break;
	case '-': i= i1-i2;break;
	case '*': i= i1*i2;break;
	case '/': i= i1/i2;break;
	}
	result.value=i+48;  //运算结果为整型，这里增加48是为了与ASCII码操作，实际数据应该减去48（48是'0'字符的ASCII码）
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
};  //定义算数运算符优先级，‘>’表示要进行运算操作，‘<’表示该运算符进行进栈操作，
    //‘=’表示消除当前运算符与上一个运算符操作，‘\0’表示当前运算符与前一个运算符不可能存在前后关系
    //竖排是上一运算符，横排是输入的当前运算符
char Precede(Elemtype e,char indata)  //e是上一运算符，indata是当前输入运算符
{
	short m,n;
	switch ((char)e.value)  //强制转换为字符型
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
	SqStack OPTR,OPND;  //建立两个栈，OPTR用来装运算符，OPND用来装数字
	OPTR.base=NULL;  OPND.base=NULL;
	OPTR.top=NULL;  OPND.top=NULL;
	OPTR.stacksize=0;   OPND.stacksize=0;  //初始化
	if(CreateStack(OPTR)!=1||CreateStack(OPND)!=1)
	{
		printf("初始化失败！");
		return;
	}
	Elemtype scandata,deldata,data1,data2;  //定义一个输入数据，和一个删除数据，以及两个计算数据
	scandata.value='#';   //将‘#’的ASCII码序号存入
	Push(OPTR,scandata);  //将最开始的'#'压入栈底
	printf("请输入需要运算的表达式（以‘#’为结束字符）：\n");
	scandata.value=getchar();  //输入最开始的数据，并把输入的数据转换整型
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
			case '<' :  Push(OPTR,scandata); scandata.value=getchar();break;  //当前运算符优先级大于上一运算符，则将当前运算符压入栈中

			case '=' :  Pop(OPTR,deldata);  scandata.value=getchar(); break;  //进行括号消除

			case '>' :  Pop(OPND,data2); Pop(OPND,data1);   //先把装有数字的栈的前两个数据取出
				        Push(OPND,Operate(data1,GetTop(OPTR),data2));  //将操作过的数据压入栈
						Pop(OPTR,deldata);  //将运算符删除
		}
	}
	getchar();  //吸收回车
	printf("其结果为：%d\n",(GetTop(OPND).value)-48);
	DestoryStack(OPND);  DestoryStack(OPTR);  //摧毁栈
}