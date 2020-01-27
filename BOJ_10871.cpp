//  1984kb, 348ms. 
#include <iostream>
using namespace std;
int n, key;
int main() {	
	cin >> n >> key;
  int tmp;
	for (int i = 0; i < n; i++) {
      cin >> tmp;
      if(tmp < key) cout << tmp << " ";
	}
}

//  2120kb, 4ms.
#include <vector>
#include <iostream>
using namespace std;
int main()
{
	int N, X, a;
	cin >> N >> X;
	vector <int> A;
	for (int i = 0; i < N; i++){
		cin >> a;
		A.push_back(a);
	}
	for (int i = 0; i < N; i++)	{
		if (A.at(i) < X)
			cout << A.at(i)<<" ";
	}
}


//dunno which is better
