13장 주요 클래스
1. 문자열클래스
	basic_string 클래스 템플릿으로 선언된 클래스
	typedef basic_string<char> string;
	typedef basic_string<wchar_t> wstring;  -> wstring역시 basic_string클래스 템플릿의 인수. wchar_t타입을 쓰는 것 이외에 string클래스와 별 차이가 없다.

	-string의 기본  멤버함수
		 _.capacity()   : 생성된 문자열 객체의 크기를 반환한다
		_.max_size()   : 문자열로 처리할 수 있는 가장 큰 크기가 무엇인지 알려줌
		_.size() ==._length()   :현재 객체에 담겨져있는 문자열의 크기 (정확히는 문자갯수)를 반환한다.

	- string의 장점
	1. 연산자 기능을 제공
	2. 문자열의 비교가 가능. -> int compare(const string& str)const함수를 사용하여 상호 문자열을 비교가능   (같은 클래스의 객체끼리는 접근지정자를 무시하고 서로의 멤버에 접근 가능)
	3. 문자열의 교체   -> .find(const string) 으로 원하는 문자(열)를 문자열에서 뽑아서 위치를 받을 수 있다.
			그러나 이때 이 함수가 std::string::npos상수를 반환하면, 이것은 원하는 문자열을 찾을 수 없다는 뜻이다
			그리고 만약찾았다면, 찾은 위치를 사용해서
			.replace(.find(~~), 교체할 부분의 길이(원래 문자열의), 교체할 문자열)로 교체가능
	
	*pg490 basic_string 클래스참고(stl제공)
	template	<class _CharT, class _Traits, class _Alloc>
	class basic_string : private _String_base<_CahrT, _Alloc>{
	public:
		typedef _CharT value_type;
		"""
		"""
		typedef value_type* pointer;
		typedef const value_type* const_pointer;
		
		typedef value_type& reference;
		typedef const value_type& const_reference;
		
		typedef size_t size_type;
		typedef ptrdiff_t difference_type;
		"""
		"""
	}
	* stl에서 제공하는 클래스 템플릿은 위의 프로그램 처럼 기본적으로 내부에 타입멤버라는 이름으로데이터 타입들을 가지고 있다. -> 즉, 언제던지 개발자도 원할때마다 위의 데이터타입을 사용가능.
		->윈도우, 리눅스의 경우 대부분 디폴트 size_type은 size_t이다!
	*
	   size_type find(const basic_string& str, size_type pos=0)const   -> 객체내부에 str과 같은 문자열이 존재한다면 문자열이 존재하는 위치를 반환. 없다면 -1을 반환.
	   basic_string& replace(size_type pos, size_type count, const basic_string& str)  ->pos위치부터 시작해서 pos+count까지 문자열을 str인수로 교체해줌
	   
	   reference at(size_type pos) -> 문자열에서 pos인수가 가리키는 위치의 문자를 참조로 만들어 반환
	   (std::string은 typedef basic_string<char> string;으로 선언되어 있으므로, at함수는 char&를 반환하는것과 같다.)
	
	   basic_string& assign(size_type count, CharT ch)  -> 첫번째 인수 크기만큼의 회문을 만듬.
	   ex.(std:: string s;   s.assign(4, '=');   -> ====을 가짐.)

	   const char* c_str() const
	   const char* data() const  두함수 모두 string의 문자열을 const char* 타입의 문자열로 변환하여 리턴.

	   bool empty()const
	
	   string substr(size_t pos = 0, size_t len = npos)const;		->pos:복사하려는 문자열의 시작위치.
								pos+len의 문자열까지 복사.

	*
	   int stoi(const std::string& str, std::size_t*pos=0, int base=10)
	   long stol(const std::string&str, std::size_t* pos=0, int base=10)
	   long long stoll(const std::string& str, std::size_t*pos=0, int base=10)
	   float stof(const std::string&str, std::size_t*pos=0)
	   double stod(const std::string& str, std::size_t*pos=0)
	   long double stold(const std::string&str, std::size_t*pos =0)
	
	base-> 진법을 나타냄(10진법, 16진법등)
	pos ->숫자로 변환하지 못한 문자열의 위치


