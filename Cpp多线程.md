# Cpp多线程
```cpp
#include <iostream>
#include <thread>
#include <mutex>
using namespace std;

int balance = 0;
mutex balancemutex;

void put_balance(int n) {
	for(int i=0; i<n; ++i) {
		balancemutex.lock();
		balance += 1;
		balancemutex.unlock();
	}
}

void get_balance(int n) {
	for(int i=0; i<n; ++i) {
		balancemutex.lock();
		balance -= 1;
		balancemutex.unlock();
	}
}


int main() {
	thread t1(put_balance, 100000);
	thread t2(get_balance, 100000);
	
	t1.join();
	t2.join();
	cout << balance << endl;	
}
```

## 条件变量
```cpp
#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <condition_variable>
 
std::mutex m;
std::condition_variable cv;
std::string data;
bool ready = false;
bool processed = false;
 
void worker_thread()
{
    // 等待直至 main() 发送数据
    std::unique_lock<std::mutex> lk(m);
    cv.wait(lk, []{return ready;});
 
    // 等待后，我们占有锁。
    std::cout << "Worker thread is processing data\n";
    data += " after processing";
 
    // 发送数据回 main()
    processed = true;
    std::cout << "Worker thread signals data processing completed\n";
 
    // 通知前完成手动解锁，以避免等待线程才被唤醒就阻塞（细节见 notify_one ）
    lk.unlock();
    cv.notify_one();
}
 
int main()
{
    std::thread worker(worker_thread);
 
    data = "Example data";
    // 发送数据到 worker 线程
    {
        std::lock_guard<std::mutex> lk(m);
        ready = true;
        std::cout << "main() signals data ready for processing\n";
    }
    cv.notify_one();
 
    // 等候 worker
    {
        std::unique_lock<std::mutex> lk(m);
        cv.wait(lk, []{return processed;});
    }
    std::cout << "Back in main(), data = " << data << '\n';
 
    worker.join();
}
```

**条件变量**
`condition_variable`类是同步原语，用于阻塞一个线程，或者同时阻塞多个线程，
直到另一个线程修改共享变量，并通知`condition_variable`

有意修改变量的线程必须：
* 获得`std::mutex` （常通过`lock_guard`)
* 在保有锁时进行修改
* 在`condition_variable`上执行`notify_one`或`notify_all`

有意在`condition_variable`上等待的线程必须
* 在与用于保护共享变量者相同的互斥上获得`unique_lock<mutex>`
* 执行下列之一：
 1. 检查条件，是否已更新或提醒它的情况

 2. 执行`wait`, `wait_for`, 或者`wait_until`

 3. `condition_variable`被通知时，时限消失或虚假唤醒发生，线程被唤醒，且自动重获得互斥。之后线程应该检查条件，若唤醒时虚假的，则继续等待。

    

    ## notify_one

```cpp
#include <iostream>
#include <condition_variable>
#include <thread>
#include <chrono>

std::condition_variable cv;
std::mutex cv_m;
int i = 0;
bool done = false;

void waits() {
    std::unique_lock<std::mutex> lk(cv_m);
    std::cout << "Waiting...\n";
    cv.wait(lk, []{ return i == 1;});
    std::cout << "...finished waiting. i == 1\n";
    done = true;
}

void signals() {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "Notifying falsely...\n";
    cv.notify_one();
    
    std::unique_lock<std::mutex> lk(cv_m);
    i = 1;
    while(!done) {
        std::cout << "Notifying true change...\n";
        lk.unlock();
        cv.notify_one();
        std::this_thread::sleep_for(std::chrono::seconds(1));
        lk.lock();
    }
}
int main() {
    std::thread t1(waits);
    std::thread t2(signals);
    
    t1.join();
    t2.join();
}
```

