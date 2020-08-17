#include <stdio.h>
#include "list.h"

struct node {
	int val;
	struct list_head list;
};

//test INIT_LIST_HEAD
//test list_for_each
int test_list_for_each()
{
	struct list_head head, *plist;
	struct node a, b;

	a.val = 2;
	b.val = 3;

	INIT_LIST_HEAD(&head); //相当于&head->prev = &head, head->next = &head;
	list_add(&a.list, &head);
	list_add(&b.list, &head);

	list_for_each(plist, &head) {
			struct node *pnode = list_entry(plist, struct node, list);
			printf("%s val = %d\n", __func__, pnode->val);
	}
	printf("\n");

	return 0;
}

//test LIST_HEAD & list_for_each_entry
//test list_add
int test_list_add()
{
	LIST_HEAD(head);//定义一个链表表头，相当于 struct list_head head = {&head,  &head} ;
	struct node a, b;//定义具体元素实体
	struct node *pnode = NULL;//元素指针

	a.val = 2;
	b.val = 3;

	list_add(&a.list, &head);//将元素a追加到head链表末尾
	list_add(&b.list, &head);//将元素b追加到head链表末尾

	list_for_each_entry(pnode, &head, list) {
		printf("%s val = %d\n", __func__, pnode->val);
	}
	printf("\n");


	return 0;
}
//test list_add_tail
int test_list_add_tail1()
{
	LIST_HEAD(head);//定义一个链表表头，相当于 struct list_head head = {&head,  &head} ;

	struct list_head *plist = &head;
	struct node a, b;//定义具体元素实体
	struct node *pnode = NULL;//元素指针

	a.val = 2;
	b.val = 3;

	list_add_tail(&a.list, &head);//将元素a追加到head链表之前
	list_add_tail(&b.list, &head);//将元素a追加到head链表之前

	pnode = list_entry(plist->next, struct node, list);
	printf("%s val = %d\n", __func__, pnode->val);

	pnode = list_entry(plist->next->next, struct node, list);
	printf("%s val = %d\n", __func__, pnode->val);

	printf("\n");


	return 0;
}

//test list_add_tail
int test_list_add_tail2()
{
	LIST_HEAD(head);//定义一个链表表头，相当于 struct list_head head = {&head,  &head} ;

	struct list_head *plist = &head;
	struct node a, b;//定义具体元素实体
	struct node *pnode = NULL;//元素指针

	a.val = 2;
	b.val = 3;

	list_add_tail(&a.list, &head);//将元素a追加到head链表之前
	list_add_tail(&b.list, &head);//将元素b追加到head链表之前

	list_for_each_entry(pnode, &head, list) {
		printf("%s val = %d\n", __func__, pnode->val);
	}
	printf("\n");


	return 0;
}

//test list_del
int test_list_del()
{
	LIST_HEAD(head);//定义一个链表表头，相当于 struct list_head head = {&head,  &head} ;
	struct node a, b, c;//定义具体元素实体
	struct node *pnode = NULL;//元素指针

	a.val = 2;
	b.val = 3;
	c.val = 4;

	list_add(&a.list, &head);//将元素a追加到head链表末尾
	list_add(&b.list, &head);//将元素b追加到head链表末尾
	list_add(&c.list, &head);//将元素b追加到head链表末尾

	list_for_each_entry(pnode, &head, list) {
		printf("%s before del: val = %d\n", __func__, pnode->val);
	}
	list_del(&b.list);
	list_for_each_entry(pnode, &head, list) {
		printf("%s after del: val = %d\n", __func__, pnode->val);
	}
	printf("\n");

	return 0;
}

// test list_for_each_entry_safe
int test_list_for_each_entry_safe()
{
	LIST_HEAD(head);//定义一个链表表头，相当于 struct list_head head = {&head,  &head} ;
	struct node a, b;//定义具体元素实体
	struct node *pnode = NULL;//元素指针
	struct node *temp_node = NULL;//元素指针
	a.val = 2;
	b.val = 3;

	list_add(&a.list, &head);//将元素a追加到head链表末尾
	list_add(&b.list, &head);//将元素b追加到head链表末尾

	list_for_each_entry(pnode, &head, list) {
		printf("%s before del: val = %d\n", __func__, pnode->val);
	}

	list_for_each_entry_safe(pnode, temp_node, &head, list) {
		list_del(&pnode->list);
		// kfree(pnode); //如果pnode曾经使用kmalloc申请空间，这里应使用kfree释放掉pnode
	}

	// 删除之后，链表应当无数据
	list_for_each_entry(pnode, &head, list) {
		printf("%s after del: val = %d\n", __func__, pnode->val);
	}
	printf("\n");


	return 0;
}

int main()
{
	test_list_for_each();
	test_list_add();
	test_list_add_tail1();
	test_list_add_tail2();
	test_list_del();
	test_list_for_each_entry_safe();
	return 0;
}
