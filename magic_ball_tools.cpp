#include <iostream>
#include <iomanip>
#include <conio.h>
#include "magic_ball.h"
#include "cmd_console_tools.h"
#include <Windows.h>

using namespace std;

/*------------------------------ ��ӡ��----------------------------------*/
void print_out(int (*s)[10], int r, int c, int option, int (*h)[10])
{
	if (option == 1) {
		cout << "��ʼ���飺" << endl;
	}
	for (int j = 0; j <= c; j++) {
		if (j == 0)
			cout << setw(3) << "|";
		else
			cout << setw(3) << j;
	}
	cout << endl << "--+" << setfill('-') << setw(3 * c + 1) << "-" << setfill(' ') << endl;

	if (option == 1 || option == 10 || option == 11 || option == 12) {
		for (int i = 1; i <= r; i++) {
			for (int j = 0; j <= c; j++) {
				if (!j) {
					cout << char('A' + i - 1) << " |";
				}
				else {
					cout << "  "; // 2 space
					if (option == 1) {
						cout << s[i][j];
					}
					else if (option == 10) {
						if (h[i][j] == 1) {
							cct_setcolor(14, 1);
							cout << s[i][j];
							cct_setcolor(0);
						}
						else {
							cct_setcolor(0);
							cout << s[i][j];
						}
					}
					else if (option == 11) {
						if (s[i][j] == 0) {
							cct_setcolor(14, 1);
							cout << s[i][j];
							h[i][j] = 1;
							cct_setcolor(0);
						}
						else {
							cct_setcolor(0);
							cout << s[i][j];
						}
					}
					else if (option == 12) {
						if (h[i][j] == 1) {
							cct_setcolor(14, 1);
							cout << s[i][j];
							cct_setcolor(0);
							h[i][j] = 0;
						}
						else {
							cct_setcolor(0);
							cout << s[i][j];
						}
					}
				}
			}
			cout << endl;
		}
	}
	cout << endl;
}

/*------------------------------ ������----------------------------------*/
int check_1(int (*s)[10], int r, int c, int (*h)[10], int option)
{
	int helper = 0;
	int helper_check_1 = 0;
	for (int i = 1; i <= r; i++) {
		for (int j = 1; j <= c; j++) {
			if (s[i][j] == s[i][j + 1] && s[i][j] == s[i][j + 2] && s[i][j] != -1) {
				h[i][j] = h[i][j + 1] = h[i][j + 2] = 1;
				helper = 1;
			}
		}
	}
	for (int j = 1; j <= c; j++) {
		for (int i = 1; i <= r; i++) {
			if (s[i][j] == s[i + 1][j] && s[i][j] == s[i + 2][j] && s[i][j] != -1) {
				h[i][j] = h[i + 1][j] = h[i + 2][j] = 1;
				helper = 1;
			}
		}
	}
	helper_check_1 = helper;
	if (option != 9) {
		if (helper == 0) {
			cout << "��ʼ���޿�������" << endl;
			return helper_check_1;
		}
		else {
			cout << "��ʼ���������ͬɫ��ʶ����" << endl;  // 1
		}
	}

	return helper_check_1;
}

void remove_0(int (*s)[10], int r, int c, int(*h)[10])
{
	for (int i = 1; i <= r; i++) {
		for (int j = 1; j <= c; j++) {
			if (h[i][j] == 1) {
				s[i][j] = 0;
				h[i][j] = 0; //��ʼ��Ϊ�������λ�����Ǻ���׼��
			}
		}
	}

	for (int j = 1; j <= c; j++) {
		for (int i = r; i > 0; i--) {
			if (s[i][j] == 0) {
				for (int w = i; w > 1; w--) {
					s[w][j] = s[w - 1][j];
				}
				s[1][j] = 0;
				int helper_i = 0;
				for (int w = i; w > 0; w--) {
					if (s[w][j] == 0) {
						helper_i = 0;
					}
					else {
						helper_i = 1;
						break;
					}
				}
				if (helper_i) {
					i++;
				}
			}
		}
	}
}

