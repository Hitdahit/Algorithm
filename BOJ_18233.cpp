//https://www.acmicpc.net/problem/18233

#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
using namespace std;
typedef pair<int, int> pii;
int n, e, p;
int main()
{
	int x, y;
	vector <pii> v;
	cin >> n >> p >> e;
	int *ans = (int*)malloc(sizeof(int) * n);
	for (int i = 0; i < n; i++) ans[i] = -1;

	int *comb = (int*)malloc(sizeof(int) * n);
	for (int i = 0; i < n; i++) {
		if (i < p) comb[i] = 0;
		else comb[i] = 1;
	}

	for (int i = 0; i < n; i++) {
		cin >> x >> y;
		v.push_back(make_pair(y, x));
	}

	int hap = 0;
	do {
		hap = 0;
		for (int i = 0; i < n; i++) {
			if (!comb[i]) hap += v[i].second;  //n개 중 p개 뽑는 조합.
		}
		if (hap <= e) {
			for (int i = 0; i < n; i++) {
				if (!comb[i]) ans[i] = v[i].second;
				else ans[i] = 0;
			}
			break;
		}
	} while (next_permutation(comb, comb + n));

	if (ans[0] == -1) {
		cout << -1;
		return 0;
	}
	int flag = 0;
	while (e != hap) {
		flag = 0;
		for (int i = 0; i < n; i++) {
			if (ans[i])
				if (v[i].first > ans[i] && hap != e) {
					ans[i]++;
					hap++; flag = 1;
				}

		}
		if (!flag) {
			cout << -1; return 0;
		}
	}

	for (int i = 0; i < n; i++) {
		cout << ans[i] << " ";
	}

}
