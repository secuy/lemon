#include<stdio.h>
#include<stdlib.h>
typedef struct {
	char value;
}ElementType;
typedef struct Node{
	Node *prior,*next;
	ElementType data;
	short freq;
}LNode,*LinkList;
typedef short Status;  //状态值，1代表正常，<=0代表各种错误
Status CreateLinkList(LinkList &L)  //创建双向循环链表
{
	if(L==NULL)
	{
		L=(LinkList)malloc(sizeof(LNode));
		if(L==NULL)  return -1;  //动态存储空间分配失败
		L->prior=L;
		L->next=L;  //将前驱与后继指针指向自己
		L->freq=0;  //访问频率初始化为0
		return 1;  //创建成功，返回值为1
	}
	return 0;  //引入的L有头结点
}
Status IsEmpty(LinkList L)  //判断链表是否为空（链表只有一个头结点）
{
	if(L==NULL)
		return -1;  //L头结点不存在，返回值为-1
	if(L->next==L && L->prior==L)
		return 1;  //L为空，返回值1
	else
		return 0;  //L不为空，返回值为0
}
Status InsertDataAtTail(LinkList &L,LNode *pNode) //尾插法在链表中插入元素
{
	if(L==NULL||pNode==NULL)
		return 0;  //插入的链表头结点不存在或者插入的元素指针为空，返回值为0
	L->prior->next=pNode;  //将最后一个元素的后继指针指向插入元素
	pNode->prior=L->prior;  //插入元素的前驱指针指向最后一个元素
	pNode->next=L;  //插入元素的后继指针指向头结点
	L->prior=pNode;  //头结点的前驱指针指向最后一个元素
	pNode->freq=0;
	return 1;
}
Status DeleteDataFromList(LinkList &L,LNode *pNode)  //删除元素
{
	if(L==NULL||pNode==NULL||pNode==L) //删除的链表头结点不存在，或者删除元素地址为空，或者删除元素地址为头结点则删除失败
		return 0;
	LNode *p=L->next;
	while(p!=L)  //检索pNode指针元素
	{
		if(p==pNode)  break;  //当找到时退出循环
		p=p->next;  //进行下一个检索
	}
	if(p==L)  return -1;  //没有检索到需要删除的元素，失败，返回值为-1
	p->prior->next=p->next;
	p->next->prior=p->prior;  //进行删除操作
	return 1;
}
Status InsertDataAtElemHead(LinkList &L,LNode*pNode,LNode*eNode)  //在某一元素的前面插入元素,pNode为插入元素，eNode为某一元素
{
	if(L==NULL||pNode==NULL)
		return 0;
	eNode->prior->next=pNode;  //将插入位置的上一个元素的后继指针指向插入元素
	pNode->prior=eNode->prior;   //插入元素前驱指针指向插入位置的上一个元素
	eNode->prior=pNode;   //后一个元素的前驱指针指向插入元素
	pNode->next=eNode;   //插入元素的后继指针指向后一个元素
	return 1;
}
Status LocateLinkList(LinkList &L,char x)  //查找到存在x后，进行调整，返回1；查不到则返回0
{
	LNode *p=L->next,*s=NULL;
	while(p!=L)  //p用来遍历整个双向循环链表
	{ 
		if(p->data.value==x)
		{
			(p->freq)++;
			s=p;  //s代表记录到查找的位置
			LNode* del=p->next;   //将要删除的元素记录下来
			p=p->next;
			for(LNode *q=L->next;q!=L;q=q->next)  //q用来访问频度比较时的遍历
				if((s->freq)>(q->freq))   //访问频度比较，并交换位置
				{
					DeleteDataFromList(L,del->prior);
					InsertDataAtElemHead(L,s,q);
					break;
				}
		}
		else
			p=p->next;
	}
	if(s==NULL)
		return 0;  //如果s为空，则查找不到元素x，失败返回0
	else
		return 1;   //如果s不为空，则查找到了元素x，并进行了排序，返回值1
}
Status ClearLinkList(LinkList &L)   //释放双向循环链表的空间
{
	if(L==NULL)  return 0;  //传入L不存在，失败
	LNode *p=L->next,*q=NULL;
	while(q!=L)  //进行除头结点外的结点循环释放空间
	{
		q=p->next;
		free(p);
		p=q;
	}
	free(L);  //释放头结点L的空间
	L=NULL;
	p=NULL;
	q=NULL;   //将L,p与q的指针赋值为空
	return 1;
}
Status PrintLinkList(LinkList &L)   //打印链表
{
	if(IsEmpty(L)!=0)  return 0;  //传入链表不存在或者为空，失败
	LNode *p=L->next;
	short num=1;
	while(p!=L)
	{
		printf("第%d个结点内容为:%c,访问频率为%d\n",num,p->data.value,p->freq);
		num++;
		p=p->next;
	}
	return 1;
}

int main()
{
	LinkList L=NULL;
	short num,i;
	if(CreateLinkList(L)!=1)
	{
		printf("创建双向循环链表失败！");
	    return 0;
	}
	else
		printf("创建双向循环链表成功！");
	printf("请输入链表长度:");
	scanf("%d",&num);
	getchar();
	for(i=1;i<=num;i++)
	{
		printf("请输入第%d个数据（共%d个）:\n",i,num);
		LNode*p=(LNode*)malloc(sizeof(LNode));
		if(p==NULL)  return 0;  //分配空间失败
		scanf("%c",&p->data.value);
		getchar();
		if(InsertDataAtTail(L,p)!=1)
			return 0;
	}
	printf("请输入要访问链表次数:");
	scanf("%d",&num);
	getchar();
	char x;
	for(i=1;i<=num;i++)
	{
		printf("请输入需要访问的第%d个数据（共%d个）:",i,num);
		scanf("%c",&x);
		getchar();
		if(LocateLinkList(L,x)!=1)
			return 0;  //没有查找到元素，查找失败
	}
	printf("访问完成！\n");
	PrintLinkList(L);  //打印链表
	ClearLinkList(L);  //释放内存空间
	return 1;
}
