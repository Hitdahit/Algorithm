람다 형식 :
[변수 캡쳐](받을 인자)->리턴타입 {함수}(넘길 인자)

[변수캡쳐] : 현재 함수에서 사용할 외부 변수들을 의미함.
main함수에 int num; 이라는 변수가 있어도 main의 람다가 그 변수를 사용하기 위해서는 변수 캡쳐로 써줘야 한다.

[]에 = 를 넣으면 해당 함수의 모든 변수를 전부다 사용한다는 의미
& 을 넣으면 모든 변수를 참조형으로 받아들인다는 의미이다
[=, &num]처럼 특정 변수만 참조형으로 사용하는 것도 가능
비워두면 아무것도 사용하지 않는다는 뜻

참고 : 전역변수는 캡쳐 할 필요 x



(받는 인자) : 함수에서 필요한 매개변수들을 적는 곳.
일반 함수에서도 int fun(int a, int b); 의 a, b와 같은 매개변수의 타입들을 지정.



->리턴 타입 : 화살표 뒤에는 리턴타입을 적어주면 됨.
단, void는 화살표와 함께 생략이 가능.


{함수} : 함수 몸체영역.


(넘길 인자) : 인제 함수가 모두 선언 되었으니, 호출할 인수들을 넣어줘야함.
이안에는 함수를 호출할 때 필요한 인자 값들을 적어두면 된다.


std::thread myThread = std::thread([](int nParam)
    {
        for (int i = 0; i < 10; i++) {
            std::cout << "thread called : " << nParam << std::endl;
        }
    }, 4);

thread를 람다로 구현함.

스레드
- 배경: CPu의 처리속도, 메모리작업, 디바이스 간의 입출력 속도 차로 인해, CPU가 100프로 사용되지 못하고 대기하는 시간이
->초기에는 fork() 함수를 이용해서 독립된 프로세스를 생성했으나, 결국 프로세스를 생성하는 비용이 드는데다,
프로세스 간에는 부모 자식이라도 메모리 영역을 공유하지 않기 때문에 결국 메시지 패싱 내지는 공유메모리를
사용해야 한다는 비효율성이 내재되어 있다.
->스레드는 프로세스를 구성하는 요소이므로, 스레드 간의 메모리를 공유할 수 있다는 장점이있다.

- STL 스레드 기능.
1. 스레드 관리 : 스레드 객체의 생성 및 실행, 종료.
2. 뮤텍스락 : 스레드 간 동기화 기능 제공.뮤텍스 클래스는 객체를 생성하여 락을 제공함.
3. 조건변수 : 이 값에 따라 스레드의 작업이 실행되거나 대기됨.
4. 비동기 작업(Async Task.) : 스레드 하나가 끝나면 그 작업결과가 자연스럽게 다른 하나의 스레드로 넘어가 실행되는 기능.

- thread는 이동생성자 디폴트 생성자는 제공하나, 복사 생성자는 제공되지 않는다.

std::thread thread1(Function&& f, f 인자값...); 과 같이 선언.
-> 내장된 전역함수.
    std::thread::id get_id() const : <thread> (스레드의 아이디를 받는다.)
    
    void yield()no except:<thread> (스레드가 자신의 실행될 권한을 다른 스레드에 양보하는 기능.)
    
    template <class Rep, class Period>
std::this_thred::sleep_for(const chrono::duration<Rep, Period>& rel_time);

**프로그램의 종료:
1. 메인스레드에서 실행되는 main() 함수의 실행이 완료되어 프로그램의 제어를 운영체제에게 반환할 때.
2. 메인스레드나 일반 스레드에서 exit()함수나 terminate()함수를 호출할 때.
3. 예외 및 에러 발생 할 때.
즉, 메인스레드는 가장 늦게 작업이 종료되어야 한다.
->join()함수는 함수와 연결된 스레드가 종료 될 때까지 join()함수를 호출한 스레드의 작업이 지연됨.
주로 메인스레드에서 일반스레드를 대상으로 사용.
->detach()함수는 join함수와 달리 메인스레드와 일반스레드를 분리시킴.
분리된 스레드는 독자 작업을 수행하지만 메인 스레드가 종료되면 바로 같이 종료됨.

