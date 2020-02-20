/*
	1, 8, 3, 5
	ch11. 친구관계와 연산자 오버로딩
		
		친구관계:
			객체지향 언어의 클래스는 기본적으로 접근 지정자를 가지고 있고, public으로 선언되지 않았다면 그 멤버에 대한 접근은 차단된다.

			만약, 클래스 내부에서 friend지정자를 사용해서 외부의 다른 함수/클래스를 친구로 선언한다면,
			상속관계가 없더라도 친구로 선언된 외부의 함수/클래스에서 friend가 선언된 클래스 내부의 모든 멤버로의 접근이 허용된다.
			ex.
			함수에서 friend 지정자 쓰기.
			class Ours;   //전방선언.
			class Friends{
			public:
				int Func1(Ours& b);
			private:
				int Func2(Ours& b);
			};
			class Ours{
			private:
				int _b;
				//함수를 친구로 선언하기
				friend int Friends::Func1(Ours& b);   //Func1은 이제 Ours의 _b에 맘대로 접근이 가능.
			};
			
			class otherclass;
			class yourclass{
				friend class otherclass;   //클래스를 친구로 선언하기
			private:
				int top;
			};

			class otherclass{
			public:
				void change(yourclass& yc, int x){
					yc.top = x;
				}
			}
			//yourclass내부에서 other클래스를 친구라고 선언했기 때문에 other는 your로 모두 접근이가능, 그러나 other는 your로 접근불가.

			friend함수 특징:
				-클래스 내/외에서 정의가 가능.
				-클래스 내부에서 선언한 friend 함수는 접근지정자와 상관없이 그 클래스의 모든 멤버에 접근이 가능하다
				-friend 함수가 클래스내부에서 정의된다 하더라도 그 함수는 일단 외부함수로 취급된다.
				-연산자 오버로딩을 위해서 만든 개념. 그러나 캡슐화/정보은닉의 관점에서 규칙에 어긋나는 개념. 그러므로 
				자바는 연산자오버로딩을 제공하지 않는다.
				-전역함수역시 클래스 내부에서 친구로 선언해서 사용할 수 있다.
				-컴파일러는 friend 지정자를 먹인 함수를 extern 지정자 먹인 함수처럼 취급한다.
					=> extern 지정자를 먹은 변수는 반드시 사용하지 않으면 컴파일에러가 발생.
		****
		*함수와 연산자 검색 과정.(중요)
		1. 함수/연산자가 범위확인 연산자와 함께 아래와 같이 정규화 되어 있다면, 
			this->name=(char*)std::malloc(strlen(name)+1)
			우선적으로 네임스페이스를 제공하는 라이브러리에서 함수를 찾는다.

		2. 변수타입에 따라 상속 관계에 있는 모든 클래스의 멤버 함수 가운데 인수 갯수와 타입이 맞는
			함수 오버로딩을 찾는다.

		3. 함수/연산자가 클래스의 멤버함수가 아니라면 컴파일러는 해당 프로그램 내에서 전역함수 혹은
			람다와 같은 지역함수를 찾는다. 맞는 함수를 찾았다면, 그것을 호출한다.

		4. 위의 과정에서 함수/연산자 오버로딩을 찾지 못했다면 ADL(인수의존검색)을 수행한다.
		*ADL: 함수 내 인수의 데이터 타입을 통해 해당함수를 찾는 기법.

		**오버로딩시 함수의 인수순서에 항상 주의할 것.
		**만약 클래스 내부에서 friend지정자를 사용하여 함수를 선언하였다면 외부에서 함수를 정의할 때 friend지정자를 삭제해 주어야 한다.
		**friend 지정자는 오로지 접근지정자가 있는 클래스 내부에서만 사용가능하기 때문.
		**친구 관계로 선언된 함수나 클래스에 대해서 선언문과 정의문을 구별해준다면 함수검색의 시간을 줄일 수 있다.

		반복작업: ??뭔소리여

		-객체 접근 제한과 클래스 접근 제한:
			자바는 객체를 중심으로 접근 제한을 두고 있으므로, 같은 클래스에서 생성된 서로다른 객체끼리도 private이 씌워져 있다면 접근을 금지함.
			그러나 C++은 가능!(클래스 접근제한.)

		-친구관계와 클래스 상속 주의점:
			1. 클래스 간의 상속이 이루어지더라도 친구관계는 상속되지 않는다.
			2. 클래스와 클래스가 서로 친구관계이더라도 친구의 친구 사이에 접근은 불가능하다. 




	-연산자 오버로딩: 좋은점도 있지만, 클래스가 복잡해지게 만든다는 단점.
		산술, 비트 연산자는 어렵지 않지만, 함수호출연산자(), 배열 인덱스 연산자 [], 간접 참조연산자 *의 오버로딩은 암시적 생성자- 대입 연산자를 주의 깊게 봐야함.

		-연산자 오버로딩의 제한: 오버로딩 할 수 없는 연산자(범위확인연산자::, 멤버선택연산자., 삼항연산자?:)
				논리연산자의 오버로딩은 성능저하로 이어질 수 있다.

		연산자 오버로딩 형식:
			리턴타입_자리 operator연산자_자리(인수){
			
			}
		ex. 만약 특정 클래스의 덧셈 연산자를 오버로딩한 경우.
		A a;
		A b;
		a+b, a.operator+(b); 와 같이 사용할 수 있다.

		클래스 내 멤버 연산자 오버로딩: 자기 자신을 기준으로 같은 클래스 타입의 인수 또는 다른 데이터 타입의 인수와의 연산작업을 수행하는 함수 오버로딩.
		전역 연산자 오버로딩: 자기자신이 기준이 되지 않는 연산을 오버로딩할 때 사용.
		
		*** 단항 연산자, 이항연산자는 멤버연산자 오버로딩과 전역 연산자 오버로딩으로 정의 할 수 있지만,
			대입 연산자, 함수호출연산자, 배열 인덱스 연산자, 포인터 멤버선택연산자는 오로지 클래스의 멤버 연산자 오버로딩으로만 정의가 가능하다.

			그외에 다른 연산자들은 클래스 멤버 연산자, 전역 연산자 오버로딩 모두 가능하나 권고 사항이 있다.
				그 중 중요한 것. -> 연산자 오버로딩은 new, delete를 제외하고 전역연산자 오버로딩과
									구별이 어렵다는 특성 때문에 static 지정자를 잘 쓰지 않는다.
		
		연산자 오버로딩 3기본법칙:
			1. 연산자의 기능이 분명치 않거나 논쟁의 소지가 있다면, 해당 연산자는 오버로딩하지 않는다.
			2. 연산자 오버로딩은 보편적인 상식을 기준으로 한다.
			3. 연관된 연산자를 모두 오버로딩 해야 한다.(<했으면, >도. +했으면 - * /도 오버로딩해야함.)


			* 산술 연산자 오버로딩 형식: 
				구현에 주의.
			* 대입 연산자 오버로딩 형식:
				데이터의 수정을 위해 반드시 this 객체를 참조로 반환해주어야함.
			* 비교연산자 오버로딩 형식:
				반환 타입이 bool, 객체의 수정도 이뤄지지 않음.
				그러므로 전역 연산자 오버로딩으로 구현.
			* 타입 변환 연산자 오버로딩 형식:
				operator 변환-타입() or explicit operator 변환-타입()
				ex.
					Complex::operator char *() const{
						공간 할당등 여러가지 변경...
					}
			* 함수 호출 연산자 () 오버로딩:
				c언어였다면 다른 함수를 호출하기 위해 함수포인터를 사용했겠지만,
				c++은 함수포인터 말고도 아래와 같은 방법으로 함수를 호출할 수 있다.
					1. 함수호출연산자 ()를 오버로딩하여 클래스의 인스턴스를 함수처럼 쓸 수 있다.
						ex. int operator()(int a){return sdlfkjsalfkasj; }
							->인수가 int 타입일 때 사용. 객체 옆에 괄호(함수호출연산자) + 알맞은 인수를 넣어서 사용한다.
					2. function 객체와 bind() 함수를 함수포인터처럼 다른 함수를 대입하여 호출하는 방법. ->나중에 알아보자.
					3. 람다를 함수호출연산자와 함께 사용하여 호출할 수 있다.

			* 배열 인덱스 연산자 [] 오버로딩:
				컨테이너 클래스 내부의 요소를 배열의 인덱스 처럼 사용할 수 있는 기능을 제공. 
				11-7이거 어케 했누(pg.432)
				
				접근지정자가 private이더라도 간접적으로 public지정자를 가진 함수/연산자를 통해 반환받은 멤버변수의
				참조를 사용하면 private의수정이 가능함.

			* new, delete 연산자 오버로딩


*/
//11-1 에러남.
//C++에서는 같은 클래스에서 생성된 객체끼리는 접근지정자에 관계없이 서로 모두 접근이 가능하다.
/*
#include <iostream>
#include <string>
using namespace std;
class Person{
	Person(const string n, int a) {
		name = n; 
		age = a;
	}
	bool Compare(Person& p) {   //일단 같은 클래스 내이므로, private이더라도 접근 가능.
		if (this->age < p.age)return false;
		return true;
	}
	const char *GetName() {
		return name.c_str();
	}
private:
	std::string name;
	int age;
};
int main()
{
	Person hong("홍길동", 23);
	Person lee("이순신", 53);

	if (hong.Compare(lee)) {   //lee의 나이 멤버에 접근할 수 있다. (같은 클래스 출신이므로, private이라도 서로 접근가능.)
		std::cout << hong.GetName() << "의 나이가"
			<< lee.GetName() << "보다 많다" << std::endl;
	}
	else {
		std::cout << lee.GetName() << "의 나이가 "
			<< hong.GetName() << "보다 많다" << std::endl;
	}


}
*/
//11-8

