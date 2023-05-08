#include<iostream>
#include"Container.h"
using namespace std;
class CoffeeVendingMachine {
	Container tong[3];
	void fill() { for (int i = 0; i < 3; i++) tong[i].fill(10); }
	void selectEspresso() {
		tong[0].consume(1);
		tong[1].consume(1);
		cout << "���������� �Դϴ�\n";
	}// ���������Ҹ� ������ ���, Ŀ�� 1, �� 1 �Ҹ�
	void selectAmericano() {
		tong[0].consume(1);
		tong[1].consume(2);
		cout << "�Ƹ޸�ī�� �Դϴ�\n";
	}// �Ƹ޸�ī�븦 ������ ���, Ŀ�� 1, �� 2 �Ҹ�
	void selectSugarCoffee() {
		tong[0].consume(1);
		tong[1].consume(2);
		tong[2].consume(1);
		cout << "����Ŀ�� �Դϴ�\n";
	}// ����Ŀ�Ǹ� ������ ���, Ŀ�� 1, �� 2 �Ҹ�, ���� 1 �Ҹ�
	void show() {
		cout <<"Ŀ��: "<<tong[0].getSize() <<", ��: " << tong[1].getSize() <<", ����: "<< tong[2].getSize()<<"\n";
	} // ���� Ŀ��, ��, ������ �ܷ� ���
public:
	void run();
};
void CoffeeVendingMachine::run() {
	cout << ("***Ŀ�� ���Ǳ⸦ �۵��մϴ�.***\n");
	while (tong[0].getSize() > 0 && tong[1].getSize() > 0 && tong[2].getSize()> 0) {
		cout << "�޴��� �����ּ���(1.���������� 2:�Ƹ޸�ī�� 3:����Ŀ�� 4.�ܷ����� 5:ä���)>>";
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