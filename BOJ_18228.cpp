#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
using namespace std;

int n;
vector <int> x;
vector <int> y;
int main()
{
	int idx;
	cin >> n;
	int *a = (int *)malloc(sizeof(int)*n);
	for (int i = 0; i < n; i++) {
		cin >> a[i];
		if (a[i] == -1) idx = i;
	}

	for (int i = 0; i < idx; i++) 
		x.push_back(a[i]);
	for (int i = idx + 1; i < n; i++) 
		y.push_back(a[i]);
	
	sort(x.begin(), x.end());
	sort(y.begin(), y.end());

	cout << x[0] + y[0];
}
