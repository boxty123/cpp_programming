#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>//표준 입출력 라이브러리
#include <stdlib.h>//동적 메모리 할당과 관련된 함수를 포함한 라이브러리
#include <string.h>//문자열 처리 함수를 포함한 라이브러리
#include <conio.h>//콘솔 입출력을 처리하는 함수를 포함한 라이브러리
#include <memory.h>//메모리 조작 함수를 포함한 라이브러리
#include <time.h>//시간 관련 함수를 포함한 라이브러리
#include <ctype.h>//문자들을 조건에 맞는지 검사하는 함수들을 포함한 라이브러리 

#define DIM	9

enum LabelType { Empty = 0, Bomb = 9 };//열거형변수 LabelType선언
enum MaskType { Hide = 0, Open, Flag };//열거형변수 MaskType선언
int	nx = DIM, ny = DIM;
int	nBomb = DIM;

inline int& mask(int x, int y,int MineMapMask[][DIM]) { return MineMapMask[y][x]; }//MapMask[y][x]값을 리턴한다.
inline int& label(int x, int y, int MineMapLabel[][DIM]) { return MineMapLabel[y][x]; }//MapLabel[y][x]값을 리턴한다
inline bool	isValid(int x, int y) { return (x >= 0 && x < nx&& y >= 0 && y < ny); }//x,y가 내부에 있는지 확인한다.
inline bool	isBomb(int x, int y, int MineMapLabel[][DIM]) { return isValid(x, y) && label(x, y,MineMapLabel) == Bomb; }//x,y가 내부에 있고 MapLabel[y][x]가 Bomb이면 true리턴 아니면 false리턴
inline bool	isEmpty(int x, int y, int MineMapLabel[][DIM] ) { return isValid(x, y) && label(x, y,MineMapLabel) == Empty; }//x,y가 내부에 있고 MapLabel[y][x]가 Empty면 true리턴 아니면 false리턴

