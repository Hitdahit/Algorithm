#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
using namespace std;
int n;
int stair[301] = {0, };
int score[301][2] = {0, };
/*
	풀이:
		우선, 내가 할 수 있는 행동 -> 계단을 1칸만 오른다.
									  계단을 2칸만 오른다.
		계단을 연속해서 3개까지 오를 수 없다.
		그렇다면 -> dp 풀이를 위해 우선 매 반복을 계단 3칸씩으로 정의.(한 번에 할 수 있는 행동의 제한 범위가 3칸이므로)
		score 배열은 매 반복 즉, i번째 계단에 j + 1 (1또는 2)번만에 오를때의 최대 점수를 기록할 것이다.
		만약 내가 3번째 계단에 1번에 올라간다는건, 1번째 계단에서 한번에 2칸을 올라갔단 뜻이다.
		
		만약 내가 3번째 계단에 2번에 올라간다는건, 1번째 계단에서 한칸씩 두번 올라갔단 뜻이다.

		그러나 문제의 제약조건에서 연속한 3칸을 올라가는 것이 불가능함을 알 수 있다,
		즉, 내가 만약에 어떤 계단에 2번에 올라간다는 것은, 이전 계단을 한번에 올라 갔었다는 뜻이다.

		그리고 내가 어떤 계단에 1번에 올라가는 것은 이전 계단의 시행에 대해 아무제약이 없으나, 우리는 점수의 최대합을 구하려 하므로, 
		이전 계단에서 한번에 올라갔던 두번에 올라갔던 점수가 큰 놈을 선택하면 된다. 

		즉 점화식은 아래와 같다.
		score[i][0] = max(score[i - 2][0], score[i - 2][1]) + stair[i];   //0, 1이 j자리.
		score[i][1] = score[i - 1][0] + stair[i];
*/
int main()
{
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> stair[i];

	score[1][0] = stair[1];
	score[2][0] = stair[2];   //현재 계단을 3칸씩 자른 상황을 가정했으므로, 초기 3개의 계단에 대한 초기화가 필요하다.
	score[2][1] = stair[2] + score[1][0];   //그리고 이것은 점화식에 따르면 자명

	for (int i = 3; i <= n; i++) {
		score[i][0] = max(score[i - 2][0], score[i - 2][1]) + stair[i];
		score[i][1] = score[i - 1][0] + stair[i];
	}
	
	cout << max(score[n][0], score[n][1]);

	return 0;
}
