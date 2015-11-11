#include "SLPoolBF.hpp"
#include "SLPool.cpp"
void* SLPoolBF::Allocate(size_t _bytes){
    size_t num=((_bytes+sizeof(Header))/sizeof(Block)) + ((_bytes+sizeof(Header))%sizeof(Block)!=0);
    Block *tmp=(&this->mr_Sentinel)->mp_Next;
    Block *bef_tmp=&this->mr_Sentinel;
    Block *best_tmp=&this->mr_Sentinel;
    bool nFound=true;

    while((tmp!=nullptr)){
        if(tmp->mui_Length==num){//Area igual
            bef_tmp->mp_Next=tmp->mp_Next;
            nFound=false;
        }else if(tmp->mui_Length>num){//Area maior ou igual a pedida
            if(best_tmp->mui_Length>tmp->mui_Length)
                best_tmp=tmp;
            nFound=false;
        }else bef_tmp=bef_tmp->mp_Next;
        tmp=tmp->mp_Next;
    }
    tmp=best_tmp;
    if(nFound) throw(std::bad_alloc());
    else{
        bef_tmp->mp_Next=tmp+num;
        bef_tmp->mp_Next->mp_Next=tmp->mp_Next;
        bef_tmp->mp_Next->mui_Length=tmp->mui_Length-num;
        tmp->mui_Length=num;
        if(this->mr_Sentinel.mp_Next==tmp)//WHY?
            this->mr_Sentinel.mp_Next=tmp->mp_Next;
    }
    return reinterpret_cast<void*>(reinterpret_cast<int*>(tmp)+1U);
}
int main(void){
    StoragePool *s=new SLPoolBF(1024);
    int *p=new (s) int;
}