#include <cstdio>
#include <iostream>
#include <cstdlib>

void *operator new(size_t sz){  //new는 원래 stl라이브러리 제공함수가 아님. 
	std::cout << "new called. 크기: " << sz << std::endl;   //따라서 만약 new, delete의 기능을 클래스 내부로만 제한시키려면 클래스 내부로 함수를 넣어주면 된다.
	return std::malloc(sz); //인수로 들어온 sz는 컴파일러가 자료형의 크기를 자동으로 계산해서 uint값으로 넣어준 것.
}

void operator delete(void* ptr) noexcept {   //new를 오버로딩하면 delete도 같이 해줄것.
	std::cout << "delete called.\n";   //noexcept: 연산자. 한정자..
	std::free(ptr);   //컴파일 타임에 해당 표현식이 예외를 던지는지 체크해서 T/F를 반환함.
}

class mystring {
	char* mdata;
	size_t mdatalength;
};

int main()
{
	//아래의 new는 전역 new 연산자 오버로딩을 호출함
	int* p1 = new int;
	delete p1;

	int* p2 = new int[10];
	delete[] p2;

	mystring* p3 = new mystring();   //근데 이거 왜 16바이트임??  8바이트여야지..
	delete p3;

	std::cout << sizeof(char*) << std::endl;
}


