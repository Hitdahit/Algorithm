//https://www.acmicpc.net/problem/10870

#include <iostream>
using namespace std;

int n;
int f2 = 0;
int fib(int n) 
{
	if (n > 1) {
		f2 = fib(n-1) + fib(n-2);
	}
	else if (n == 1) {
		f2 = 1;
	}
	return f2;
}
int main()
{
	cin >> n;

	if (n == 0) {
		cout << 0;
		return 0;
	}
	else if (n == 1) {
		cout << 1;
		return 0;
	}
	else {
		cout << fib(n-1);
	}

}
