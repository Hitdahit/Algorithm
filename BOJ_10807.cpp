#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
int main()
{
    int n, tmp, cnt = 0;
    cin >> n;

    vector <int> v;
    for (int i = 0; i < n; i++) {
        cin >> tmp;
        v.push_back(tmp);
    }
    cin >> tmp;
    
    for (auto i : v) 
        if (tmp == i)cnt++;
    
    cout << cnt;
}