-함수포인터: 함수의 메모리주소를 가지고 있는 포인터

	FuncType function = &함수명; 과 같이 사용.

->C++은 함수포인터뿐만 아니라, 함수클래스와 바인더함수를 제공함.(함수 포인터와 기능은 동일, 안전.)

	바인더함수 선언문
	template <class Fn, class... Args>
	/*unspecified*/ bind(Fn&& fn, Args&& ...args): <functional>
	template <class Ret, class Fn, class... Args>
	/*unspecified*/ bind(Fn&& fn, Args&& ...args):<functional>  
	첫번째 인수는 호출하고자 하는 함수/함수포인터/클래스나 구조체의 멤버함수를 가리킴.
	두번째 인수는 가변인수. rvalue참조를 가리킴.
	  ->만약 첫 인수가 전역함수 => 두번째인수는 함수가 사용하는 인수
	 ->첫인수가 클래스의 멤버함수 => 멤버함수를 가지고 있는 클래스의 인스턴스를 가리키는 포인터., 세번째 인수부터는 첫인수의 함수가 사용하는 인수들

	그러나 바인더함수를 사용하면, 
		인수가 변경될때 마다 매번 bind()함수를 선언해야하므로 불편
	해결:	->1. std::reference_wrapper 클래스 템플릿 사용.
		->2. std::placeholders 네임스페이스 내의 extern변수를 사용한다.
	
	1.  std::refernce_wrapper 클래스 템플릿 => 람더의 캡처절과 같이 참조를 사용할 수 없는 환경에서 변수를 참조처럼 사용하는 기능 제공.
	ex.
	int i=1;
	std::reference_wrapper<int> y(i);   //int변수를 reference_wrapper로 포장.
	이제 i를 바꾸면 y도 자동으로 바뀜 -> bind계속 선언할 필요 없어짐. 단, 리터럴(상수)는 사용불가.
	이외에도 ref(), cref()함수를 이용해서 포장할 수 있다. 
	그러나 이 함수들은 일반변수, lvalue참조만 refernce_wrapper로 포장할 수 있고,
	rvalue참조를 사용하는 함수는 삭제되어서 사용할 수 없다. 
	
	2. namespace std::placeholders사용하기
	namespace placeholders{
		extern _1;
		extern _2;
		"""
	}
	위와같이 변수를 선언해서 bind함수와 같이 사용함. 
	이 네임스페이스 내의 변수들은 별도로 명시된 데이터 타입이 존재하지 않음 -> 함수에 선언된 데이터 타입에 따라 자동으로 결정됨.
	
	bind에 사용시
	auto f = std::bind(&클래스명::멤버함수, &클래스 객체, std::placeholders _1);처럼 사용하면 됨. 바뀌면 바뀔때마다 그에 맞게 쓰기.
	
	extern 지정자는 외부에서 선언되고 생성된 변수나 함수를 프로그램에서 사용하기 위해 선언하는 지정자.
		=> bind()함수와 std::placehoders네임스페이스내 변수가 c++이 아닌 c로 작성된 함수임을 알 수 있다.

	***. 함수 클래스 템플릿.
	bind함수를 수비게 쓸 ㅅ 있도록 만든 클래스 템플릿.
	template<class Ret, class... Args>
	class function<Ret(Args...)>: <functional>
	와 같이 선언되어 있음 -> 템플릿인수 형태 == <함수리턴(함수인수타입)> 으로 만들어주면 됨.
	
	즉, typedef std::function<auto> Fun;  //<auto>   ==   <void(const std::string&)>
	
	Fun f1 = std::bind(...); 과 같이 사용할 수 있다.
