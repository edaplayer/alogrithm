#include <stdio.h>
#include "list.h"

struct node {
	int val;
	struct list_head list;
};


//test INIT_LIST_HEAD
//test list_for_each
int test1()
{
	struct list_head head, *plist;
	struct node a, b;

	a.val = 2;
	b.val = 3;

	INIT_LIST_HEAD(&head); //相当于&head->prev = &head, head->next = &head;
	list_add(&a.list, &head);
	list_add(&b.list, &head);

	list_for_each(plist, &head) {
			struct node *node = list_entry(plist, struct node, list);
			printf("test1 val = %d\n", node->val);
	}

	return 0;
}

//test LIST_HEAD & list_for_each_entry
//test list_add
int test2()
{
	LIST_HEAD(head);//定义一个链表表头，相当于 struct list_head head = {&head,  &head} ;
	struct node a, b;//定义具体元素实体
	struct node *pnode = NULL;//元素指针

	a.val = 2;
	b.val = 3;

	list_add(&a.list, &head);//将元素a追加到head链表末尾
	list_add(&b.list, &head);//将元素b追加到head链表末尾

	list_for_each_entry(pnode, &head, list) {
		printf("test2 val = %d\n", pnode->val);
	}

	return 0;
}

//test list_del
int test3()
{
	LIST_HEAD(head);//定义一个链表表头，相当于 struct list_head head = {&head,  &head} ;
	struct node a, b;//定义具体元素实体
	struct node *pnode = NULL;//元素指针

	a.val = 2;
	b.val = 3;

	list_add(&a.list, &head);//将元素a追加到head链表末尾
	list_add(&b.list, &head);//将元素b追加到head链表末尾
	list_del(&b.list);

	list_for_each_entry(pnode, &head, list) {
		printf("test3 val = %d\n", pnode->val);
	}

	return 0;
}

int main()
{
	test1();
	test2();
	test3();
	return 0;
}
