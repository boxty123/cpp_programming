#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>//ǥ�� ����� ���̺귯��
#include <stdlib.h>//���� �޸� �Ҵ�� ���õ� �Լ��� ������ ���̺귯��
#include <string.h>//���ڿ� ó�� �Լ��� ������ ���̺귯��
#include <conio.h>//�ܼ� ������� ó���ϴ� �Լ��� ������ ���̺귯��
#include <memory.h>//�޸� ���� �Լ��� ������ ���̺귯��
#include <time.h>//�ð� ���� �Լ��� ������ ���̺귯��
#include <ctype.h>//���ڵ��� ���ǿ� �´��� �˻��ϴ� �Լ����� ������ ���̺귯�� 

#define DIM	9

enum LabelType { Empty = 0, Bomb = 9 };//���������� LabelType����
enum MaskType { Hide = 0, Open, Flag };//���������� MaskType����
int	nx = DIM, ny = DIM;
int	nBomb = DIM;

inline int& mask(int x, int y,int MineMapMask[][DIM]) { return MineMapMask[y][x]; }//MapMask[y][x]���� �����Ѵ�.
inline int& label(int x, int y, int MineMapLabel[][DIM]) { return MineMapLabel[y][x]; }//MapLabel[y][x]���� �����Ѵ�
inline bool	isValid(int x, int y) { return (x >= 0 && x < nx&& y >= 0 && y < ny); }//x,y�� ���ο� �ִ��� Ȯ���Ѵ�.
inline bool	isBomb(int x, int y, int MineMapLabel[][DIM]) { return isValid(x, y) && label(x, y,MineMapLabel) == Bomb; }//x,y�� ���ο� �ְ� MapLabel[y][x]�� Bomb�̸� true���� �ƴϸ� false����
inline bool	isEmpty(int x, int y, int MineMapLabel[][DIM] ) { return isValid(x, y) && label(x, y,MineMapLabel) == Empty; }//x,y�� ���ο� �ְ� MapLabel[y][x]�� Empty�� true���� �ƴϸ� false����

