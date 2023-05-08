#include<iostream>
#include"Container.h"
using namespace std;
class CoffeeVendingMachine {
	Container tong[3];
	void fill() { for (int i = 0; i < 3; i++) tong[i].fill(10); }
	void selectEspresso() {
		tong[0].consume(1);
		tong[1].consume(1);
		cout << "에스프레소 입니다\n";
	}// 에스프레소를 선택한 경우, 커피 1, 물 1 소모
	void selectAmericano() {
		tong[0].consume(1);
		tong[1].consume(2);
		cout << "아메리카노 입니다\n";
	}// 아메리카노를 선택한 경우, 커피 1, 물 2 소모
	void selectSugarCoffee() {
		tong[0].consume(1);
		tong[1].consume(2);
		tong[2].consume(1);
		cout << "설탕커피 입니다\n";
	}// 설탕커피를 선택한 경우, 커피 1, 물 2 소모, 설탕 1 소모
	void show() {
		cout <<"커피: "<<tong[0].getSize() <<", 물: " << tong[1].getSize() <<", 설탕: "<< tong[2].getSize()<<"\n";
	} // 현재 커피, 물, 설탕의 잔량 출력
public:
	void run();
};
void CoffeeVendingMachine::run() {
	cout << ("***커피 자판기를 작동합니다.***\n");
	while (tong[0].getSize() > 0 && tong[1].getSize() > 0 && tong[2].getSize()> 0) {
		cout << "메뉴를 눌러주세요(1.에스프레소 2:아메리카노 3:설탕커피 4.잔량보기 5:채우기)>>";
		int num;
		cin >> num;
		switch (num)
		{
		case 1:
			selectEspresso();
			break;
		case 2:
			selectAmericano();
			break;
		case 3:
			selectSugarCoffee();
			break;
		case 4:
			show();
			break;
		case 5:
			fill();
			show();
			break;
		}
	}
}
int main() {
	CoffeeVendingMachine C_V_M;
	C_V_M.run();
}