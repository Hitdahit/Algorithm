#include <iostream>
#include <algorithm>
using namespace std;
int main()
{
	int a[5] = { 0, };
	int hap = 0;
	for (int i = 0; i < 5; i++) {
		cin >> a[i];
		hap += a[i];
	}
	sort(a, a + 5);

	cout << hap / 5 << "\n" << a[2];
}