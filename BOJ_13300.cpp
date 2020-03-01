#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
using namespace std;
typedef pair<int, int> pii;   //first 해당학년 남학생수, second 해당학년 여학생 수
vector<pii>v;
int main()
{
	int n, k;
	cin >> n >> k;
	for (int i = 0; i < 6; i++) v.push_back(make_pair(0, 0));	

	int s, y;
	for (int i = 0; i < n; i++) {
		cin >> s >> y;
		if (!s)	v[y-1].second++;
		else v[y-1].first++;
	}
	
	int cnt=0;
	for (int i = 0; i < 6; i++) {
		if (!v[i].first)continue;
		if (v[i].first < k) cnt++;
		else {
			cnt += v[i].first / k + (v[i].first % k == 0) ? 1 : 0;
		}
	}

	for (int i = 0; i < 6; i++) {
		if (!v[i].second)continue;
		if (v[i].second < k) cnt++;
		else {
			cnt += v[i].second / k + (v[i].second % k == 0) ? 1 : 0;
		}
	}
	cout << cnt;
}
