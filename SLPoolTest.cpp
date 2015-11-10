#include <ctime>
#include <queue>
#include <iostream>
#include "SLPool.cpp"
#include "Event.cpp"
#include "Random.cpp"
#include <cstddef>      //nullptr

#include "mempool_common.cpp"


void StoragePoolTest(std::time_t _timeLimit,StoragePool *_pool=nullptr){
    Random ran;
    std::priority_queue<Event> pq;
    std::time_t t(0);
    Event ev;
    for(;t<_timeLimit;t++){
        std::cout<<t<<"INICIO "<<_timeLimit<<std::endl;
        while(!pq.empty()) { // Run while we have events pending or time to run .
            ev=pq.top();
            if(ev.getTime()>t) break ; // Still some time left ....
            pq.pop(); // Remove event from priority queue .
            delete ((bool*)(ev.getMemoryPtr())); // Calling free operator .
        }
        auto memSize = ran.getInt(100,2000);

        bool* add;
        bool flag=false;
        try{
            if(_pool==nullptr)
                add=new bool[memSize];
            else{
                add=new (*_pool) bool[memSize];
                flag=true;
            }
        }
        catch(std::bad_alloc){std::cout<<"FALTA MEMORIA"<<std::endl;}

        if(flag){
            auto elapsedTime = ran.getInt(1,100);
            std::time_t releaseTime=t+elapsedTime ; // Set time stamp some time from now .
            pq.push(Event(reinterpret_cast<void*>(add),releaseTime)); // Creating a new simulation event .
        }

        std::cout<<"FIM"<<std::endl;
    }std::cout<<"ENDAAIIIIIIIIIII"<<std::endl;
    while(!pq.empty()) { // Run while we have events pending or time to run .
        std::cout<<"ENTREI"<<std::endl;
        ev=pq.top();
        pq.pop();
        delete ((bool*)ev.getMemoryPtr());
    }
    std::cout<<"ENDAAIIIIIIIIIII"<<std::endl;
}
#include <ratio>
#include <chrono>
#include <unistd.h>
int main ()
{
  using namespace std::chrono;

  high_resolution_clock::time_point t1 = high_resolution_clock::now();

  StoragePool *s=new SLPool(1048576);
  StoragePoolTest(600000,s);

  high_resolution_clock::time_point t2 = high_resolution_clock::now();
    std::cout<<"MDASIO";
  duration<double> time_span = duration_cast<duration<double>>(t2 - t1);
  if((reinterpret_cast<Tag*>(s)-1U)->pool==nullptr)
    std::cout<<"OLOKO"<<std::endl;
    sleep(1);
  delete s;
  std::cout << "It took me " << time_span.count() << " seconds.";
  std::cout << std::endl;

  return 0;
}
