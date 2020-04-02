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
typedef short Status;  //״ֵ̬��1����������<=0������ִ���
Status CreateLinkList(LinkList &L)  //����˫��ѭ������
{
	if(L==NULL)
	{
		L=(LinkList)malloc(sizeof(LNode));
		if(L==NULL)  return -1;  //��̬�洢�ռ����ʧ��
		L->prior=L;
		L->next=L;  //��ǰ������ָ��ָ���Լ�
		L->freq=0;  //����Ƶ�ʳ�ʼ��Ϊ0
		return 1;  //�����ɹ�������ֵΪ1
	}
	return 0;  //�����L��ͷ���
}
Status IsEmpty(LinkList L)  //�ж������Ƿ�Ϊ�գ�����ֻ��һ��ͷ��㣩
{
	if(L==NULL)
		return -1;  //Lͷ��㲻���ڣ�����ֵΪ-1
	if(L->next==L && L->prior==L)
		return 1;  //LΪ�գ�����ֵ1
	else
		return 0;  //L��Ϊ�գ�����ֵΪ0
}
Status InsertDataAtTail(LinkList &L,LNode *pNode) //β�巨�������в���Ԫ��
{
	if(L==NULL||pNode==NULL)
		return 0;  //���������ͷ��㲻���ڻ��߲����Ԫ��ָ��Ϊ�գ�����ֵΪ0
	L->prior->next=pNode;  //�����һ��Ԫ�صĺ��ָ��ָ�����Ԫ��
	pNode->prior=L->prior;  //����Ԫ�ص�ǰ��ָ��ָ�����һ��Ԫ��
	pNode->next=L;  //����Ԫ�صĺ��ָ��ָ��ͷ���
	L->prior=pNode;  //ͷ����ǰ��ָ��ָ�����һ��Ԫ��
	pNode->freq=0;
	return 1;
}
Status DeleteDataFromList(LinkList &L,LNode *pNode)  //ɾ��Ԫ��
{
	if(L==NULL||pNode==NULL||pNode==L) //ɾ��������ͷ��㲻���ڣ�����ɾ��Ԫ�ص�ַΪ�գ�����ɾ��Ԫ�ص�ַΪͷ�����ɾ��ʧ��
		return 0;
	LNode *p=L->next;
	while(p!=L)  //����pNodeָ��Ԫ��
	{
		if(p==pNode)  break;  //���ҵ�ʱ�˳�ѭ��
		p=p->next;  //������һ������
	}
	if(p==L)  return -1;  //û�м�������Ҫɾ����Ԫ�أ�ʧ�ܣ�����ֵΪ-1
	p->prior->next=p->next;
	p->next->prior=p->prior;  //����ɾ������
	return 1;
}
Status InsertDataAtElemHead(LinkList &L,LNode*pNode,LNode*eNode)  //��ĳһԪ�ص�ǰ�����Ԫ��,pNodeΪ����Ԫ�أ�eNodeΪĳһԪ��
{
	if(L==NULL||pNode==NULL)
		return 0;
	eNode->prior->next=pNode;  //������λ�õ���һ��Ԫ�صĺ��ָ��ָ�����Ԫ��
	pNode->prior=eNode->prior;   //����Ԫ��ǰ��ָ��ָ�����λ�õ���һ��Ԫ��
	eNode->prior=pNode;   //��һ��Ԫ�ص�ǰ��ָ��ָ�����Ԫ��
	pNode->next=eNode;   //����Ԫ�صĺ��ָ��ָ���һ��Ԫ��
	return 1;
}
Status LocateLinkList(LinkList &L,char x)  //���ҵ�����x�󣬽��е���������1���鲻���򷵻�0
{
	LNode *p=L->next,*s=NULL;
	while(p!=L)  //p������������˫��ѭ������
	{ 
		if(p->data.value==x)
		{
			(p->freq)++;
			s=p;  //s�����¼�����ҵ�λ��
			LNode* del=p->next;   //��Ҫɾ����Ԫ�ؼ�¼����
			p=p->next;
			for(LNode *q=L->next;q!=L;q=q->next)  //q��������Ƶ�ȱȽ�ʱ�ı���
				if((s->freq)>(q->freq))   //����Ƶ�ȱȽϣ�������λ��
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
		return 0;  //���sΪ�գ�����Ҳ���Ԫ��x��ʧ�ܷ���0
	else
		return 1;   //���s��Ϊ�գ�����ҵ���Ԫ��x�������������򣬷���ֵ1
}
Status ClearLinkList(LinkList &L)   //�ͷ�˫��ѭ������Ŀռ�
{
	if(L==NULL)  return 0;  //����L�����ڣ�ʧ��
	LNode *p=L->next,*q=NULL;
	while(q!=L)  //���г�ͷ�����Ľ��ѭ���ͷſռ�
	{
		q=p->next;
		free(p);
		p=q;
	}
	free(L);  //�ͷ�ͷ���L�Ŀռ�
	L=NULL;
	p=NULL;
	q=NULL;   //��L,p��q��ָ�븳ֵΪ��
	return 1;
}
Status PrintLinkList(LinkList &L)   //��ӡ����
{
	if(IsEmpty(L)!=0)  return 0;  //�����������ڻ���Ϊ�գ�ʧ��
	LNode *p=L->next;
	short num=1;
	while(p!=L)
	{
		printf("��%d���������Ϊ:%c,����Ƶ��Ϊ%d\n",num,p->data.value,p->freq);
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
		printf("����˫��ѭ������ʧ�ܣ�");
	    return 0;
	}
	else
		printf("����˫��ѭ������ɹ���");
	printf("������������:");
	scanf("%d",&num);
	getchar();
	for(i=1;i<=num;i++)
	{
		printf("�������%d�����ݣ���%d����:\n",i,num);
		LNode*p=(LNode*)malloc(sizeof(LNode));
		if(p==NULL)  return 0;  //����ռ�ʧ��
		scanf("%c",&p->data.value);
		getchar();
		if(InsertDataAtTail(L,p)!=1)
			return 0;
	}
	printf("������Ҫ�����������:");
	scanf("%d",&num);
	getchar();
	char x;
	for(i=1;i<=num;i++)
	{
		printf("��������Ҫ���ʵĵ�%d�����ݣ���%d����:",i,num);
		scanf("%c",&x);
		getchar();
		if(LocateLinkList(L,x)!=1)
			return 0;  //û�в��ҵ�Ԫ�أ�����ʧ��
	}
	printf("������ɣ�\n");
	PrintLinkList(L);  //��ӡ����
	ClearLinkList(L);  //�ͷ��ڴ�ռ�
	return 1;
}
