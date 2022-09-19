/*
* 约瑟夫环问题
（1）问题描述
设有编号为 1,2,…,n 的 n（n＞0）个人围成一个圈，每个人持有一个密码 m。从第一个人开始报数，报到 m 时停止报数，
报 m 的人出圈，再从他的下一个人起重新报数，报到 m 时停止报数，报 m 的出圈，……，如此下去，直到所有人全部出圈为止。
当任意给定 n 和 m 后，设计算法求 n 个人出圈的次序。
（2）基本要求
-  建立模型，确定存储结构。
-  对任意 n 个人，密码为 m，实现约瑟夫环问题。
-  出圈的顺序可以依次输出，也可以用一个数组存储。
（3）思考：
-  采用顺序存储结构如何实现约瑟夫环问题？
-  如果每个人持有的密码不同，应如何实现约瑟夫环问题？
*/


#include <stdio.h>
#include <stdlib.h>

//建立结点
typedef struct node
{
	int data;
	struct node *next;
}node;

int main(int argc, char *argv[])
{
	node *head = NULL;
	head = (node*)malloc(sizeof(node));
	head->data = 1;
	head->next = NULL;
	node *p = head;
	//尾插法建造链表
	int i,n,k;
	scanf("%d",&n);
	scanf("%d",&k);
	//针对约瑟夫问题可以使用for循环来建立链表
	for(i=2;i<=n;i++)
	{
		node *q = NULL;
		q = (node*)malloc(sizeof(node));
		q->data = i;
		q->next = NULL;
		p->next = q;
		p = q;
		q = q->next;
	}
	p->next = head;
	node* q = head;

	//以上代码把数据为1~n的循环链表建立成功

	//约瑟夫问题：
	int cnt = 1;
	node *t = p;
	t = head;
    int x = 0;
    //这里引入x的意义是在于方便对比循环次数
	while(x != n)
	{
		if(cnt!=k)
		{
			if(t->data!=0)
			{
				cnt++;
			}
			t = t->next;
		}
		else
		{
			//第一次遍历时遇到满足条件的元素就输出，然后赋值为0
			if(t->data!=0)
			{
				cnt = 1;
				x++;
				printf("%d",t->data);
				if(x != n)
                    printf(" ");
				t->data = 0;
			}
			t = t->next;
		}
	}
		t = head;
		x = 0;
        //注意循环条件不能是while(t!=NULL)
		while(x != n)
		{
			t = t->next;
			free(head);
			x++;
			head = t;
		}
		return 0;
}