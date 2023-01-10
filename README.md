# SnakeC51

51单片机上实现贪吃蛇小游戏

[!Watch the video](https://github.com/SherlockUnknowEn/SnakeC51/blob/main/ezgif-1-e72d609c69.gif)

### 游戏逻辑

单片机LED阵列一共8x8, `unsigned char map[8]` 记录地图数据，`unsigned char`数据类型8 bits，`map[i]` 中第`j`个bit 代表 第`i`行第`j`列是否被点亮

1. 单片机主函数中，不断刷新LED点阵，更新蛇的位置和食物的位置

```
while(1)
{		
    if (is_game_over()) { 
        light_all();
    } else {
        show_map(); // 根据蛇位置和食物的位置，点亮矩阵屏
        k = keyboard(); // 尝试获取用户输入（蛇前进方向的改变）
        dir_scan(k);
    }
}	

```

2. 使用`snake_body_x[64]`和`snake_body_y[64]`数组存储蛇的身体，`i = 0`位置为蛇头，单片机定时器中断函数中，每500ms移动蛇的位置，蛇头根据按键输入向前后左右其中一个方向移动，蛇后一节躯体向前一节躯体的位置移动，即

```
    snake_body_x[0] = ? // 根据按键输入方向移动
    snake_body_y[0] = ? // 根据按键输入方向移动
    for (int i = 1; i < snake_len; i++) {
        snake_body_x[i] = snake_body_x[i-1];
        snake_body_y[i] = snake_body_y[i-1];
    }
```

3. 如果蛇吃到食物，长度增加（蛇尾增加一节），刷新下一次食物的位置

```
// 如果吃到食物
if (snake_body_y[0] == food_y && snake_body_x[0] == food_x) {
    snake_body_x[snake_len] = tail_x;
    snake_body_y[snake_len] = tail_y;
    snake_len++;
    update_food();
}
```

4. 食物的位置刷新方法：获取当前未点亮的LED序号，如 [0, 3, 5, 7, 9, 14] 6栈未点亮，在 [0, 5]中取随机数，点亮其中一盏作为食物

```
unsigned char pos = rand() % (64 - snake_len);
// 找到第 pos 个未被点亮的LED作为食物的位置
```

5. 游戏结束判定，蛇碰到墙壁或者蛇头碰到自己的身体，游戏结束
```
unsigned int is_game_over() {
    unsigned int i = 0;
    // 如果碰到墙
    if (snake_body_x[0] >= 8 || snake_body_x[0] < 0 || snake_body_y[0] >= 8 || snake_body_y[0] < 0) {
        return 1;
    }

    // 如果蛇头碰到自己的身体
    for (i = 1; i < snake_len; i++) {
        if (snake_body_x[0] == snake_body_x[i] && snake_body_y[0] == snake_body_y[i]) {
            return 1;
        }
    }
    return 0;
}
```
