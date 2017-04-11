#include <stdio.h>

//链表节点信息
struct node_t{
	int data;//数据域 保存用户输入数据
	struct node_t *next;//指针域 用来保存下一个节点地址
};
int main(void)
{
	struct node_t head = {0, NULL};//头节点
	struct node_t a = {10,NULL}, d = {40, NULL}, b = {20, NULL}, c = {30, NULL};

	head.next = &a;
	a.next = &b;
	b.next = &c;

	printf("head.next->data = %d\n", head.next->data);
	printf("a -> b = %d\n", a.next->data);
	printf("a -> c = %d\n", a.next->next->data);
	//printf("a = %d %p\n", a, &a);
	//printf("b = %d %p\n", b, &b);
	//printf("c = %d %p\n", c, &c);

	//printf("a -> b = %d\n", *(&a - 1));
	return 0;
}