void dig(int x, int y, int MineMapMask[][DIM], int MineMapLabel[][DIM]) {//(x,y)와 주변 (x,y)를 open으로 바꾼다. 주변에 지뢰가 없다면 주변8칸에서 함수를 다시 실행시킨다
	if (isValid(x, y) && mask(x, y, MineMapMask) != Open) {//MapMask[y][x]가 Open이 아니고 x,y가 내부에있다면
		mask(x, y, MineMapMask) = Open;//MapMask[y][x]를 Open으로 바꿈
		if (label(x, y, MineMapLabel) == 0) {//MapLabel[y][x]가 0이면 상하좌우대각선 8방향으로 dig함수를 재귀 호출한다.
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
void mark(int x, int y, int MineMapMask[][DIM]) {//MapMask[y][x]를 Hide에서 Flag상태로 바꾸는 함수.
	if (isValid(x, y) && mask(x, y,MineMapMask) == Hide)//x,y가 내부에있고 MapMask가 Hide면
		mask(x, y, MineMapMask) = Flag;//MapMask[y][x]를 Flag상태로 바꾼다.
}
int getBombCount(int MineMapMask[][DIM]) {//전체 맵을 돌아다니며 발견한 깃발 개수를 리턴한다.
	int count = 0;
	for (int y = 0; y < ny; y++)
		for (int x = 0; x < nx; x++)
			if (mask(x, y, MineMapMask) == Flag) count++;//MapMask[y][x]가 Flag면 count증가
	return count;
}
void print(int MineMapMask[][DIM], int MineMapLabel[][DIM]) {//전체 맵 출력
	system("cls");//출력화면을 초기화한다.
	printf("   발견:%2d   전체:%2d\n", getBombCount(MineMapMask), nBomb);//
	printf("    ① ② ③ ④ ⑤ ⑥ ⑦ ⑧ ⑨\n");
	for (int y = 0; y < ny; y++) {
		printf("%2c ", 'A' + y);
		for (int x = 0; x < nx; x++) {
			if (mask(x, y, MineMapMask) == Hide)	printf(" □");//MapMask[y][x]가 Hide면 □ 출력 
			else if (mask(x, y, MineMapMask) == Flag) printf("¤");//MapMask[y][x]가 Flag면 ¤출력
			else {
				if (isBomb(x, y, MineMapLabel)) printf(" ※");//MapLabel[y][x]가 Bomb이면 ※출력
				else if (isEmpty(x, y, MineMapLabel)) printf("  ");//MapLabel[y][x]가 Empty이면 " "출력
				else printf("%2d", label(x, y, MineMapLabel));
			}
		}
		printf("\n");
	}
}
int countNbrBombs(int x, int y,int MineMapLabel[][DIM]) {//MapLabel[y][x]주변에 Bomb수를 반환
	int count = 0;
	for (int yy = y - 1; yy <= y + 1; yy++)//Label[y][x]의 주변 8곳을 탐색하며
		for (int xx = x - 1; xx <= x + 1; xx++)
			if (isValid(xx, yy) && label(xx, yy, MineMapLabel) == Bomb)// xx,yy가 내부에 있고 MapLabel[yy][xx]가 Bomb이면 count증가
				count++;
	return count;
}
void init(int MineMapMask[][DIM], int MineMapLabel[][DIM],int total = 9) {//초기화 함수
	srand((unsigned int)time(NULL));//시드값 랜덤 설정
	for (int y = 0; y < ny; y++)//전체 맵을 탐색하며
		for (int x = 0; x < nx; x++) {
			mask(x, y, MineMapMask) = Hide; //MapMask[y][x]를 Hide로 바꾼다.
			label(x, y, MineMapLabel) = 0;//MapLabel[y][x]를 0 으로 바꾼다.
		}
	nBomb = total;//매설할 지뢰의 수
	for (int i = 0; i < nBomb; i++) {//폭탄을 nBomb개 다 심을때 까지
		int x, y;
		do {//MapLabel[y][x]가 Empty가 아닐때까지 x,y값 랜덤 설정
			x = rand() % nx;
			y = rand() % ny;
		} while (label(x, y, MineMapLabel) != Empty);
		label(x, y, MineMapLabel) = Bomb; //MapLabel[y][x]를 Bomb로 설정
	}
	for (int y = 0; y < ny; y++)//전체 MapLabel을 탐색하며
		for (int x = 0; x < nx; x++)
			if (label(x, y, MineMapLabel) == Empty)//MapLabel[y][x]가 Empty라면
				label(x, y, MineMapLabel) = countNbrBombs(x, y, MineMapLabel);//MapLabel[y][x]에 (x,y)주변 폭탄의 수를 값으로 준다.
}
bool getPos(int& x, int& y) {//open을 하거나 깃발을 꽂을 좌표를 입력받는다.
	printf("\n지뢰(P)행(A-I)열(1-9)\n      입력 --> ");
	bool isBomb = false;
	y = toupper(_getch()) - 'A';//행 좌표를 입력받아 대문자로 변환
	if (y == 'P' - 'A') { //'p'를 입력하면 isBomb을 true로 설정하고 열 좌표 입력
		isBomb = true;
		y = toupper(_getche()) - 'A';
	}
	x = _getch() - '1';//열 좌표 입력받아 정수로 변환
	return isBomb; //폭탄인지 좌표인지 반환
}
int checkDone(int MineMapMask[][DIM],int MineMapLabel[][DIM]) {//게임을 끝내도 되는지 확인한다.
	int count = 0;
	for (int y = 0; y < ny; y++)//전체 맵을 탐색하며
		for (int x = 0; x < nx; x++) {
			if (mask(x, y, MineMapMask) != Open) count++;//MapMask[y][x]가 Open이 아니면 카운트 증가
			else if (isBomb(x, y, MineMapLabel)) return -1;//MapLabel[y][x]가 Bomb면 -1리턴
		}
	return (count == nBomb) ? 1 : 0; //count가 nBomb(매설한 지뢰수)와 같으면1 아니면 0 리턴
}
void playMineSweeper(int total,int MineMapMask[][DIM],int MineMapLabel[][DIM]) {//전체적인 코드를 실행하는 함수
	int x, y, status;
	init(MineMapMask, MineMapLabel,total);//초기화 함수 호출
	do {//status가 0이면 반복
		print(MineMapMask, MineMapLabel);//맵 출력
		bool isBomb = getPos(x, y);
		if (isBomb) mark(x, y, MineMapMask);//isBomb가 true라면 MapMask[y][x]를 Hide에서 Flag로 바꿈
		else		  dig(x, y, MineMapMask, MineMapLabel);//false면 (x,y)를 탐색하며 주변을 Open한다
		status = checkDone(MineMapMask,MineMapLabel);//모든 지뢰를 찾으면 status를 1로 바꾼다.
	} while (status == 0);
	print(MineMapMask, MineMapLabel);//출력함수
	if (status < 0)// 지뢰를 선택했으면
		printf("\n실패: 지뢰 폭발!!!\n\n");
	else	printf("\n성공: 탐색 성공!!!\n\n");
}
void main()
{
	int	MineMapMask[DIM][DIM];//9x9 이차원배열 선언
	int MineMapLabel[DIM][DIM];//9x9 이차원배열 선언
	int total;
	printf(" <Mine Sweeper>\n");
	printf(" 매설할 총 지뢰의 개수 입력 : ");
	scanf("%d", &total);
	playMineSweeper(total, MineMapMask, MineMapLabel);//게임시작
}