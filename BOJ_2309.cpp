//https://www.acmicpc.net/problem/2309

#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
using namespace std;

int main()
{
	vector <int> v;
	int tmp, exceed = 0;
	for (int i = 0; i < 9; i++) {
		cin >> tmp;
		exceed += tmp;
		v.push_back(tmp);
	}

	sort(v.begin(), v.end());
	exceed -= 100;

	int hap = 0, flag = 0;
	for (int i = 0; i < 9; i++) {
		for (int j = i + 1; j < 9; j++) {
			
			hap = v[i] + v[j];
			if (hap == exceed) {
				flag = 1;
				v.erase(v.begin() + i);
				v.erase(v.begin() + j - 1);
				break;
			}
		}
		if (flag) break;
	}

	for (int i = 0; i < 7; i++) {
		cout << v[i] << endl;
	}
}
*/
