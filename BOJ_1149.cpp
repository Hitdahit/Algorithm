// https://www.acmicpc.net/problem/1149
//DP
#include <iostream>
#include <algorithm>
using namespace std;
int cost[1001][3] = {0, };
int ans[1001][3] = { 0, };
int n;
/*
	ans[i][0] -> i번째 집을 빨간색으로 칠할떄 i번째 집까지 칠했을때의 최소비용.
*/
int main()
{
	cin >> n;
	for (int i = 1; i <= n; i++) {
		int r, g, b;
		cin >> r >> g >> b;
		cost[i][0] = r;
		cost[i][1] = g;
		cost[i][2] = b;
	}
	ans[1][0] = cost[1][0];
	ans[1][1] = cost[1][1];
	ans[1][2] = cost[1][2];
	for (int i = 2; i <= n; i++) {
		ans[i][0] = min(ans[i - 1][1], ans[i - 1][2]) + cost[i][0];
		ans[i][1] = min(ans[i - 1][0], ans[i - 1][2]) + cost[i][1];
		ans[i][2] = min(ans[i - 1][0], ans[i - 1][1]) + cost[i][2];
	}

	cout << min(min(ans[n][0], ans[n][1]), ans[n][2]);
}
