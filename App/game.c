#include "game.h"

static char dirction; // 蛇前进方向
static unsigned char food_y; // 食物所在行
static unsigned char food_x; // 食物所在列
static unsigned char res_cell; // 剩余格子数
static unsigned char snake_len;  // 蛇的长度
static char snake_body_y[64]; // 蛇身体每个点的坐标
static char snake_body_x[64]; // 蛇身体每个点的坐标

void game_init()
{
	// 初始蛇位置
	// map[2] = 0x60;
	snake_body_x[0] = 3;
	snake_body_y[0] = 2;
	
	snake_body_x[1] = 2;
	snake_body_y[1] = 2;
	snake_len = 2;
	dirction = 'r';
	update_food();
	update_food();
}


// 更新食物坐标
void update_food()
{
	unsigned char i, j;
	unsigned char map[8];
	unsigned char pos = rand() % (64 - snake_len);
	for (i = 0; i < snake_len; i++) {
		map[snake_body_y[i]] |= (0x80 >> snake_body_x[i]);
	}
	for (i = 0; i < 8; i++) {
		if (map[i] == 0xFF)
			continue;
		for (j = 0; j < 8; j++) {
			if (pos == 0) { // food 位置找到
				food_y = i;
				food_x = j;
				return;
			}
			
			if ((map[i] & (0x80 >> j)) == 0)
				pos--;
		}
	}
}

// 当前状态地图 8x8
void create_map(unsigned char* map)
{
	unsigned char i = 0;
	map[food_y] |= (0x80 >> food_x); // 食物的位置
	for (i = 0; i < snake_len; i++) {
		map[snake_body_y[i]] |= (0x80 >> snake_body_x[i]);
	}
}

// 修改方向，不能直接掉头
void change_dir(unsigned char d)
{
	if (dirction == 'u' && d == 'd') return;
	if (dirction == 'd' && d == 'u') return;
	if (dirction == 'l' && d == 'r') return;
	if (dirction == 'r' && d == 'l') return;
	dirction = d;
}


// 蛇移动
void snake_move()
{
	unsigned char i = snake_len - 1;
	unsigned char tail_x = snake_body_x[i];
	unsigned char tail_y = snake_body_y[i];
	
	for (i = snake_len - 1; i > 0; i--) {
		snake_body_x[i] = snake_body_x[i-1];
		snake_body_y[i] = snake_body_y[i-1];
	}
	
	if (dirction == 'u') {
		snake_body_y[0] -= 1;
	} else if (dirction == 'd') {
		snake_body_y[0] += 1;
	} else if (dirction == 'l') {
		snake_body_x[0] -= 1;
	} else if (dirction == 'r') {
		snake_body_x[0] += 1;
	}
	
	// 如果吃到食物
	if (snake_body_y[0] == food_y && snake_body_x[0] == food_x) {
		snake_body_x[snake_len] = tail_x;
		snake_body_y[snake_len] = tail_y;
		snake_len++;
		update_food();
	}
	
}


unsigned int is_game_over() {
	unsigned int i = 0;
	// 如果碰到墙
	if (snake_body_x[0] >= 8 || snake_body_x[0] < 0 || snake_body_y[0] >= 8 || snake_body_y[0] < 0) {
		return 1;
	}
	// 如果碰到自己的身体
	for (i = 1; i < snake_len; i++) {
		if (snake_body_x[0] == snake_body_x[i] && snake_body_y[0] == snake_body_y[i]) {
			return 1;
		}
	}
	return 0;
}