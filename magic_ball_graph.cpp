#include <iostream>
#include <iomanip>
#include <conio.h>
#include "magic_ball.h"
#include "cmd_console_tools.h"
#include <Windows.h>

using namespace std;

/*------------------------------ 图形区----------------------------------*/
void set_cmd(int r)
{
	cct_cls();
	cct_setfontsize("新宋体", 32);
	cct_setconsoleborder(40, r + 6, 40, 1000);
	cout << "屏幕：" << 6 + r << "行" << 40 << "列 ";
}

void reset_cmd()
{
	cct_setfontsize("新宋体", 16);
	cct_setconsoleborder(128, 30, 150, 1000);
}

void print_canvas(int(*s)[10], int r, int c, int grid, int speed)
{
	int m;
	if (speed) {
		m = 0;
	}
	else {
		m = 20;
	}
	cct_setcolor(15, 0);
	cct_gotoxy(0, 1);
	cout << "╔";
	for (int i = 1; i < c; i++) {
		Sleep(m);
		if (grid) {
			cout << "═╦";
		}
		else {
			cout << "═";
		}
	}
	cout << "═╗" << endl;

	for (int i = 1; i <= r; i++) {
		for (int j = 0; j <= c + 1; j++) {
			if (j == 0) {
				cct_setcolor(15, 0);
				cout << "║";
				if (grid) {
					for (int w = 1; w < c; w++) {
						cout << "  ║";
					}
					cout << "  ";
				}
				else {
					cct_setcolor(0);
					cout << setfill(' ') << setw(2 * c) << ' ';
				}
				cct_setcolor(15, 0);
				cout << "║";
				Sleep(m);
			}
		}
		cout << endl;
		if (i != r && grid) {
			for (int j = 0; j <= 2 * c; j++) {
				if (j == 0) {
					cout << "╠";
				}
				else if (j == 2 * c) {
					cout << "╣";
				}
				else if (j % 2 == 0) {
					cout << "╬";
				}
				else {
					cout << "═";
				}
			}
			cout << endl;
		}
	}
	cct_setcolor(15, 0);
	cout << "╚";
	for (int i = 1; i < c; i++) {
		Sleep(m);
		if (grid) {
			cout << "═╩";
		}
		else {
			cout << "═";
		}
	}
	cout << "═╝" << endl;
	cct_setcolor(0);
}

void print_circle(int(*s)[10], int r, int c, int grid, int(*h)[10], int speed, int option)
{
	int m = 5;
	if (speed) {
		m = 0;
	}
	else {
		m = 5;
	}
	int color[10] = { -1, 6, 7, 8, 9, 10, 11, 12, 13, 14 };
	if (grid) {
		for (int i = 1; i <= r; i++) {
			cct_gotoxy(0, 2 * i);
			for (int j = 1; j <= c; j++) {
				cct_setcolor(color[s[i][j]], 0);
				int x, y;
				cct_getxy(x, y);
				cct_gotoxy(x + 2, y);
				if (h[i][j] == 1) {
					cout << "●"; // 
				}
				else {
					cout << "○"; // ●
				}
				if (option != 9) {
					Sleep(5);
				}
			}
			cout << endl;
			cct_setcolor(0);
		}
	}
	else {
		for (int i = 1; i <= r; i++) {
			cct_gotoxy(2, 1 + i);
			for (int j = 1; j <= c; j++) {
				cct_setcolor(color[s[i][j]], 0);
				if (h[i][j] == 1) {
					cout << "●"; // 
				}
				else {
					cout << "○"; // ●
				}
				Sleep(m);
			}
			cout << endl;
			cct_setcolor(0);
		}
	}
}

