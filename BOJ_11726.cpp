//https://www.acmicpc.net/problem/11726
//dp
#include <iostream>
#include <algorithm>
using namespace std;
/*
	dp[i]  2*i를 채우는 모든 가짓수의 갯수.
	dp[1]=1
	dp[2]=2
	dp[3]=3
	dp[4]=5
	   "
	   "
	   "
*/
int dp[1001] = { 0, };
int main()
{
	int n;
	cin >> n;

	dp[1] = 1;
	dp[2] = 2;
	for (int i = 3; i <= n; i++) {
		dp[i] = (dp[i - 1] + dp[i - 2])%10007;   //오버플로 조심.
	}

	cout << dp[n];
}
