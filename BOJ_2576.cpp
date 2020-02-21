#include <iostream>
using namespace std;
int main()
{
	int tmp, hap = 0, small = 101;

	for (int i = 0; i < 7; i++) {
		cin >> tmp;
		if (tmp % 2 == 1) {
			hap += tmp;
			if (small > tmp)small = tmp;
		}
	}
	if (hap == 0)cout << -1;
	else {
		cout << hap <<"\n";
		cout << small;
	}
	
}