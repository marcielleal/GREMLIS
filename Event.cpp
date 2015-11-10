#include "Event.hpp"
#include <iostream>

Event::Event(void* _ptr,std::time_t _time){
    this->ptr=_ptr;
    this->time=_time;
}
Event::Event(){

}
void* Event::getMemoryPtr(){
    return this->ptr;
}
std::time_t Event::getTime(){
    return this->time;
}
bool Event::operator<(Event rhs)const{
    return (this->time<rhs.getTime());
}
