#include<iostream>
using namespace std;
class Integer {
private:int num;
public:
	Integer(int n) {
		num = n;
	}
	int get() { return num; }
	void set(int n) {num = n; }
	bool isEven() {
		return !(num % 2);
	};
};
int main() {
	Integer n(30);
	cout << n.get() << ' ';
	n.set(50);
	cout << n.get() << ' ';
	Integer m(300);
	cout << m.get() << ' ';
	cout << m.isEven();
}