/*------------------------------ ���----------------------------------*/
void fill_new(int (*s)[10], int r, int c, int(*h)[10], int print_new_circle)
{
	int color[10] = { -1, 6, 7, 8, 9, 10, 11, 12, 13, 14 };
	srand((unsigned)time(NULL));
	for (int i = 1; i <= r; i++) {
		for (int j = 1; j <= c; j++) {
			if (s[i][j] == 0) {
				//srand((unsigned)time(NULL));
				s[i][j] = rand() % 9 + 1;
				if (print_new_circle) {
					cct_gotoxy(4 * j - 2, 2 * i);
					cct_setcolor(color[s[i][j]], 0);
					cout << "��"; // ��
					Sleep(200);
				}
			}
		}
	}
	if (print_new_circle) {
		cct_setcolor(0);
		cct_gotoxy(0, 2 * r + 2);
		cout << "                              ";
		cct_gotoxy(0, 2 * r + 2);
	 }

}

/*------------------------------ ��ʾ��----------------------------------*/
int hint(int(*s)[10], int r, int c, int(*h)[10], int print_hint_circle)
{
	int ts = 0;
	int helper_hint = 0;
	// ����h�᲻���ͻ �����Ű�
	// �ܷ�����б߽�����
	// ���ܲ��ܶ�������һ����λ������
	int ds[20][20] = { 0 };
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 20; j++) {
			ds[i][j] = 0;
		}
	}
	for (int i = 1; i <= r; i++) {
		for (int j = 1; j <= c; j++) {
			ds[i + 1][j + 1] = s[i][j];
			h[i][j] = 0;
		}
	}

	for (int i = 2; i <= r; i++) {
		for (int j = 2; j <= c; j++) {
			// up
			if (ds[i - 1][j]) {
				ts = ds[i - 1][j];
				ds[i - 1][j] = ds[i][j];
				ds[i][j] = ts;
				if ((ds[i][j] == ds[i][j + 1] && ds[i][j] == ds[i][j - 1])
					|| (ds[i][j] == ds[i][j + 1] && ds[i][j] == ds[i][j + 2])
					|| (ds[i][j] == ds[i][j - 1] && ds[i][j] == ds[i][j - 2])
					|| (ds[i][j] == ds[i + 1][j] && ds[i][j] == ds[i + 2][j]) && ds[i][j] != 0) {
					// ��Ǽӻ�ԭ
					h[i - 1][j - 1] = 1;
					h[i - 2][j - 1] = 1;
					helper_hint = 1;
				}
				ts = ds[i - 1][j];
				ds[i - 1][j] = ds[i][j];
				ds[i][j] = ts;
			}

			// down
			if (ds[i + 1][j]) {
				ts = ds[i + 1][j];
				ds[i + 1][j] = ds[i][j];
				ds[i][j] = ts;
				if ((ds[i][j] == ds[i][j + 1] && ds[i][j] == ds[i][j - 1])
					|| (ds[i][j] == ds[i][j + 1] && ds[i][j] == ds[i][j + 2])
					|| (ds[i][j] == ds[i][j - 1] && ds[i][j] == ds[i][j - 2])
					|| (ds[i][j] == ds[i - 1][j] && ds[i][j] == ds[i - 2][j]) && ds[i][j]) {
					// ��Ǽӻ�ԭ
					h[i - 1][j - 1] = 1;
					h[i][j - 1] = 1;
					helper_hint = 1;
				}
				ts = ds[i + 1][j];
				ds[i + 1][j] = ds[i][j];
				ds[i][j] = ts;
			}

			// left
			if (ds[i][j - 1]) {
				ts = ds[i][j - 1];
				ds[i][j - 1] = ds[i][j];
				ds[i][j] = ts;
				if ((ds[i][j] == ds[i + 1][j] && ds[i][j] == ds[i - 1][j])
					|| (ds[i][j] == ds[i - 1][j] && ds[i][j] == ds[i - 2][j])
					|| (ds[i][j] == ds[i + 1][j] && ds[i][j] == ds[i + 2][j])
					|| (ds[i][j] == ds[i][j + 1] && ds[i][j] == ds[i][j + 2]) && ds[i][j]) {
					// ��Ǽӻ�ԭ
					h[i - 1][j - 1] = 1;
					h[i - 1][j - 2] = 1;
					helper_hint = 1;
				}
				ts = ds[i][j - 1];
				ds[i][j - 1] = ds[i][j];
				ds[i][j] = ts;
			}

			// right
			if (ds[i][j + 1]) {
				ts = ds[i][j + 1];
				ds[i][j + 1] = ds[i][j];
				ds[i][j] = ts;
				if ((ds[i][j] == ds[i + 1][j] && ds[i][j] == ds[i - 1][j])
					|| (ds[i][j] == ds[i - 1][j] && ds[i][j] == ds[i - 2][j])
					|| (ds[i][j] == ds[i + 1][j] && ds[i][j] == ds[i + 2][j])
					|| (ds[i][j] == ds[i][j - 1] && ds[i][j] == ds[i][j - 2]) && ds[i][j]) {
					//// ��Ǽӻ�ԭ
					h[i - 1][j - 1] = 1;
					h[i - 1][j] = 1;
					helper_hint = 1;
				}
				ts = ds[i][j + 1];
				ds[i][j + 1] = ds[i][j];
				ds[i][j] = ts;
			}
		}
	}

	if (print_hint_circle) {
		int color[10] = { -1, 6, 7, 8, 9, 10, 11, 12, 13, 14 };
		for (int i = 1; i <= r; i++) {
			for (int j = 1; j <= c; j++) {
				if (h[i][j] == 1) {
					cct_gotoxy(4 * j - 2, 2 * i);
					cct_setcolor(color[s[i][j]], 0);
					cout << "��"; // ���
				}
			}
		}
		clear_instrcution(r);
	}
	return helper_hint;
}

