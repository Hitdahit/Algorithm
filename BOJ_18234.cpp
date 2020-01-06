//https://www.acmicpc.net/problem/18234
#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;
typedef pair<long long, long long>pll;
long long n, t;
vector <pll> v;
int main()
{
	cin >> n >> t;
	int w, p;
	for (int i = 0; i < n; i++) {
		cin >> w >> p;
		v.push_back(make_pair(p, w));
	}

	sort(v.begin(), v.end());
	long long ans = 0;

	if (n != t) {
		for (int i = 0; i < n; i++) {
			v[i].second += v[i].first * (t - n);
		}
	}
	
	for (int i = 0; i < n; i++)
		ans += v[i].second + v[i].first * i;

	cout << ans;
}
