#include<iostream>
#include<vector>
#include<string>
using namespace std;
int main() {
	vector<string>str;
	cout << "이름을 5개 입력하라" << "\n";
	string temp;
	for (int i = 0; i < 5; i++)
	{
		getline(cin, temp, '\n');
		str.push_back(temp);
	}
	string biggest = str[0];
	for (int i = 1; i < 5; i++)
		if (biggest < str[i])
			biggest = str[i];
	cout << "사전에서 가장 뒤에 나오는 이름은 " << biggest;
}
