#include <stdio.h>
#include "list.h"

struct int_node {
	int val;
	struct list_head list;
};


//test INIT_LIST_HEAD
int test1()
{
	struct list_head int_list, *plist;
	struct int_node a, b;

	a.val = 2;
	b.val = 3;

	INIT_LIST_HEAD(&int_list);
	list_add(&a.list, &int_list);
	list_add(&b.list, &int_list);

	list_for_each(plist, &int_list) {
			struct int_node *node = list_entry(plist, struct int_node, list);
			printf("val = %d\n", node->val);
	}

	return 0;
}

//test LIST_HEAD & list_for_each_entry
int test2()
{
	LIST_HEAD(int_list);//定义一个链表表头，相当于 struct list_head int_list = {&int_list,  &int_list} ;
	struct int_node a, b;//定义具体元素实体
	struct int_node *pnode = NULL;//元素指针

	a.val = 2;
	b.val = 3;

	list_add(&a.list, &int_list);//将元素a追加到int_list链表末尾
	list_add(&b.list, &int_list);//将元素b追加到int_list链表末尾

	list_for_each_entry(pnode, &int_list, list) {
		printf("val = %d\n", pnode->val);
	}

	return 0;
}

//test list_del
int test3()
{
	LIST_HEAD(int_list);//定义一个链表表头，相当于 struct list_head int_list = {&int_list,  &int_list} ;
	struct int_node a, b;//定义具体元素实体
	struct int_node *pnode = NULL;//元素指针

	a.val = 2;
	b.val = 3;

	list_add(&a.list, &int_list);//将元素a追加到int_list链表末尾
	list_add(&b.list, &int_list);//将元素b追加到int_list链表末尾
	list_del(&b.list);

	list_for_each_entry(pnode, &int_list, list) {
		printf("val = %d\n", pnode->val);
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