/*------------------------------ ������----------------------------------*/
int location(int (*s)[10], int r, int c, int (*h)[10], int option)
{
	cct_gotoxy(0, r * 2 + 2);
	cout << "[��ǰ���]";
	int color[10] = { -1, 6, 7, 8, 9, 10, 11, 12, 13, 14 };
	int x = 0, y = 0;
	int x1 = 0, y1 = 0;
	int x3 = 0, y3 = 0;
	int game_choice = 0;
	int x31 = 0, y31 = 0;
	int x32 = 0, y32 = 0;
	cct_getxy(x1, y1); 
	int ret, maction;
	int keycode1, keycode2;
	int loop = 1;
	int SCORE = 0;
	int check_swap = 0;
	cct_enable_mouse();
	cct_setcursor(CURSOR_INVISIBLE); 
	while (loop) {
		cct_gotoxy(0, r * 2 + 2);
		cout << "[��ǰ���]";
		/* �����/���̣�����ֵΪ���������е�ĳһ��, ��ǰ���λ����<x,y>�� */
		ret = cct_read_keyboard_and_mouse(x, y, maction, keycode1, keycode2);
		if (ret == CCT_MOUSE_EVENT) {
			cct_gotoxy(x1, y1);
			cout << "                                     ";
			if (y % 2 == 0 && (x % 4 == 2 || x % 4 == 3)) {
				if (x % 4 == 3) {
					x3 = (x + 1) / 4;
					x = x - 1;
				}
				else
					x3 = (x + 2) / 4;
				y3 = y / 2;

				if (y3 <= r && x3 <= c) {
					cct_gotoxy(x1, y1);
					cout << setw(2) << char(y3 + 'A' - 1) << "��" << setw(2) << x3 << "��";
				}
				else {
					cct_gotoxy(x1, y1);
					cout << "λ�÷Ƿ�";
				}
			}
			else {
				cct_gotoxy(x1, y1);
				cout << "λ�÷Ƿ�";
			}

			switch (maction) {
				case MOUSE_ONLY_MOVED:
					break;
				case MOUSE_LEFT_BUTTON_CLICK:
					 ret = cct_read_keyboard_and_mouse(x, y, maction, keycode1, keycode2);
					 if (x % 4 == 3) {
						 x3 = (x + 1) / 4;
						 x = x - 1;
					 }
					 else
						 x3 = (x + 2) / 4;
					 y3 = y / 2;
					// ѡ��    //��ǰѡ��H��3��  //����ѡ��I��4��
					if (y % 2 == 0 && (x % 4 == 2 || x % 4 == 3) && (y3 <= r && x3 <= c)) {
						if (h[y3][x3] == 1) {
							cct_gotoxy(0, r * 2 + 2);
							cout << "                                     ";
							cct_gotoxy(0, r * 2 + 2);
							cout << "��ǰѡ��" << setw(4) << char(y3 + 'A' - 1) << "��" << setw(2) << x3 << "��";
							if (option == 8) {
								Sleep(400);
								cct_gotoxy(0, r * 2 + 2);
								cout << "                                     ";
								cct_gotoxy(0, r * 2 + 2);
								return -2;
							}
							if (option == 9) {
								game_choice++;
								if (game_choice % 2 == 1) {
									x31 = x3;
									y31 = y3;
								}
								if (game_choice % 2 == 0) {
									x32 = x3;
									y32 = y3;
								}
								if (x31 != x32 && y32 != y31) {
									cct_gotoxy(x, y);
									cct_setcolor(color[s[y3][x3]], 15);
									cout << "��"; // ��
									cct_setcolor(0);
								}
								else if (x31 == x32 && y32 == y31){
									cct_gotoxy(x, y);
									cct_setcolor(color[s[y3][x3]], 0);
									cout << "��"; // ��
									cct_setcolor(0);
									x31 = 0;
									y31 = 0;
									x32 = 0;
									y32 = 0;
									break;
								}

								if (game_choice % 2 == 0) {
									check_swap = game_swap(s, r, c, h, x31, y31, x32, y32, &SCORE);
									if (!check_swap) {
										cct_gotoxy(0, r * 2 + 2);
										cout << "                                     ";
										cct_gotoxy(0, r * 2 + 2);
										cout << "���ܽ���                     " ;
										Sleep(400); 
									}
									else {
										int helper_9_game = check_1(s, r, c, h, 9);
										if (helper_9_game) {
											while (helper_9_game) {
												remove_circle(s, r, c, h);
												falling_down(s, r, c, h); // ���䶯��
												remove_0(s, r, c, h); //����ȡ�� Ϊ����ṩʶ����
												fill_new(s, r, c, h, 1);
												helper_9_game = check_1(s, r, c, h, 9);
											}
										}
										print_circle(s, r, c, 1, h, 1, 9);
										int helper_hint_game = hint(s, r, c, h, 1); // �޿��������Ϸ����!
										if (!helper_9_game && !helper_hint_game) {
											cct_gotoxy(0, 0); //�޿��������Ϸ����!���շ���:3)
											cout << "�޿��������Ϸ����!���շ���:" << SCORE << ")        ";
											cct_gotoxy(0, r * 2 + 2);
											cout << "                                     ";
											cct_gotoxy(0, r * 2 + 3);

											return -4;
										}
										else {
											cct_gotoxy(14, 0);
											cout << "����ǰ������"<< SCORE <<" �Ҽ��˳���";
										}
									}
									x31 = 0;
									y31 = 0;
									x32 = 0;
									y32 = 0;
								}
							}
						}
						else {
							cct_gotoxy(0, r * 2 + 2);
							cout << "                                     ";
							cct_gotoxy(0, r * 2 + 2);
							cout <<"����ѡ��" << setw(4) << char(y3 + 'A' - 1) << "��" << setw(2) << x3 << "��";
							Sleep(180); // ���ʵ��ѡ�г�����ʾ�أ�
						}
					}
					break;
				case MOUSE_RIGHT_BUTTON_CLICK:
					if (y % 2 == 0 && (x % 4 == 2 || x % 4 == 3) && (y3 <= r && x3 <= c)) {
						loop = 0; // �Ҽ�����˳�ѭ��
						cct_gotoxy(0, r * 2 + 2);
						cout << "                                     ";
						cct_gotoxy(0, r * 2 + 2);
						return -1;
						break;
					}
					break;
				default:
					break;
			} 
		}
	}
	return 0;
}

