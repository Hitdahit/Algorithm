//https://www.acmicpc.net/problem/10808
//newly solved version
#include <iostream>
#include <cstring>
using namespace std;
int main()
{
	int a[26];
	memset(a, 0, sizeof a);
	string s;
	cin >> s;
	for (auto f : s)
		a[f - 'a']++;   //아스키코드 활용
	for (int i = 0; i < 26; i++)
		cout << a[i] << " ";
	                                        
}
