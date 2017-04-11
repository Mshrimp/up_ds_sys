#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//#define container_of(ptr)
#define container_of(ptr, type, member)   ((type *)(((char *)(ptr)) - ((size_t)(&(((type *)0)->member)))))
/*#define FRI_ADDRESS(ptr, type, member)   ((type *)(((void *)(ptr)) - ((unsigned long)(&(((type *)0)->member)))))*/


struct node_t{
	struct node_t *next;
	struct node_t *prev;
};

struct a_t{
	struct node_t sel;
	char name[128];
	int age;
};
struct b_t{
	int x;
	struct node_t sel;
	int y;
};
struct c_t{
	char s[128];
	int i;
	struct node_t sel;
	int j;
};

void add(struct node_t *new, struct node_t *head)
{
	new->next = head;
	new->prev = head->prev;
	head->prev->next = new;
	head->prev = new;

}
void test(struct node_t *head)
{
	struct a_t *ap = NULL;
	struct b_t *bp = NULL;
	struct c_t *cp = NULL;

	ap = container_of(head->next, struct a_t, sel);

	/*ap = (struct a_t *)(((void *)(head->next)) - ((unsigned long)(&(((struct a_t *)0)->sel))));*/

	printf("name = %s\n", ap->name);
	printf("age = %d\n", ap->age);
	bp = (struct b_t *)(((void *)(head->next->next)) - ((unsigned long)(&(((struct b_t *)0)->sel))));
	printf("x = %d y = %d\n", bp->x, bp->y);
	cp = (struct c_t *)(((void *)(head->next->next->next)) - ((unsigned long)(&(((struct c_t *)0)->sel))));
	printf("s = %s i = %d, j = %d\n", cp->s, cp->i, cp->j);
    /*
	 *printf("test = %p\n", &(((struct a_t *)0)->sel));
	 *printf("test = %d\n", &(((struct a_t *)0)->sel));
     */
	/*ap->sel = head->next;*/
}
int main(void)
{
	struct node_t head = {&head, &head};
	struct a_t a = {.name = "tom", .age = 18};
	struct b_t b = {.x = 3, .y = 5};
	struct c_t c = {.s = "hello", .i = 10, .j = 20};

	add(&a.sel, &head);
	add(&b.sel, &head);
	add(&c.sel, &head);

	test(&head);
    /*
	 *printf("a.sel = %d\n", *(int *)(((void *)(head.next)) - 4));
	 *printf("a.sel = %p\n", head.next);
	 *printf("a.sel = %p\n", &a.sel);
	 *printf("a.sel = %d\n", *(int *)(((void *)&a.sel) - 4));
     */
	return 0;
}