/*------------------------------ ��Ϸ��----------------------------------*/
int game_score(int(*s)[10], int r, int c, int (*h)[10], int* SCORE)
{
	int check_swap = 0;
	for (int i = 1; i <= r; i++) {
		for (int j = 1; j <= c; j++) {
			h[i][j] = 0;
			}
		}

	check_1(s, r, c, h, 9);
	for (int i = 1; i <= r; i++) {
		for (int j = 1; j <= c; j++) {
			if (h[i][j] == 1) {
				check_swap = 1;
				(*SCORE)++;
			}
		}
	}
	return check_swap;
}

int game_swap(int(*s)[10], int r, int c, int (*h)[10], int x31, int y31, int x32, int y32, int *SCORE)
{
	int color[10] = { -1, 6, 7, 8, 9, 10, 11, 12, 13, 14 };
	int x1, y1, x2, y2;
	y1 = 2 * y31;
	y2 = 2 * y32;
	x1 = 4 * x31 - 2;
	x2 = 4 * x32 - 2;
	if (abs(x31 - x32) == 1 || abs(y31 - y32) == 1) {
		if (!(abs(x31 - x32) == 1 && abs(y31 - y32))) {
			int ts;
			ts = s[y31][x31];
			s[y31][x31] = s[y32][x32];
			s[y32][x32] = ts;

			int check_swap = game_score(s, r, c, h, SCORE);
			if (!check_swap) {
				ts = s[y31][x31];
				s[y31][x31] = s[y32][x32];
				s[y32][x32] = ts;
				cct_gotoxy(x1, y1);
				cct_setcolor(color[s[y31][x31]], 0);
				// ��
				cout << "��"; // ��
				cct_gotoxy(x2, y2);
				cct_setcolor(color[s[y32][x32]], 0);
				cout << "��"; // ��
				cct_setcolor(0);

				return 0;
			}

			// ���ƽ���
			cct_gotoxy(x1, y1);
			cct_setcolor(color[s[y31][x31]], 0);
			cout << "��"; // ��
			cct_gotoxy(x2, y2);
			cct_setcolor(color[s[y32][x32]], 0);
			cout << "��"; // ��
			cct_setcolor(0);

			return 1;
		}
	}
	cct_gotoxy(x2, y2);
	cct_setcolor(color[s[y32][x32]], 0);
	cout << "��"; // ��
	cct_gotoxy(x1, y1);
	cct_setcolor(color[s[y31][x31]], 0);
	cout << "��"; // ��
	cct_setcolor(0);

	return 0;
}

