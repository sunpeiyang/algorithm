/*
 * 汉诺塔问题
 * X Y Z 三个柱子， 在X上有1 2..n, n个圆盘，依次从小到大
 *将圆盘从X柱子 移到Z 柱子上，大圆盘不能再小圆盘上
 *
 * 思路：
 *      1、将 X上面的n-1个盘子 移到Y上
 *      2、将X最后一个盘子移到Z
 *      3、将Y上的n-1个盘子 通过X移到Z上 ，递归
 * */
#include <stdio.h>
#include <iostream>
#include <string>
using namespace std;

void move(char a, int n, char b)
{
    printf("将 %d 从%c 移到 %c 上\n", n, a, b);
    return;
}
void hanoi(int n, char x, char y, char z)
{
    if (n == 1)
    {
        move(x, 1, z);
        return;
    }
    hanoi(n - 1, x, z, y);
    move(x, n, z);
    hanoi(n - 1, y, x,  z);
}

int main()
{
    hanoi(3, 'X', 'Y', 'Z');
    return 0;
}
