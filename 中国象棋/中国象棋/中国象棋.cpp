#include<stdio.h>
#include<stdlib.h>
#include<easyx.h>
#include<math.h>
#define WIDTH 800
#define HEIGHT 880
#define RADIUS 40
IMAGE R_bing[2];
IMAGE R_pao[2];
IMAGE R_che[2];
IMAGE R_ma[2];
IMAGE R_xiang[2];
IMAGE R_shi[2];
IMAGE R_shuai[2];
IMAGE B_zu[2];
IMAGE B_pao[2];
IMAGE B_ju[2];
IMAGE B_ma[2];
IMAGE B_xiang[2];
IMAGE B_shi[2];
IMAGE B_jiang[2];
IMAGE biankuang[2];
typedef struct ChessPiece {
	char type;
	bool isExist;
	bool isPicked;
	IMAGE* img;
}MyPiece;
struct Mouse {
	int startX, startY;
	int endX, endY;
}MyMouse;
MyPiece** Map;
ExMessage m;
char currentPiece = 'R';
void loadPicture() {
	loadimage(R_bing, "R_bing_0.png", 2 * RADIUS, 2 * RADIUS);
	loadimage(R_bing + 1, "R_bing_1.png", 2 * RADIUS, 2 * RADIUS);
	loadimage(R_pao, "R_pao_0.png", 2 * RADIUS, 2 * RADIUS);
	loadimage(R_pao + 1, "R_pao_1.png", 2 * RADIUS, 2 * RADIUS);
	loadimage(R_che, "R_che_0.png", 2 * RADIUS, 2 * RADIUS);
	loadimage(R_che + 1, "R_che_1.png", 2 * RADIUS, 2 * RADIUS);
	loadimage(R_ma, "R_ma_0.png", 2 * RADIUS, 2 * RADIUS);
	loadimage(R_ma + 1, "R_ma_1.png", 2 * RADIUS, 2 * RADIUS);
	loadimage(R_xiang, "R_xiang_0.png", 2 * RADIUS, 2 * RADIUS);
	loadimage(R_xiang + 1, "R_xiang_1.png", 2 * RADIUS, 2 * RADIUS);
	loadimage(R_shi, "R_shi_0.png", 2 * RADIUS, 2 * RADIUS);
	loadimage(R_shi + 1, "R_shi_1.png", 2 * RADIUS, 2 * RADIUS);
	loadimage(R_shuai, "R_shuai_0.png", 2 * RADIUS, 2 * RADIUS);
	loadimage(R_shuai + 1, "R_shuai_1.png", 2 * RADIUS, 2 * RADIUS);
	loadimage(B_zu, "B_zu_0.png", 2 * RADIUS, 2 * RADIUS);
	loadimage(B_zu + 1, "B_zu_1.png", 2 * RADIUS, 2 * RADIUS);
	loadimage(B_pao, "B_pao_0.png", 2 * RADIUS, 2 * RADIUS);
	loadimage(B_pao + 1, "B_pao_1.png", 2 * RADIUS, 2 * RADIUS);
	loadimage(B_ju, "B_ju_0.png", 2 * RADIUS, 2 * RADIUS);
	loadimage(B_ju + 1, "B_ju_1.png", 2 * RADIUS, 2 * RADIUS);
	loadimage(B_ma, "B_ma_0.png", 2 * RADIUS, 2 * RADIUS);
	loadimage(B_ma + 1, "B_ma_1.png", 2 * RADIUS, 2 * RADIUS);
	loadimage(B_xiang, "B_xiang_0.png", 2 * RADIUS, 2 * RADIUS);
	loadimage(B_xiang + 1, "B_xiang_1.png", 2 * RADIUS, 2 * RADIUS);
	loadimage(B_shi, "B_shi_0.png", 2 * RADIUS, 2 * RADIUS);
	loadimage(B_shi + 1, "B_shi_1.png", 2 * RADIUS, 2 * RADIUS);
	loadimage(B_jiang, "B_jiang_0.png", 2 * RADIUS, 2 * RADIUS);
	loadimage(B_jiang + 1, "B_jiang_1.png", 2 * RADIUS, 2 * RADIUS);
	loadimage(biankuang, "biankuang_0.png", 2 * RADIUS, 2 * RADIUS);
	loadimage(biankuang + 1, "biankuang_1.png", 2 * RADIUS, 2 * RADIUS);
}
void drawBoard() {
	for (int i = 0;i < 10;i++) {
		line(2 * RADIUS, (2 + 2 * i) * RADIUS, WIDTH - 2 * RADIUS, (2 + 2 * i) * RADIUS);
	}
	line(2 * RADIUS, 2 * RADIUS, 2 * RADIUS, HEIGHT - 2 * RADIUS);
	line(WIDTH - 2 * RADIUS, 2 * RADIUS, WIDTH - 2 * RADIUS, HEIGHT - 2 * RADIUS);
	for (int i = 1;i < 9;i++) {
		line((2 + 2 * i) * RADIUS, 2 * RADIUS, (2 + 2 * i) * RADIUS, 10 * RADIUS);
		line((2 + 2 * i) * RADIUS, 12 * RADIUS, (2 + 2 * i) * RADIUS, HEIGHT - 2 * RADIUS);
	}
	line(8 * RADIUS, 2 * RADIUS, 12 * RADIUS, 6 * RADIUS);
	line(8 * RADIUS, 6 * RADIUS, 12 * RADIUS, 2 * RADIUS);
	line(8 * RADIUS, HEIGHT - 6 * RADIUS, 12 * RADIUS, HEIGHT - 2 * RADIUS);
	line(8 * RADIUS, HEIGHT - 2 * RADIUS, 12 * RADIUS, HEIGHT - 6 * RADIUS);
}
void initMap() {
	Map = (MyPiece**)malloc(10 * sizeof(MyPiece*));
	for (int i = 0;i < 10;i++) {
		Map[i] = (MyPiece*)malloc(9 * sizeof(MyPiece));
		for (int j = 0;j < 9;j++) {
			Map[i][j].isPicked = false;
		}
	}
	for (int i = 0;i < 9;i++) {
		Map[4][i].type = '_';
		Map[4][i].isExist = false;
		Map[4][i].img = NULL;
		Map[5][i].type = '_';
		Map[5][i].isExist = false;
		Map[5][i].img = NULL;
		Map[1][i].type = '_';
		Map[1][i].isExist = false;
		Map[1][i].img = NULL;
		Map[8][i].type = '_';
		Map[8][i].isExist = false;
		Map[8][i].img = NULL;
	}
	for (int i = 0;i < 9;i++) {
		if (i % 2 == 0) {
			Map[3][i].type = 'Z';
			Map[3][i].isExist = true;
			Map[3][i].img = R_bing;
			Map[6][i].type = 'z';
			Map[6][i].isExist = true;
			Map[6][i].img = B_zu;
		}
		else {
			Map[3][i].type = '_';
			Map[3][i].isExist = false;
			Map[3][i].img = NULL;
			Map[6][i].type = '_';
			Map[6][i].isExist = false;
			Map[6][i].img = NULL;
		}
	}
	for (int i = 0;i < 9;i++) {
		if (i == 1) {
			Map[2][i].type = 'P';
			Map[2][i].isExist = true;
			Map[2][i].img = R_pao;
			Map[7][i].type = 'p';
			Map[7][i].isExist = true;
			Map[7][i].img = B_pao;
		}
		else if (i == 7) {
			Map[2][i].type = 'P';
			Map[2][i].isExist = true;
			Map[2][i].img = R_pao;
			Map[7][i].type = 'p';
			Map[7][i].isExist = true;
			Map[7][i].img = B_pao;
		}
		else {
			Map[2][i].type = '_';
			Map[2][i].isExist = false;
			Map[2][i].img = NULL;
			Map[7][i].type = '_';
			Map[7][i].isExist = false;
			Map[7][i].img = NULL;
		}
	}
	for (int i = 0;i < 4;i++) {
		if (i == 0) {
			Map[0][i].type = 'C';
			Map[0][i].isExist = true;
			Map[0][i].img = R_che;
			Map[0][8 - i].type = 'C';
			Map[0][8 - i].isExist = true;
			Map[0][8 - i].img = R_che;
			Map[9][i].type = 'c';
			Map[9][i].isExist = true;
			Map[9][i].img = B_ju;
			Map[9][8 - i].type = 'c';
			Map[9][8 - i].isExist = true;
			Map[9][8 - i].img = B_ju;
		}
		else if (i == 1) {
			Map[0][i].type = 'M';
			Map[0][i].isExist = true;
			Map[0][i].img = R_ma;
			Map[0][8 - i].type = 'M';
			Map[0][8 - i].isExist = true;
			Map[0][8 - i].img = R_ma;
			Map[9][i].type = 'm';
			Map[9][i].isExist = true;
			Map[9][i].img = B_ma;
			Map[9][8 - i].type = 'm';
			Map[9][8 - i].isExist = true;
			Map[9][8 - i].img = B_ma;
		}
		else if (i == 2) {
			Map[0][i].type = 'X';
			Map[0][i].isExist = true;
			Map[0][i].img = R_xiang;
			Map[0][8 - i].type = 'X';
			Map[0][8 - i].isExist = true;
			Map[0][8 - i].img = R_xiang;
			Map[9][i].type = 'x';
			Map[9][i].isExist = true;
			Map[9][i].img = B_xiang;
			Map[9][8 - i].type = 'x';
			Map[9][8 - i].isExist = true;
			Map[9][8 - i].img = B_xiang;
		}
		else if (i == 3) {
			Map[0][i].type = 'S';
			Map[0][i].isExist = true;
			Map[0][i].img = R_shi;
			Map[0][8 - i].type = 'S';
			Map[0][8 - i].isExist = true;
			Map[0][8 - i].img = R_shi;
			Map[9][i].type = 's';
			Map[9][i].isExist = true;
			Map[9][i].img = B_shi;
			Map[9][8 - i].type = 's';
			Map[9][8 - i].isExist = true;
			Map[9][8 - i].img = B_shi;
		}
	}
	Map[0][4].type = 'J';
	Map[0][4].isExist = true;
	Map[0][4].img = R_shuai;
	Map[9][4].type = 'j';
	Map[9][4].isExist = true;
	Map[9][4].img = B_jiang;
}
void initMyMouse() {
	MyMouse.startX = -1;
	MyMouse.startY = -1;
	MyMouse.endX = -1;
	MyMouse.endY = -1;
}
void drawPiece() {
	for (int i = 0;i < 10;i++) {
		for (int j = 0;j < 9;j++) {
			if (Map[i][j].isExist) {
				putimage((2 * j + 1) * RADIUS, (2 * i + 1) * RADIUS, Map[i][j].img, SRCPAINT);
				putimage((2 * j + 1) * RADIUS, (2 * i + 1) * RADIUS, Map[i][j].img + 1, SRCAND);
			}
		}
	}
}
void pickPiece(int x, int y) {
	for (int i = 0;i < 10;i++) {
		for (int j = 0;j < 9;j++) {
			if (i == y && j == x) {
				continue;
			}
			Map[i][j].isPicked = false;
		}
	}
}
void drawBiankuang() {
	for (int i = 0;i < 10;i++) {
		for (int j = 0;j < 9;j++) {
			if (Map[i][j].isPicked) {
				putimage((2 * j + 1) * RADIUS, (2 * i + 1) * RADIUS, biankuang, SRCPAINT);
				putimage((2 * j + 1) * RADIUS, (2 * i + 1) * RADIUS, biankuang + 1, SRCAND);
				return;
			}
		}
	}
}
void movePiece(int x1, int y1, int x2, int y2) {
	Map[y2][x2].type = Map[y1][x1].type;
	Map[y2][x2].isExist = true;
	Map[y2][x2].img = Map[y1][x1].img;
	Map[y1][x1].type = '_';
	Map[y1][x1].isExist = false;
	Map[y1][x1].isPicked = false;
	Map[y1][x1].img = NULL;
}
bool TheTwoKingsFaceEachOther(int x1, int y1, int x2, int y2) {
	int m = -1, n = -1;
	for (int i = 0;i <= 2;i++) {
		for (int j = 3;j <= 5;j++) {
			if (Map[i][j].type == 'J') {
				m = i;
				n = j;
				break;
			}
		}
		if (m != -1 && n != -1) {
			break;
		}
	}
	for (int i = m ;i < 10;i++) {
		if (i == y1 && n == x1) {
			continue;
		}
		if (i == y2 && n == x2) {
			break;
		}
		if (Map[i][n].isExist && Map[i][n].type != 'j') {
			break;
		}
		if (Map[i][n].type == 'j') {
			return true;
		}
	}
	return false;
}
bool Zu() {
	int x1 = MyMouse.startX;
	int y1 = MyMouse.startY;
	int x2 = MyMouse.endX;
	int y2 = MyMouse.endY;
	int flag = 0;
	if (currentPiece == 'R') {
		if (y1 >= 5) {
			if (y2 == y1 && (x2 == x1 + 1 || x2 == x1 - 1)) {
				if (!Map[y2][x2].isExist || (Map[y2][x2].type >= 97 && Map[y2][x2].type <= 122)) {
					flag = 1;
				}
			}
		}
		if (y2 == y1 + 1 && x2 == x1) {
			if (!Map[y2][x2].isExist || (Map[y2][x2].type >= 97 && Map[y2][x2].type <= 122)) {
				flag = 1;
			}
		}
	}
	else if (currentPiece == 'B') {
		if (y1 <= 4) {
			if (y2 == y1 && (x2 == x1 + 1 || x2 == x1 - 1)) {
				if (!Map[y2][x2].isExist || (Map[y2][x2].type >= 65 && Map[y2][x2].type <= 90)) {
					flag = 1;
				}
			}
		}
		if (y2 == y1 - 1 && x2 == x1) {
			if (!Map[y2][x2].isExist || (Map[y2][x2].type >= 65 && Map[y2][x2].type <= 90)) {
				flag = 1;
			}
		}
	}
	if (flag == 1 && !TheTwoKingsFaceEachOther(x1, y1, x2, y2)) {
		movePiece(x1, y1, x2, y2);
		return true;
	}
	return false;
}
bool Pao() {
	int x1 = MyMouse.startX;
	int y1 = MyMouse.startY;
	int x2 = MyMouse.endX;
	int y2 = MyMouse.endY;
	int flag = 0;
	int max = -1, min = -1;
	if (currentPiece == 'R') {
		min = 97;
		max = 122;
	}
	else {
		min = 65;
		max = 90;
	}
	if (!Map[y2][x2].isExist) {
		if (y2 == y1) {
			for (int i = fmin(x2, x1) + 1;i < fmax(x2, x1);i++) {
				if (Map[y2][i].isExist) {
					return false;
				}
			}
			flag = 1;
		}
		else if (x2 == x1) {
			int number = 0;
			for (int i = fmin(y2, y1) + 1;i < fmax(y2, y1);i++) {
				if (Map[i][x2].isExist) {
					return false;
				}
			}
			flag = 1;
		}
	}
	else if (Map[y2][x2].type >= min && Map[y2][x2].type <= max) {
		if (y2 == y1) {
			int number = 0;
			for (int i = fmin(x2, x1) + 1;i < fmax(x2, x1);i++) {
				if (Map[y2][i].isExist) {
					number++;
				}
			}
			if (number == 1) {
				flag = 1;
			}
		}
		else if (x2 == x1) {
			int number = 0;
			for (int i = fmin(y2, y1) + 1;i < fmax(y2, y1);i++) {
				if (Map[i][x2].isExist) {
					number++;
				}
			}
			if (number == 1) {
				flag = 1;
			}
		}
	}
	if (flag == 1 && !TheTwoKingsFaceEachOther(x1, y1, x2, y2)) {
		movePiece(x1, y1, x2, y2);
		return true;
	}
	return false;
}
bool Ju() {
	int x1 = MyMouse.startX;
	int y1 = MyMouse.startY;
	int x2 = MyMouse.endX;
	int y2 = MyMouse.endY;
	int flag = 0;
	int max = -1, min = -1;
	if (currentPiece == 'R') {
		min = 97;
		max = 122;
	}
	else {
		min = 65;
		max = 90;
	}
	if ((!Map[y2][x2].isExist) || (Map[y2][x2].type >= min && Map[y2][x2].type <= max)) {
		if (y2 == y1) {
			for (int i = fmin(x2, x1) + 1;i < fmax(x2, x1);i++) {
				if (Map[y2][i].isExist) {
					return false;
				}
			}
			flag = 1;
		}
		else if (x2 == x1) {
			for (int i = fmin(y2, y1) + 1;i < fmax(y2, y1);i++) {
				if (Map[i][x2].isExist) {
					return false;
				}
			}
			flag = 1;
		}
	}
	if (flag == 1 && !TheTwoKingsFaceEachOther(x1, y1, x2, y2)) {
		movePiece(x1, y1, x2, y2);
		return true;
	}
	return false;
}
bool Ma() {
	int x1 = MyMouse.startX;
	int y1 = MyMouse.startY;
	int x2 = MyMouse.endX;
	int y2 = MyMouse.endY;
	int flag = 0;
	int max = -1, min = -1;
	if (currentPiece == 'R') {
		min = 97;
		max = 122;
	}
	else {
		min = 65;
		max = 90;
	}
	if (!Map[y2][x2].isExist || (Map[y2][x2].type >= min && Map[y2][x2].type <= max)) {
		if (y2 == y1 - 2 && (x2 == x1 - 1 || x2 == x1 + 1)) {
			if (!Map[y1 - 1][x1].isExist) {
				flag = 1;
			}
		}
		else if (y2 == y1 + 2 && (x2 == x1 - 1 || x2 == x1 + 1)) {
			if (!Map[y1 + 1][x1].isExist) {
				flag = 1;
			}
		}
		else if (x2 == x1 - 2 && (y2 == y1 - 1 || y2 == y1 + 1)) {
			if (!Map[y1][x1 - 1].isExist) {
				flag = 1;
			}
		}
		else if (x2 == x1 + 2 && (y2 == y1 - 1 || y2 == y1 + 1)) {
			if (!Map[y1][x1 + 1].isExist) {
				flag = 1;
			}
		}
	}
	if (flag == 1 && !TheTwoKingsFaceEachOther(x1, y1, x2, y2)) {
		movePiece(x1, y1, x2, y2);
		return true;
	}
	return false;
}
bool Xiang() {
	int x1 = MyMouse.startX;
	int y1 = MyMouse.startY;
	int x2 = MyMouse.endX;
	int y2 = MyMouse.endY;
	int flag = 0;
	int max = -1, min = -1;
	if (currentPiece == 'R') {
		min = 97;
		max = 122;
	}
	else {
		min = 65;
		max = 90;
	}
	if (!Map[y2][x2].isExist || (Map[y2][x2].type >= min && Map[y2][x2].type <= max)) {
		if (y2 == y1 - 2 && x2 == x1 - 2) {
			if (!Map[y1 - 1][x1 - 1].isExist) {
				flag = 1;
			}
		}
		else if (y2 == y1 - 2 && x2 == x1 + 2) {
			if (!Map[y1 - 1][x1 + 1].isExist) {
				flag = 1;
			}
		}
		else if (y2 == y1 + 2 && x2 == x1 - 2) {
			if (!Map[y1 + 1][x1 - 1].isExist) {
				flag = 1;
			}
		}
		else if (y2 == y1 + 2 && x2 == x1 + 2) {
			if (!Map[y1 + 1][x1 + 1].isExist) {
				flag = 1;
			}
		}
	}
	if (flag == 1 && !TheTwoKingsFaceEachOther(x1, y1, x2, y2)) {
		movePiece(x1, y1, x2, y2);
		return true;
	}
	return false;
}
bool Shi() {
	int x1 = MyMouse.startX;
	int y1 = MyMouse.startY;
	int x2 = MyMouse.endX;
	int y2 = MyMouse.endY;
	int flag = 0;
	int max = -1, min = -1;
	if (currentPiece == 'R') {
		min = 97;
		max = 122;
	}
	else {
		min = 65;
		max = 90;
	}
	if (currentPiece == 'R') {
		if (y2 <= 2 && x2 >= 3 && x2 <= 5) {
			if (!Map[y2][x2].isExist || (Map[y2][x2].type >= min && Map[y2][x2].type <= max)) {
				if (y2 == y1 - 1 && x2 == x1 - 1) {
					flag = 1;
				}
				else if (y2 == y1 - 1 && x2 == x1 + 1) {
					flag = 1;
				}
				else if (y2 == y1 + 1 && x2 == x1 - 1) {
					flag = 1;
				}
				else if (y2 == y1 + 1 && x2 == x1 + 1) {
					flag = 1;
				}
			}
		}
	}
	else if (currentPiece == 'B') {
		if (y2 >= 7 && x2 >= 3 && x2 <= 5) {
			if (!Map[y2][x2].isExist || (Map[y2][x2].type >= min && Map[y2][x2].type <= max)) {
				if (y2 == y1 - 1 && x2 == x1 - 1) {
					flag = 1;
				}
				else if (y2 == y1 - 1 && x2 == x1 + 1) {
					flag = 1;
				}
				else if (y2 == y1 + 1 && x2 == x1 - 1) {
					flag = 1;
				}
				else if (y2 == y1 + 1 && x2 == x1 + 1) {
					flag = 1;
				}
			}
		}
	}
	if (flag == 1 && !TheTwoKingsFaceEachOther(x1, y1, x2, y2)) {
		movePiece(x1, y1, x2, y2);
		return true;
	}
	return false;
}
bool Jiang() {
	int x1 = MyMouse.startX;
	int y1 = MyMouse.startY;
	int x2 = MyMouse.endX;
	int y2 = MyMouse.endY;
	int flag = 0;
	int max = -1, min = -1;
	if (currentPiece == 'R') {
		min = 97;
		max = 122;
		for (int i = y2 + 1;i < 10;i++) {
			if (Map[i][x2].isExist && Map[i][x2].type != 'j') {
				break;
			}
			if (Map[i][x2].type == 'j') {
				return false;
			}
		}
		if (y2 <= 2 && x2 >= 3 && x2 <= 5) {
			if ((abs(y2 - y1) <= 1 && x2 - x1 == 0) || (y2 - y1 == 0 && abs(x2 - x1) <= 1)) {
				if (!Map[y2][x2].isExist || (Map[y2][x2].type >= min && Map[y2][x2].type <= max)) {
					flag = 1;
				}
			}
		}
	}
	else {
		min = 65;
		max = 90;
		for (int i = y2 - 1;i >= 0;i--) {
			if (Map[i][x2].isExist && Map[i][x2].type != 'J') {
				break;
			}
			if (Map[i][x2].type == 'J') {
				return false;
			}
		}
		if (y2 >= 7 && x2 >= 3 && x2 <= 5) {
			if ((abs(y2 - y1) <= 1 && x2 - x1 == 0) || (y2 - y1 == 0 && abs(x2 - x1) <= 1)) {
				if (!Map[y2][x2].isExist || (Map[y2][x2].type >= min && Map[y2][x2].type <= max)) {
					flag = 1;
				}
			}
		}
	}
	if (flag == 1) {
		movePiece(x1, y1, x2, y2);
		return true;
	}
	return false;
}
bool judgePiece(int x, int y) {
	if (Map[y][x].type == 'Z' || Map[y][x].type == 'z') {
		return Zu();
	}
	else if (Map[y][x].type == 'P' || Map[y][x].type == 'p') {
		return Pao();
	}
	else if (Map[y][x].type == 'C' || Map[y][x].type == 'c') {
		return Ju();
	}
	else if (Map[y][x].type == 'M' || Map[y][x].type == 'm') {
		return Ma();
	}
	else if (Map[y][x].type == 'X' || Map[y][x].type == 'x') {
		return Xiang();
	}
	else if (Map[y][x].type == 'S' || Map[y][x].type == 's') {
		return Shi();
	}
	else if (Map[y][x].type == 'J' || Map[y][x].type == 'j') {
		return Jiang();
	}
	return false;
}
bool checkWin() {
	if (currentPiece == 'R') {
		for (int i = 0;i < 3;i++) {
			for (int j = 3;j < 6;j++) {
				if (Map[i][j].type == 'J') {
					return false;
				}
			}
		}
	}
	else {
		for (int i = 7;i < 10;i++) {
			for (int j = 3;j < 6;j++) {
				if (Map[i][j].type == 'j') {
					return false;
				}
			}
		}
	}
	return true;
}
void DrawTipText()
{
	static TCHAR str[20];
	if (currentPiece == 'R') {
		_stprintf_s(str, _T("当前为红方回合"));
	}
	else {
		_stprintf_s(str, _T("当前为黑方回合"));
	}
	settextcolor(RGB(225, 175, 45));
	outtextxy(0, 0, str);
}
int main() {
	initgraph(WIDTH, HEIGHT);
	loadPicture();
	initMap();
	initMyMouse();
	bool running = true;
	bool isMoving = false;
	bool RoundisEnd = false;
	MessageBox(GetHWnd(), _T("点击OK开始对局"), _T("红方先行！"), MB_OK);
	BeginBatchDraw();
	while (running) {
		DWORD startTime = GetTickCount();
		while (peekmessage(&m)) {
			int min = -1, max = -1;
			if (currentPiece == 'R') {
				min = 65;
				max = 90;
			}
			else {
				min = 97;
				max = 122;
			}
			int x, y;
			if (m.message == WM_LBUTTONDOWN) {
				x = (m.x - RADIUS) / (2 * RADIUS);
				y = (m.y - RADIUS) / (2 * RADIUS);
				if (isMoving) {
					MyMouse.endX = x;
					MyMouse.endY = y;
					RoundisEnd = judgePiece(MyMouse.startX, MyMouse.startY);
				}
				if (Map[y][x].isExist && Map[y][x].type >= min && Map[y][x].type <= max) {
					Map[y][x].isPicked = !Map[y][x].isPicked;
					pickPiece(x, y);
					isMoving = true;
					MyMouse.startX = x;
					MyMouse.startY = y;
				}
				if (RoundisEnd) {
					if (currentPiece == 'R') {
						currentPiece = 'B';
					}
					else {
						currentPiece = 'R';
					}
					pickPiece(-1, -1);
					isMoving = false;
					RoundisEnd = false;
				}
			}
		}
		drawBoard();
		DrawTipText();
		drawPiece();
		drawBiankuang();
		FlushBatchDraw();
		cleardevice();
		if (checkWin()) {
			if (currentPiece == 'R') {
				MessageBox(GetHWnd(), _T("黑方玩家获胜！"), _T("游戏结束！"), MB_OK);
				running = !checkWin();
			}
			else {
				MessageBox(GetHWnd(), _T("红方玩家获胜！"), _T("游戏结束！"), MB_OK);
				running = !checkWin();
			}
		}
		DWORD endTime = GetTickCount();
		DWORD deltaTime = endTime - startTime;
		if (deltaTime < 1000 / 60)
		{
			Sleep(1000 / 60 - deltaTime);
		}
	}
	EndBatchDraw();
	return 0;
}