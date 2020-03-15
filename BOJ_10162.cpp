//https://www.acmicpc.net/problem/10162
#include <iostream>
#include <stack>
using namespace std;
int a = 300, b = 60, c = 10;
int t;
int main()
{
	cin >> t;
	int ans[3] = { 0, };

	if (t % 10 != 0) {
		cout << -1;
		return 0;
	}

	if (t / a != 0) {
		ans[0] = t / a;
		t %= a;
	}
	if (t / b != 0) {
		ans[1] = t / b;
		t %= b;
	}
	if (t / c != 0) {
		ans[2] = t / c;
		t %= c;
	}
	cout << ans[0] << " " << ans[1] << " " << ans[2] << endl;
}
