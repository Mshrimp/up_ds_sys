#ifndef __QUEUE_H__
#define __QUEUE_H__

struct node_t {
    void *data;
    struct node_t *next;
    struct node_t *prev;
};

typedef struct queue_t {
    struct node_t head;
    int size;
    int max;
    int num;
}QUEUE;

#define ERR(con, ret)       do                  \
                            {                   \
                                if (con)        \
                                {               \
                                    ret;        \
                                }               \
                            } while (0)

typedef void (queue_op_t)(const void *);

QUEUE *queue_create(int size, int max);
void queue_destroy(QUEUE *handle, queue_op_t *op);
void queue_clean(QUEUE *handle, queue_op_t *op);
int queue_isempty(QUEUE *handle);
int queue_isfull(QUEUE *handle);
int queue_en(void *data, QUEUE *handle);
void *queue_de(QUEUE *handle, queue_op_t *op);
void queue_travel(queue_op_t *op, QUEUE *handle);

#endif /* __QUEUE_H__ */