** join detach를 호출하지 않는다면, 스레드 작업이 종료되더라도 os는 해당 스레드 리소스를 해제하지 않음.(비정상 종료)


- 스레드의 무분별한 공유리소스 사용을 제재. = > Serial
Serial : 경쟁조건이 발생해도 공유변수들을 순차적(serial)으로 참조하고 업데이트 시키는 함수.
뮤텍스 : 인위적으로 공유변수의 접근을 순차적으로 만들어버림.성능은 전반적으로 하락하나 여러가지 동기화 기능들 중에선 최선.

뮤텍스 : std::mutex mtx;  (즉, 변수타입임.)
->뮤텍스 변수는 접근을 오로지 하나에만 허용함.
-> void lock() : <mutex>  뮤텍스에 대한 잠금을 설정.이 함수를 부른 스레드가 unlock을 부를 때까지
lock을 부른 다른 스레드들은 대기하게 된다.
bool try_lock() : <mutex> 뮤텍스 잠금과 같으나, 이미 잠겨있는 락을 불렀을 때 대기 하는게 아니라 거짓을 리턴.
잠기지 않은 락을 불렀을 때 참을 리턴.

ex.
#include <iostream>
#include <mutex>
#include <atomic>

std::mutex mtx_lock;   //뮤텍스 변수의 선언.
int global = 0;
#define MAX_THREADS 2

void function(int func, int loops)
{
    /*인수로 제공된 loops만큼 지속적으로 1을 global 변수에 합한다*/
    for (int i = 0; i < loops; i++) {
        mtx_lock.lock();
        ++global;
        mtx_lock.unlock();
        if ((i % 10) == 0) std::this_thread::yield;
    }
    printf("%d.global = %d\n", func, global);
}

int main()
{
    std::thread t[MAX_THREADS];
    for (int i = 0; i < MAX_THREADS; ++i) {
        /*동일한 함수를 2개으 스레드로 만들어 실행 시킴*/
        t[i] = std::thread(function, i, 10000);
    }
    for (int i = 0; i < MAX_THREADS; ++i) {
        t[i].join();
    }
    printf("global = %d\n", global);
}
 
뮤텍스는 가능한 한 작은 범위의 임계여역을 설정하여 작업하는 것이 좋다!

뮤텍스 클래스의 종류:
    1. class mutex:<mutex>    - 일반적인 뮤텍스
    2. class recursive_mutex:<mutex>   
        - 위의 뮤텍스와 동일한 기능을 갖지만, 일반 뮤텍스는 같은 스레드에서 한번만 잠금을 설정할 수 있는 반면,
        이녀석은 여러번의 잠금을 설정할 수 있다.
    3. class timed_mutex:<mutex>
        - 뮤텍스에 대한 잠금을 설정할 때 시간적인 조건을 줄 수 있도록 아래와 같은 함수들을 제공함.
        나머지는 일반 뮤텍스와 동일.
        template <class Rep, class Period>
        bool try_lock_for(const chrono::duration<Rep, Period>&rel_time):<mutex>
            주어진 시간간격동안 뮤텍스의 잠금이 설정될 때까지 대기하고,
            만약 그 시간내에 설정되지 않으면 false를 반환, 설정되면 true 반환
            //while(!mtx.try_lock_for(std::chrono::milliseconds(200)))   0.2초동안 잠금설정.
        template <class Clock, class Duration>
        bool try_lock_until(const std::chrono::time_point<Clock, Duration>&abs_time):<mutex>
            인수로 주어진 미래의 시간동안 뮤텍스의 잠금이 설정될 때까지 대기함. 
            만약 설정되지 않은 상태에서 해당 시간이 경과하면 false.
    4. class recursive_timed_mutex:<mutex>
            recursive_mutex 클래스와 timed_mutex클래스의 두가지 기능을 모두 가지고 있는 클래스이다.
            """
           
async task.
future클래스와 async()함수를 이용하여, 비동기 프로그래밍을 할 수 있다.
future 클래스의 주요 특징 가운데 하나는 자체적으로 객체를 생성 시키는 일반 생성자를 제공하지 않는다는 점이다.

template<class T>class future
template<class T>class future<T&>
template<> class future<void>

async(Function&& f, Args&&...args):<future>
async(std::launch policy, Function&& f, Args&&...args):<future>
async함수의 인수는 rvalue참조를 이용한다!
