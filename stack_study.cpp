//스택: 한 쪽 끝에서만 자료를 넣어줄 수 있는 자료구조.

/*
	restructed structure: 스택, 큐, 덱 등과 같이 특정 위치에서만 원소를 넣거나 뺄 수 있게 만든 자료구조.
		->대신 원소의 추가, 제거, 제일 상단의 원소 확인이 O(1)이다!

		스택은 원칙적으로 제일 상단이 아닌 나머지 원소들의 혹인/변경이 '원칙적'으로는 불가
		STL에서도 불가능. 그러나 배열을 이용해 구현하면 확인이 가능하긴 함.

	스택의 구현: 배열/연결리스트로 구현.
		 const int MX=12345678;
		 int dat[MX];
		 int pos = 0;  //다음원소가 들어갈 자리, 현재 스택내의 원소 갯수를 보여줌.

		 

*/
#include <iostream>
#include <stack>
using namespace std;
const int MX = 12345678;
int dat[MX];
int pos = 0;
void push(int x)
{
	dat[pos++] = x;
}
int pop() {
	return dat[pos--];
}
int top()
{
	return dat[pos - 1];
}

int main()
{
	stack <int> s;
	s.push(10);
	s.push(20);
	s.push(30);

	cout << s.size() << "\n";

	if (s.empty())cout << "s is empty" << "\n";
	else cout << "s is not empty" << "\n";

	s.pop();
	cout << s.top()<<"\t";

	s.pop();
	cout << s.top()<<"\t";

	s.pop();
	if (s.empty()) {
		cout << "s is empty" << endl;
		//이때 s.top(), s.pop()호출시 런타임 에러 발생함!
		//runtime err면 무조건 의심
	}

}
