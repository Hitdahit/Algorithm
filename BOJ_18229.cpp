// https://www.acmicpc.net/problem/18229
#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#define INF 100000000
using namespace std;

int n, m, k;
int main()
{
	cin >> n >> m >> k;
	
	int *p = (int*)malloc(sizeof(int)*n);
	for (int i = 0; i < n; i++)p[i] = 0;

	int **a = (int**)malloc(sizeof(int*)*n);
	for (int i = 0; i < n; i++) 
		a[i] = (int*)malloc(sizeof(int)*m);
	
	for (int i = 0; i < n; i++) 
		for (int j = 0; j < m; j++) 
			cin >> a[i][j];
	
	int flag = 0;
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			p[j] += a[j][i];

			if (p[j] >= k) {
				cout << j + 1 << " " << i + 1;
				flag = 1;
				break;
			}
		}
		if (flag)break;
	}
	return 0;

}