void dig(int x, int y, int MineMapMask[][DIM], int MineMapLabel[][DIM]) {//(x,y)�� �ֺ� (x,y)�� open���� �ٲ۴�. �ֺ��� ���ڰ� ���ٸ� �ֺ�8ĭ���� �Լ��� �ٽ� �����Ų��
	if (isValid(x, y) && mask(x, y, MineMapMask) != Open) {//MapMask[y][x]�� Open�� �ƴϰ� x,y�� ���ο��ִٸ�
		mask(x, y, MineMapMask) = Open;//MapMask[y][x]�� Open���� �ٲ�
		if (label(x, y, MineMapLabel) == 0) {//MapLabel[y][x]�� 0�̸� �����¿�밢�� 8�������� dig�Լ��� ��� ȣ���Ѵ�.
			dig(x - 1, y - 1, MineMapMask, MineMapLabel);
			dig(x - 1, y, MineMapMask, MineMapLabel);
			dig(x - 1, y + 1, MineMapMask, MineMapLabel);
			dig(x, y - 1, MineMapMask, MineMapLabel);
			dig(x, y + 1, MineMapMask, MineMapLabel);
			dig(x + 1, y - 1, MineMapMask, MineMapLabel);
			dig(x + 1, y, MineMapMask, MineMapLabel);
			dig(x + 1, y + 1, MineMapMask, MineMapLabel);
		}
	}
}
void mark(int x, int y, int MineMapMask[][DIM]) {//MapMask[y][x]�� Hide���� Flag���·� �ٲٴ� �Լ�.
	if (isValid(x, y) && mask(x, y,MineMapMask) == Hide)//x,y�� ���ο��ְ� MapMask�� Hide��
		mask(x, y, MineMapMask) = Flag;//MapMask[y][x]�� Flag���·� �ٲ۴�.
}
int getBombCount(int MineMapMask[][DIM]) {//��ü ���� ���ƴٴϸ� �߰��� ��� ������ �����Ѵ�.
	int count = 0;
	for (int y = 0; y < ny; y++)
		for (int x = 0; x < nx; x++)
			if (mask(x, y, MineMapMask) == Flag) count++;//MapMask[y][x]�� Flag�� count����
	return count;
}
void print(int MineMapMask[][DIM], int MineMapLabel[][DIM]) {//��ü �� ���
	system("cls");//���ȭ���� �ʱ�ȭ�Ѵ�.
	printf("   �߰�:%2d   ��ü:%2d\n", getBombCount(MineMapMask), nBomb);//
	printf("    �� �� �� �� �� �� �� �� ��\n");
	for (int y = 0; y < ny; y++) {
		printf("%2c ", 'A' + y);
		for (int x = 0; x < nx; x++) {
			if (mask(x, y, MineMapMask) == Hide)	printf(" ��");//MapMask[y][x]�� Hide�� �� ��� 
			else if (mask(x, y, MineMapMask) == Flag) printf("��");//MapMask[y][x]�� Flag�� �����
			else {
				if (isBomb(x, y, MineMapLabel)) printf(" ��");//MapLabel[y][x]�� Bomb�̸� �����
				else if (isEmpty(x, y, MineMapLabel)) printf("  ");//MapLabel[y][x]�� Empty�̸� " "���
				else printf("%2d", label(x, y, MineMapLabel));
			}
		}
		printf("\n");
	}
}
int countNbrBombs(int x, int y,int MineMapLabel[][DIM]) {//MapLabel[y][x]�ֺ��� Bomb���� ��ȯ
	int count = 0;
	for (int yy = y - 1; yy <= y + 1; yy++)//Label[y][x]�� �ֺ� 8���� Ž���ϸ�
		for (int xx = x - 1; xx <= x + 1; xx++)
			if (isValid(xx, yy) && label(xx, yy, MineMapLabel) == Bomb)// xx,yy�� ���ο� �ְ� MapLabel[yy][xx]�� Bomb�̸� count����
				count++;
	return count;
}
void init(int MineMapMask[][DIM], int MineMapLabel[][DIM],int total = 9) {//�ʱ�ȭ �Լ�
	srand((unsigned int)time(NULL));//�õ尪 ���� ����
	for (int y = 0; y < ny; y++)//��ü ���� Ž���ϸ�
		for (int x = 0; x < nx; x++) {
			mask(x, y, MineMapMask) = Hide; //MapMask[y][x]�� Hide�� �ٲ۴�.
			label(x, y, MineMapLabel) = 0;//MapLabel[y][x]�� 0 ���� �ٲ۴�.
		}
	nBomb = total;//�ż��� ������ ��
	for (int i = 0; i < nBomb; i++) {//��ź�� nBomb�� �� ������ ����
		int x, y;
		do {//MapLabel[y][x]�� Empty�� �ƴҶ����� x,y�� ���� ����
			x = rand() % nx;
			y = rand() % ny;
		} while (label(x, y, MineMapLabel) != Empty);
		label(x, y, MineMapLabel) = Bomb; //MapLabel[y][x]�� Bomb�� ����
	}
	for (int y = 0; y < ny; y++)//��ü MapLabel�� Ž���ϸ�
		for (int x = 0; x < nx; x++)
			if (label(x, y, MineMapLabel) == Empty)//MapLabel[y][x]�� Empty���
				label(x, y, MineMapLabel) = countNbrBombs(x, y, MineMapLabel);//MapLabel[y][x]�� (x,y)�ֺ� ��ź�� ���� ������ �ش�.
}
bool getPos(int& x, int& y) {//open�� �ϰų� ����� ���� ��ǥ�� �Է¹޴´�.
	printf("\n����(P)��(A-I)��(1-9)\n      �Է� --> ");
	bool isBomb = false;
	y = toupper(_getch()) - 'A';//�� ��ǥ�� �Է¹޾� �빮�ڷ� ��ȯ
	if (y == 'P' - 'A') { //'p'�� �Է��ϸ� isBomb�� true�� �����ϰ� �� ��ǥ �Է�
		isBomb = true;
		y = toupper(_getche()) - 'A';
	}
	x = _getch() - '1';//�� ��ǥ �Է¹޾� ������ ��ȯ
	return isBomb; //��ź���� ��ǥ���� ��ȯ
}
int checkDone(int MineMapMask[][DIM],int MineMapLabel[][DIM]) {//������ ������ �Ǵ��� Ȯ���Ѵ�.
	int count = 0;
	for (int y = 0; y < ny; y++)//��ü ���� Ž���ϸ�
		for (int x = 0; x < nx; x++) {
			if (mask(x, y, MineMapMask) != Open) count++;//MapMask[y][x]�� Open�� �ƴϸ� ī��Ʈ ����
			else if (isBomb(x, y, MineMapLabel)) return -1;//MapLabel[y][x]�� Bomb�� -1����
		}
	return (count == nBomb) ? 1 : 0; //count�� nBomb(�ż��� ���ڼ�)�� ������1 �ƴϸ� 0 ����
}
void playMineSweeper(int total,int MineMapMask[][DIM],int MineMapLabel[][DIM]) {//��ü���� �ڵ带 �����ϴ� �Լ�
	int x, y, status;
	init(MineMapMask, MineMapLabel,total);//�ʱ�ȭ �Լ� ȣ��
	do {//status�� 0�̸� �ݺ�
		print(MineMapMask, MineMapLabel);//�� ���
		bool isBomb = getPos(x, y);
		if (isBomb) mark(x, y, MineMapMask);//isBomb�� true��� MapMask[y][x]�� Hide���� Flag�� �ٲ�
		else		  dig(x, y, MineMapMask, MineMapLabel);//false�� (x,y)�� Ž���ϸ� �ֺ��� Open�Ѵ�
		status = checkDone(MineMapMask,MineMapLabel);//��� ���ڸ� ã���� status�� 1�� �ٲ۴�.
	} while (status == 0);
	print(MineMapMask, MineMapLabel);//����Լ�
	if (status < 0)// ���ڸ� ����������
		printf("\n����: ���� ����!!!\n\n");
	else	printf("\n����: Ž�� ����!!!\n\n");
}
void main()
{
	int	MineMapMask[DIM][DIM];//9x9 �������迭 ����
	int MineMapLabel[DIM][DIM];//9x9 �������迭 ����
	int total;
	printf(" <Mine Sweeper>\n");
	printf(" �ż��� �� ������ ���� �Է� : ");
	scanf("%d", &total);
	playMineSweeper(total, MineMapMask, MineMapLabel);//���ӽ���
}