//https://www.acmicpc.net/problem/1912
//dp
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
int n;
int v[100005] = { 0, };
int dp[100005] = { 0, };
/*
	dp[i] 연속된 숫자 i개 선택할때의 최대값을 가지고 있음. 
	-> 그거 말고, 선택한 숫자(들)의 마지막 인덱스가 i라고 하자. 
			단 선택한 숫자들이 주어진 배열에서 연속합이 최대임.

*/
int main()
{
	cin >> n;
	int tmp;
	for (int i = 1; i <= n; i++) cin >> v[i];

	dp[1] = v[1];
	for (int i = 2; i <= n; i++) {
		dp[i] = max(dp[i - 1], 0) + v[i];   //v[i]가 음수여도 어차피 작아지니까 마지막 줄에서 걸러짐. 참고로 벡터는 0index로 선언.

		//i-1번째 인덱스까지 계산한 값을 저장하게 됨.
	}

	sort(dp+1, dp + n  + 1);   //*max_element(dp+1, dp+n+1);
	cout << dp[n];

}