void remove_circle(int(*s)[10], int r, int c, int(*h)[10])
{
	// 通过反复尝试找到了终于可以证明demo是横向一个一个扫描消除的
	int x, y;
	int m = 200;
	int color[10] = { -1, 6, 7, 8, 9, 10, 11, 12, 13, 14 };
	for (int i = 1; i <= r; i++) {
		cct_gotoxy(0, 2 * i);
		for (int j = 1; j <= c; j++) {
			cct_setcolor(color[s[i][j]], 0);
			cct_getxy(x, y);
			cct_gotoxy(x + 2, y);
			if (h[i][j] == 1) {
				cout << "●"; // ● ¤ ◎
				cct_gotoxy(x + 2, y);
				Sleep(m / 2);
				cout << "○"; // ● ¤ ◎
				cct_gotoxy(x + 2, y);
				Sleep(m / 2);
				cout << "¤"; // ● ¤ ◎
				cct_gotoxy(x + 2, y);
				Sleep(m / 2);
				cout << "○"; // ● ¤ ◎
				cct_gotoxy(x + 2, y);
				Sleep(m / 2);
				cout << "¤"; // ● ¤ ◎
				cct_setcolor(15, 0);
				cct_gotoxy(x + 2, y);
				cout << "  ";
			}
			else {
				cct_gotoxy(x + 4, y);
			}
		}
	}
	clear_instrcution(r);
}

void falling_down(int(*s)[10], int r, int c, int(*h)[10])
{
	int x, y, w;
	int lie, hang = 2 * r;
	int helper_down; // 已经下落的数量
	int already_up = 2 * r; // 最近一次下落的坐标
	int already_bottom = 2 * r; // 最后一次到底部的纵坐标 和上面的不一样
	int step = 0; // 需要下降的高差
	int m = 10;
	int color[10] = { -1, 6, 7, 8, 9, 10, 11, 12, 13, 14 };
	cct_gotoxy(1, 2 * r);
	for (int j = 1; j <= c; j++) {
		already_up = 2 * r;
		already_bottom = 2 * r;
		helper_down = 0;
		lie = j * 4 - 2;
		cct_gotoxy(lie, 2 * r); //到达底部往上遍历
		for (int i = r; i > 0; i--) {
			if (h[i][j] == 1) {
				for (w = i; w > 0; w--) {
					if (h[w][j] == 1) {
						step++;
					}
					else {
						break;
					}
				}
				// 此时w是下移的彩球序号
				hang = w * 2 + 1;
				already_up = 2 * w;
				for (int step_i = 1; step_i < 10; step++) {
					if (hang < already_bottom && hang > 1) {
						lan(s, j, w, lie, hang, helper_down);
						hang += 2;
						helper_down = 1;
					}
					else {
						cct_getxy(x, y);
						already_bottom = min(y, already_bottom);
						break;
					}
				}
			}
			else if (helper_down) {
				hang = i * 2 + 1;
				already_up = i * 2;
				for (int step_i = 1; step_i < 10; step++) {
					if (hang < already_bottom && hang > 1) {
						lan(s, j, i, lie, hang, helper_down);
						hang += 2;
					}
					else {
						cct_getxy(x, y);
						already_bottom = min(y, already_bottom);
						break;
					}
				}
			}
			else {
				already_bottom -= 2;
			}
			i = min(i, already_up / 2);
		}
	}
	clear_instrcution(r);
}

void lan(int(*s)[10], int j, int w, int lie, int hang, int helper_down)
{
	int m = 5;
	int color[10] = { -1, 6, 7, 8, 9, 10, 11, 12, 13, 14 };
	cct_setcolor(color[s[w][j]], 0);
	cct_gotoxy(lie, hang);
	cout << "○";
	Sleep(m);
	if (hang - 1 > 0) {
		cct_setcolor(15, 0);
		cct_gotoxy(lie, hang - 1);
		cout << "  ";
		Sleep(m);
	}

	cct_setcolor(color[s[w][j]], 0);
	cct_gotoxy(lie, hang + 1);
	cout << "○";
	Sleep(m);
	cct_setcolor(15, 0);
	cct_gotoxy(lie, hang);
	cout << "═";
}
