#include <iostream>
#include <stack>
#include <condition_variable>
#include <thread>

using namespace std;
std::mutex mu;
std::condition_variable cond;
stack<int> buffer;
const unsigned int maxBufferSize = 20;


void producer (int data){
    while(data) {
        std::unique_lock<std::mutex> locker(mu);
        cond.wait(locker, [](){
            return buffer.size() < maxBufferSize;
      });
        buffer.push(data);
        cout << "Produced: " <<data<<endl;
        data--;
        locker.unlock();
        cond.notify_one();
    }
}

void consumer (){
    while(true) {
        std::unique_lock<std::mutex> locker(mu);
        cond.wait(locker, [](){
            return buffer.size() >0;
      });
        int data = buffer.top();
        buffer.pop();
        cout << "Comsumed: " <<data<<endl;
        locker.unlock();
        cond.notify_one();
    }
}

int main() {
    std::thread t1(producer, 100);
    std::thread t2(consumer);
    t1.join();
    t2.join();
    return 0;
}
