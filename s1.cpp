#include<iostream>
#include<string>
using namespace std;
int main() {
	string str[5];
	for (int i = 0; i < 5; i++)
	{
		cout << "이름>>"; getline(cin, str[i], '\n');
	}
	string biggest = str[0];
	for (int i = 1; i < 5; i++)
		if (str[i] > biggest)
			biggest = str[i];
	cout << "사전에서 가장 뒤에 나오는 문자열은 " << biggest;

}