/*
	ch 12. 반복자
		ch11의 Array클래스는 범위 기반 for문을 이용할 경우 에러가 발생한다.
		->클래스 내 반복자(내부 클래스)와 begin(), end()함수를 구현하지 않았기 때문에 발생한다.

		반복자: 일종의 포인터 기능을 제공하는 클래스.
			-장점: 1. 반복자 클래스는 제네릭 알고리즘이라 부르는 보조함수를 사용할 수 있도록 만들어 준다.  (ex. copy)
				   
				   2. 반복자 클래스는 배열, 컨테이너 클래스처럼 범위 기반 for문을 사용하여 객체 내부에 저장된 요소들을 일괄적으로 읽고 쓸 수 있는 기능을 제공한다.

				   3. 반복자 클래스는 그림과 같이 컨테이너 객체 내 쌓여져 있는 요소들을 배열처럼 순차적으로 읽고 쓸 수 있는 기능을 제공한다.

			-종류: 
			1. 입력 반복자: 컨테이너 객체 또는 문자열 객체처럼 객체 내 데이터를 읽을 수 있는 기능을 제공하는 반복자.

			2. 출력 반복자: 컨테이너 객체 또는 문자열 객체처럼 객체에 데이터를 넣을 수 있는 기능을 제공하는 반복자.

			3. 순방향 반복자: 입/출력 반복자의 기능 이외에 순방향으로 진행하면서 데이터를 읽고 쓸 수 있는 기능을 제공할 수 있는 반복자.

			4. 양방향 반복자: 양방향으로 진행하면서 데이터를 읽고 쓸 수 있는 기능을 제공할 수 있는 반복자.

			5. 임의 접근 반복자: 양방향 반복자의 기능 이외에 무작위로 객체 내 요소의 위치를 선택하여 읽고 쓰기 기능이 추가된 반복자.
				


			-특징: 
			1. 반복자는 포인터의 기능을 수행하는 내부 클래스이므로, 
				배열 인덱스 연산자와 포인터 멤버 선택 연산자 그리고 간접 참조 연산자 오버로딩이 필요하다!!
			
			2. 반복자의 간접 참조 연산자에 의해 반환하는 데이터는 객체가 관리하는 요소가 된다.
			
			3. 임의 접근 반복자는 요소를 가리키는 포인터의 위치를 임의적으로 바꿔주기 위해 포인터에 대한 연산작업을 수행해야 한다.
			-> 즉, 클래스가 포인터의 위치를 계산할 수 있도록 산술 연산자 오버로딩을 포함하여 대소비교연산자 오버로딩이 필요하다.

			4. 반복자는 일반적으로 한개 이상의 내부클래스로 제공됨. (vetor도 타입에 따라 4종류의 내부클래스를 제공한다)

			***임의 접근 반복자를 만들기 위해선 std::forward_iterator_tag구조체를 std::random_access_iterator_tag 구조체로 바꾸고,
			요구하는 연산자의 기능을 추가로 구현해 주어야 함

		--반복자를 클래스의 내부 클래스로 만들어 사용하면 범위기반 for, 연산자 오버로딩, 복사, 검색 등의 보조함수 사용시 편리하다. 
			그러나 반복자 어댑터는 내부 클래스로 반복자를 만들지 않아도 클래스가 
																	반복자를 사용한  보조함수를 쓸 수 있도록하는 기능을 제공한다.

			단, 모든 클래스에 반복자의 기능을 수행할 수 있는 건 아니다. 특정함수가 클래스 안에 존재할 때만 반복자의 기능을 제공한다.
			즉, 반복자 어댑터가 요구하는 함수/ 연산자 오버로딩이 없다면 컴파일 과정에서 에러가 발생함.
			반복자 어댑터는 모두 <iterator>헤더에 선언되어 제공된다.

			-move iterator 반복자: std::move()함수처럼 반복자를 rvalue 참조로 만드는 기능을 제공.
			즉, 임시값을 참조하여 직접 다루어 이동연산을 구현할 수 있다.
				다른 반복자 클래스 템플릿과 달리, 내부에 별도 데이터 타입을 선언하여 제공됨. `
*/
//12-1
//array 클래스에 반복자의 기능을 구현하기
/*
#include <cstring>
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <cassert>
#include <initializer_list>

template <typename Type>
class Array {
public:
	typedef int size_type;

	//내부 클래스 만들기.
	class iterator {
	public:
		typedef Type value_type;
		typedef Type& reference;
		typedef Type* pointer;

		typedef std::forward_iterator_tag iterator_category;  //반복자 카테고리 지정.
		typedef std::ptrdiff_t difference_type;

		iterator(pointer ptr = nullptr) :_ptr(ptr) { }   //내부클래스의 생성자와 디폴트 생성자를 만든다.

		iterator operator++() { ++_ptr; return *this; }  //단항 증가 전위, 후위 연산자 오버로딩 구현
		iterator operator++(int) { iterator tmp(*this); ++_ptr; return tmp; }

		//rvalue 간접참조연산자와 포인터 멤버 선택 연산자 오버로딩을 구현.
		reference operator*() { return *_ptr; }
		pointer operator->() { return _ptr; }

		//등가 비교 연산자 오버로딩은 시작이나 끝 반복자의 위치를 확인하는 작ㅂ업을 수행함.
		bool operator==(const iterator& rhs) { return _ptr == rhs._ptr; }
		bool operator!=(const iterator& rhs) { return _ptr != rhs._ptr; }

	private:
		Type* _ptr;
	};

	//Array 객체를 생성. 인수는 클래스가 관리하는 요소의 최대 갯수를 나타냄.
	Array(size_type size = 0) : _size(size) {
		if (0 == size) _data = nullptr;
		else _data = new Type[_size]();
	}

	Array(std::initializer_list<Type> init) :_size(init.size()) {
		_data = new Type[_size];
		std::copy(init.begin(), init.end(), _data);
	}

	template<typename _InputIterator>
	inline Array(_InputIterator _first, _InputIterator _last) {
		//반복자의 갯수를 산정한다.
		size_type size = _last - _first;
		_data = new Type[size];

		std::copy(_first, _last, _data);
		_size = size;
	}
	~Array() {
		if (_data) {
			delete[] _data;
			_size = 0;
		}
	}

	//객체가 관리하는 요소의 개수를 반환하는 함수
	inline size_type size() const { return _size; }

	//반복자와 무관하게 array객체 내 요소들을 읽고 쓸 수 있도록 배열 인덱스 연산자 오버로딩을 구현하면 편하다.
	Type& operator[](size_type index) {
		assert(index < _size);
		return _data[index];
	}

	const Type& operator[](size_type index) const {
		assert(index < _size);
		return _data[index];
	}

	//범위 기반 for문이 begin 과 end 함수를 요구하므로 구현.
	iterator begin() {
		//array 객체의 첫번째 요소를 사용하여 반복자 객체를 생성 후 반환.
		//객체 내부에 포인터가 생성되고 초기화된다
		return iterator(_data);
	}
	//array  객체의 마지막 비어있는 위치의 주소를 포인터로 만들어 반복자 객체를 생성하여 반환. 
	//범위 기반 for문들이 이 주소를 만나면 작업을 중단함.
	iterator end() {
		retur iterator(_data + size);
	}

private:
	Type* _data;
	size_type _size;
};

struct Account {
	//생성자
	Account() = default;
	Account(const char* id, const char* name, int bal) {
		strcpy(this->account, id);
		strcpy(this->name, name);
		this->balance = bal;
	}

	char account[20];
	char name[20];
	int balance;
};

//반복자 사용시

Array<double>::iterator i = array.begin();
*/
//12-2
//Array.hpp
/*
#ifndef Array_hpp
#define Array_hpp
#include <initializer_list>
#include <exception>
#include <iterator>

template <typename Type>
class Array {
public:
	typedef std::size_t size_type;
	class iterator {
	public:
		typedef Type value_type;
		typedef Type& reference;
		typedef Type* pointer;
		
		//반복자 카테고리를 지정함.
		typedef std::random_access_iterator_tag iterator_category;

		//difference_type은 메모리 주소를 가리키는 단위.
		//포인터 연산과 배열 indexing에 사용,
		typedef std::ptrdiff_t difference_type;

		iterator() : _ptr(nullptr) {}
		iterator(Type* rhs) : _ptr{}

		//대입 산술 연산자 오버로딩을 만듬
		inline iterator& operator=(Type* rhs) {
			_ptr = rhs;
			return *this;
		}
		inline iterator& operator=(const iterator& rhs) {
			_ptr = rhs._ptr;
			return*this;
		}
		inline iterator& operator+=(difference_type rhs) {
			_ptr += rhs;
			return *this;
		}
		inline iterator& operator-=(difference_type rhs) {
			_ptr -= rhs;
			return *this;
		}

		//rvalue 간접 참조 연산자오 포인터 멤버선택 연산자.
		//lvalue 간접 참조 연산자와 배열 인덱스 연산자 [] 오버로딩
		inline Type& operator*()const { return *_ptr;}
		inline Type* operator->() cosnt { return _ptr; }
		inline Type& operator[](difference_type rhs)const { return _ptr[rhs]; }

		//단항 증가 연산자와 단항 감소 연산자 오버로딩 구현
		inline itertor& operator++() { ++_ptr; return *this; }
		inline iterator& operator--() {--_ptr; return *this; }
		inline iterator operator++(int) { iterator tmp(*this); ++_ptr; return tmp; }
		inline iterator operator--(int) { iterator tmp(*this); --_ptr; return tmp; }

		//+, - 산술이항 연산자--> 임의의 위치를 계산하기 위해 사용,
		//자기 자신의 반복자와 메모리 주소의 증감 차를 나타내는 정수를 입력하면해당위치의 반복자르 반환.
		inline iterator operator+(difference_type rhs)const {
			return iterator(_ptr + rhs);
		}
		inline iterator operator-(differene_type rhs)const {
			return iterator(_ptr - rhs);
		}

		//iterator객체 + iterator객체는 메모리 주소를 반환해야하지만, 논리적으로 이상할 수 있어 거의 쓰지 않음. 다만 이항 연ㅅ나자 오버로딩의 규칙에 맞춰 제공.
		inline difference_type operator+(const iterator& rhs)const {
			return _ptr + rhs._ptr;
		}
		inline difference_type operator-(const iterator& rhs)const {
			return _ptr - rhs._ptr;
		}
		
		//교환법칙이 성립되도록 아래 ㅈ역함수 오버로딩을 선언한다.
		friend inline iterator operator+(difference_type lhs, cosnt iterator& rhs) {
			return iterator(lhs + rhs._ptr);
		}
		friend inline iterator operator-(difference_type lhs, const iterator& rhs) {
			return iterator(lhs - rhs._ptr);
		}

		//등가 비교연산자 (특정 인덱스의 위치인지 파악하기 위해 사용,)
		inline bool operator==(const iterator& rhs)const { return _ptr == rhs._ptr; }
		inline bool operator!=(const iterator& rhs)const { return _ptr != rhs._ptr; }

		//대소비교연산자는 정렬, 위치의 순서를 파악하기 위해 사용
		inline bool operator>(const iterator& rhs)const { return _ptr > rhs._ptr; }
		inline bool operator < (const iterator& rhs)const { return _ptr < rhs._ptr; }
		inline bool operator>=(const iterator& rhs)const { return _ptr >= rhs._ptr; }
		inline bool operator<=(const iterator& rhs)const { return _ptr <= rhs._ptr; }

	private:
		Type* _ptr;
	};

	inline Array(size_type size) : _size(size) {
		_data = new Type[_size];
	}
	inline Array(std::initializer_list<Type> init) : _size(init.size()) {
		_data = new Type[_size];
		std::copy(init.begin().init.end()._data);
	}
	inline ~Array() {
		if (_data) {
			delete[]_data;
			_size = 0;
		}
	}
	
	inline size_type size() const { return _size; }
	
	inline void push_back(Type t) {
		size_type size = _size + 1;
		Type* temp = new Type[size];
		std::copy(_data, _data + _size, temp);

		temp[_size] = t;
		delete[]_data;
		_data = temp;
		_size = size;
	}

	inline Type pop_back() {
		if (0 == _size)
			throw std::runtime_error("Array: 비어있음");
		--_size;
		return _data[_size];
	}

	inline Type& operator[](size_type index) {
		if (index >= _size || index < 0)
			throw std::runtime_error("index가 잘못됨");
		return _data[index];
	}

	inline const Type& operator[](size_type index)const {
		if (index >= _size || index < 0)
			throw std::runtime_error("인덱스가 잘못됨");
		return _data[index];
	}
	inline iterator begin() {
		return iterator(_data);
	}
	inline iterator end() {
		return iterator(_data + _size);
	}
	private:
		Type* data;
		size_type _size;
};
*/
//12-3
/*
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <cassert>
#include <initializer_list>
#include "Array.hpp"

int main() 
{
	Array<double> array = { 2.3, 3.2, 4.3 };
	for (Array<double>::__cpp_lib_make_reverse_iterator i = array.begin(); i != array().end; ++i) {
		std::cout << *i << " ";
	}
	std::cout << std::endl;

	Array<double>::iterator a = array.begin() + 2;   //포인터 덧셈.
	//+, - 산술이항 연산자--> 임의의 위치를 계산하기 위해 사용,
		//자기 자신의 반복자와 메모리 주소의 증감 차를 나타내는 정수를 입력하면해당위치의 반복자르 반환.
	
	inline iterator operator+(difference_type rhs)const {
		return iterator(_ptr + rhs);
	}
	
	std::cout << "array.begin() + 2 :" << *a << std::endl;

	return 0;
}
*/
//move_iterator 반복자
template <class Iterator>
class move_iterator {
	Iterator current;
public:
	typedef Iterator iterator_type;
	typedef typename iterator_traits<Iterator>::iterator_category iterator_category;
	typedef typename iterator_traits<Iterator>::value_type value_type;
	typedef typename iterator_traits<Iterator>::difference_type difference_type;
	typedef Iterator pointer;
	typedef value_type&& reference;