/*�տ�ʼȫ��д��Tool������������һ��graph�ˣ���*/
/*------------------------------ ͼ����----------------------------------*/
/*
* 
/*����
void set_cmd(int r);
void reset_cmd();
void print_canvas(int(*s)[10], int r, int c, int grid, int speed);
void print_circle(int(*s)[10], int r, int c, int grid, int(*h)[10], int speed, int option);
void remove_circle(int(*s)[10], int r, int c, int(*h)[10]);
/*��̬����
void falling_down(int(*s)[10], int r, int c, int(*h)[10]);
void lan(int(*s)[10], int j, int w, int lie, int hang, int helper_down);
*
*/

/*------------------------------ �س���----------------------------------*/
void enter_option(int option, int r) 
{
	if (option == 6 || option == 7 || option == 5)
		clear_instrcution(r);
	if (option == 1) {
		cout << "���س�������Ѱ�ҳ�ʼ��������Ĳ���..." << endl; // 1
	}
	else if (option == 2 || option == 5) {
		cout << "���س����������������0����..." << endl;
		if (option == 2)
			cout << "�����0�������(��ͬɫ��ʶ)��" << endl;
	}
	else if (option == 3 || option == 6) {
		cout << "���س���������ֵ���..." << endl;
		if (option == 3)
			cout << "��ֵ���������(��ͬɫ��ʶ)��" << endl;
	}
	else if (option == 4) {
		cout << "���س�����ʾͼ��..."<<endl;
	}
	else if (option == 7) {
		cout << "���س�����ʾ������ʾ..." << endl;
	}

	int x;
	while (1)
	{
		x = _getch();
		if (x == 13)
			break;
	}
}

void clear_instrcution(int r)
{
	cct_setcolor(0);
	cct_gotoxy(0, 2 * r + 2);
	cout << "                              ";
	cct_gotoxy(0, 2 * r + 2);
}

/*------------------------------ ��̭��----------------------------------*/
void tips(int(*s)[10], int r, int c, int(*h)[10])
{
	// ���˼·���� ûд�� �ȿ��� �븴���� ���治�ñ�ͨ
	int helper_num = 0;
	int helper_check_r = 0;
	int helper_check_c = 0;
	int helper_r_1 = 0;
	int helper_r_3 = 0;
	int helper_c_1 = 0;
	int helper_c_3 = 0;
	for (int i = 1; i < r; i++) {
		for (int j = 1; j < c; j++) {
			int w[10][10] = { 0 };
			helper_r_1 = 0;
			helper_r_3 = 0;
			helper_c_1 = 0;
			helper_c_3 = 0;
			helper_check_r = 0;
			helper_check_c = 0;

			for (int y = j - 1; y <= j + 1; j++) {
				for (int x = i - 1; x <= i + 1; i++) {
					helper_num = 0;
					if (s[i][j] == s[x][y]) {
						if (x == i - 1 && helper_r_1 == 0) {
							helper_r_1 = 1;
							helper_check_r += x;
						}
						else if (x == i + 1 && helper_r_3 == 0) {
							helper_r_3 = 1;
							helper_check_r += x;
						}
						if (y == j - 1 && helper_c_1 == 0) {
							helper_c_1 = 1;
							helper_check_c += y;
						}
						else if (y == j + 1 && helper_c_3 == 0) {
							helper_c_3 = 1;
							helper_check_c += y;
						}
						helper_num++;
					}
				}
			}
			if (helper_num >= 2) {
				if (!(helper_check_c == 2 * j) || !(helper_check_r == 2 * i)) {

				}
			}
			else {
				;
			}
		}
	}
}

