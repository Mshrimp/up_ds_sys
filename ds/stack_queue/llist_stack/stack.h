#ifndef __STACK_H__
#define __STACK_H__

struct node_t {
    void *data;
    struct node_t *next;
    struct node_t *prev;
};

typedef struct stack_t {
    struct node_t head;
    int size;
    int max;
    int num;
}STACK;

#define ERR(con, ret)       do                  \
                            {                   \
                                if (con)        \
                                {               \
                                    ret;        \
                                }               \
                            } while (0)

#define MAGIC       "STACK"

typedef void (stack_op_t)(const void *);

STACK *stack_create(int size, int max);
void stack_destroy(STACK *handle, stack_op_t *op);
void stack_clean(STACK *handle, stack_op_t *op);
int stack_isempty(STACK *handle);
int stack_isfull(STACK *handle);
int stack_push(void *data, STACK *handle);
void *stack_pop(STACK *handle, stack_op_t *op);
void stack_travel(stack_op_t *op, STACK *handle);
int stack_store(const char *path, STACK *handle);
STACK *stack_load(const char *path);
int stack_resize(int _max, STACK *handle);

#endif /* __STACK_H__ */