	move_iterator() {}  //디폴트 생성자.
	explicit move_iterator(Iterator it) : current(it) {}

	//복사 생성자.
	template <class Iter>
	move_iterator(const move_iterator<Iter>& it): current(it.current){}

	//복사대입연산자 오버로딩
	template<ckass Iter>
	move_Iterator& operator=(const move_iterator<Iter>& it) {
		current = it.current;
	}

	iterator_type base() const { return current; }
	pointer operator->()const { return current; }
	reference operator*()const { return std::move(*current); }

	move_iterator& operator++() {
		++current;
		return *this;
	}

	move_iterator& operator--() {
		--current;
		return *this;
	}
	 
	move_iterator& operator++(int) {
		move_iterator temp = *this;
		++current;
		return temp;
	}

	move_iterator& operator--(int) {
		move_iterator temp = *this;
		--current;
		return temp;
	}

	move_iterator operator+(difference_type n) const{
		return move_iterator(current + n);
	}

	move_iterator operator-(difference_type n)const {
		return move_iterator(current - n);
	}

	move_iterator operator+=(difference_type n) {
		current += n;
		return *this;
	}

	move_iterator operator-=(difference_type n) {
		current -= n;
		return *this;
	}

	//배열 인덱스 연산자 오버로딩
	auto operator[](difference_type n)const -> decltype(std::move(current[n])) {
		return std::move(current[n]);
	}
};
//12-5
#include <iostream>
#include <iterator>
#include <string>
#include <algorithm>
#include "Array.hpp"
int main()
{
	Array<std::string> foo (3);
	Array<std::string> bar{ "one", "two", "three" };

	typedef Array<std::string>::iterator Iter;
	std::copy(
		std::move_iterator<Iter>(bar.begin()),
		std::move_iterator<Iter>(bar.end()),
		foo.begin()
	);

	std::cout << "bar: ";
	for (std::string& x : bar)std::cout << ' ' << x;
	std::cout << std::endl;

	std::cout << "foo: ";
	for (std::string& x : foo)std::cout << ' ' << x;
	std::cout << std::endl;


}
