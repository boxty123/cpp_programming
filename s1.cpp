#include<iostream>
#include<string>
using namespace std;
int main() {
	string str[5];
	for (int i = 0; i < 5; i++)
	{
		cout << "�̸�>>"; getline(cin, str[i], '\n');
	}
	string biggest = str[0];
	for (int i = 1; i < 5; i++)
		if (str[i] > biggest)
			biggest = str[i];
	cout << "�������� ���� �ڿ� ������ ���ڿ��� " << biggest;

}