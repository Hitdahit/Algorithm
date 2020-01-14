//https://www.acmicpc.net/problem/14501
//참고: https://velog.io/@skyepodium/%EB%B0%B1%EC%A4%80-14501-%ED%87%B4%EC%82%AC-exjyfr5vgj

#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
using namespace std;
typedef pair<int, int> pii;

int n;
int don[100];   //다 0으로 초기화
vector <pii> v;
int main()
{
	int t, p;
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> t >> p;
		v.push_back(make_pair(t, p));
	}

	int ans = 0;
	//매 반복마다 그날 상담을 한 경우, 안 한 경우 모두를 dp로 시뮬레이션.

	for (int i = 0; i < n; i++) {
		if (i + v[i].first < n + 1) {  //그날 상담을 한 경우
			//사실 상담이 퇴사날까지만 끝난다면,
			//그날 상담을 할지 말지는 경우의 수 문제임.
			//그러므로 모든 경우를 다 계산해주는 것.
			don[i + v[i].first] = max(don[i + v[i].first], don[i] + v[i].second);

			ans = max(ans, don[i + v[i].first]);
		}
		//그 날 상담을 하지 않은 경우
		don[i + 1] = max(don[i + 1], don[i]);

		ans = max(ans, don[i + 1]);
	}

	cout << ans;

}
