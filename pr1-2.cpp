#include<iostream>
using namespace std;
class Circle {
	int radius;
public:
	static int cnt;
	void setRaduis(int radius) { this->radius = radius; }
	double getArea() {
		return 3.14 * radius * radius;
	}
};
int  Circle::cnt = 0;
int main() {
	int radius;
	Circle obj[3];
	for (int i = 0; i < 3; i++)
	{
		cout << "원 " << i+1 << "의 반지름 >>\n";
		cin >> radius;
		obj[i].setRaduis(radius);
		if (obj[i].getArea() > 100) Circle::cnt++;
	}
	cout << "면적이 100보다 큰 원" << Circle::cnt << "개 입니다.";
}