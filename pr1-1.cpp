#include<iostream>
using namespace std;
class Circle {
	int radius;
	
public:
	void setRaduis(int radius) { this->radius = radius; }
	double getArea() {
		return 3.14 * radius * radius;
	}
};
int main() {
	int cnt = 0;
	int radius;
	Circle obj[3];
	for (int i = 0; i < 3; i++)
	{
		cout << "�� " << i+1 << "�� ������ >>\n";
		cin >> radius;
		obj[i].setRaduis(radius);
		if (obj[i].getArea() > 100) cnt++;
	}
	cout << "������ 100���� ū ��" << cnt << "�� �Դϴ�.";
}