	배열 사용팁
	1. 초기화방법
	#include <cstring>  //memset
	#include <algorithm> //fill
	int main()
	{
		int a[21];
		int b[21][21];

		//memset 사용하기
		memset(a, 0, sizeof a);
		memset(b, 0, sizeof b);

		//fill 사용하기
		fill(a, a + 21, 0);
		for(int i = 0; i < 21; i++){
			fill(b[i], b[i]+21, 0);
		}
	}

	벡터 함수  //v.begin(), v.end()애용.
	v.push_back(값);
	v.pop_back();
	v.erase(인덱스);        O(N)
   	v.insert(인덱스, 값);   O(N)
 	v.clear();

	 for(auto i: v) 와
	 for(auto& i:v)를 구별   -> 참조니까 배열값이 바뀜
	 v.size()는  unsigned int 그러니까 뺄셈같은거 하지 말자.
	 =>벡터 비어있을때 에러 나기 쉽다.
