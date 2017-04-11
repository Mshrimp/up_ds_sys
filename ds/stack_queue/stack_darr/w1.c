#include "stack.h"

#define ROW 10
#define COL 20

struct pos_t{
	int x;
	int y;
};

void show(char (*bg)[COL])
{
	int i;
	for (i = 0; i < ROW; i++)
	{
		puts(bg[i]);
	}
}

void getxy(char (*bg)[COL], char ch, struct pos_t *pos)
{
	int i, j;

	for (i = 0; i < ROW; i++)
	{
		for (j = 0; j < COL; j++)
		{
			if (bg[i][j] == ch)
			{
				pos->x = i;
				pos->y = j;
				return ;
			}
		}
	}
}
int main(void)
{
	int i;
	struct pos_t stat, end, next;
	STACK *handle = NULL;
	struct pos_t *cur = NULL;
	struct pos_t dir[4] = {
		{1, 0},//down
		{-1, 0},//up
		{0, 1},//right
		{0, -1}//left

	};
	char bg[ROW][COL] = {
		"#S#################",
		"#                 #",
		"################# #",
		"###       ####### #",
		"#   ## ###        #",
		"### #####  ########",
		"##     #   ###    #",
		"#####    ##### ## #",
		"##    ##       ## #",
		"#################E#",
	};

	handle = stack_create(sizeof(struct pos_t), 200);
	ERRP(handle == NULL, "stack_create", goto ERR1);

	system("clear");
	show(bg);

	getxy(bg, 'S', &stat);
	getxy(bg, 'E', &end);

	stack_push(&stat, handle);
	while(1)
	{
		printf("\033[1;1H");
		cur = stack_pop(handle);
		if (cur == NULL)
		{
			printf("no exit!\n");
			break;
		}
		if (cur->x == end.x && cur->y == end.y)
		{
			break;
		}
		bg[cur->x][cur->y] = '@';
		fflush(NULL);
		/*usleep(200000);*/
		show(bg);
		getchar();

		for (i = 0; i < 4; i++)
		{
			next.x = cur->x + dir[i].x;
			next.y = cur->y + dir[i].y;
			if (bg[next.x][next.y] == '#' || bg[next.x][next.y] == '@' || next.x < 0 || next.x > ROW - 1 || next.y < 0 || next.y > COL - 1)
			{
				continue;
			}
			stack_push(&next, handle);
		}
		free(cur);
	}
/*
 *    printf("stat->x = %d stat->y = %d\n", stat.x, stat.y);
 *
 *    printf("end->x = %d end->y = %d\n", end.x, end.y);
 */

	stack_destroy(handle);
	return 0;
ERR1:
	return -1;
}
