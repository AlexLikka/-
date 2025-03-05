#include <iostream>
#include <iomanip>
#include <conio.h>
#include <cstring>
#include "magic_ball.h"
#include "cmd_console_tools.h"
#include <Windows.h>

using namespace std;

int main()
{
	while (1) {
		reset_cmd();
		int r, c;
		int s[10][10] = { -1 };
		int option = menu();
		if (!option) {
			return 0;
		}
		cct_cls();
		input(&r, &c);
		switch (option) {
			case 1:
				h1(s, r, c);
				break;
			case 2:
				h2(s, r, c);
				break;
			case 3:
				h3(s, r, c);
				break;
			case 4:
				h4(s, r, c);
				break;
			case 5:
				h5(s, r, c);
				break;
			case 6:
				h6(s, r, c);
				break;
			case 7:
				h7(s, r, c);
				break;
			case 8:
				h8(s, r, c);
				break;
			case 9:
				h9(s, r, c);
				break;
		}

		int x, y;
		cout << "\n本小题结束，请输入End继续...";
		cct_getxy(x, y);
		while (1) {

			char keepon[1024] = { 0 };
			cin.getline(keepon, 1024);
			for (int i = 0; keepon[i] != 0; i++) {
				if (keepon[i] <= 'z' && keepon[i] >= 'a') {
					keepon[i] = keepon[i] - ('a' - 'A');
				}
			}
			if (!strcmp(keepon, "END")) {
				break;
			}
			else {
				cct_gotoxy(0, y + 1);
				cout << "输入错误，请重新输入";
				cct_gotoxy(x, y);
				cout << setw(50) << " ";
				cct_gotoxy(x, y);
			}
		}
	 }

	return 0;
}