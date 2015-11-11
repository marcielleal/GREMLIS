
#include "SLPool.hpp"
#include <new>

SLPool::SLPool(size_t _bytes){
	this->mui_NumberOfBlocks=(_bytes/sizeof(Block)) + (_bytes%sizeof(Block)!=0) +1;

	this->mp_Pool=new Block[this->mui_NumberOfBlocks];
	this->mp_Pool->mui_Length=this->mui_NumberOfBlocks-1;
	this->mp_Pool->mp_Next=nullptr;

	this->mr_Sentinel=this->mp_Pool[this->mui_NumberOfBlocks-1];    //Ultimo bloco
	this->mr_Sentinel.mp_Next=mp_Pool;    							//Aponta pro inicio das areas
}

SLPool::~SLPool(){
    delete(mp_Pool);
}

void* SLPool::Allocate(size_t _bytes){
    size_t num=((_bytes+sizeof(Header))/sizeof(Block)) + ((_bytes+sizeof(Header))%sizeof(Block)!=0);
    Block *tmp=(&this->mr_Sentinel)->mp_Next;
    Block *bef_tmp=&this->mr_Sentinel;
    bool nFound=true;

    while((tmp!=nullptr)&&nFound){
        if(tmp->mui_Length>=num){//Area maior ou igual a pedida
            if(tmp->mui_Length==num){//Area igual
                bef_tmp->mp_Next=tmp->mp_Next;
            }else{
                bef_tmp->mp_Next=tmp+num;
                bef_tmp->mp_Next->mp_Next=tmp->mp_Next;
                bef_tmp->mp_Next->mui_Length=tmp->mui_Length-num;
                tmp->mui_Length=num;
            }nFound=false;
            if(mr_Sentinel.mp_Next==tmp)//WHY?
                mr_Sentinel.mp_Next=tmp->mp_Next;
            break;
        }
        else bef_tmp=bef_tmp->mp_Next;
        tmp=tmp->mp_Next;
    }if(nFound) throw(std::bad_alloc());

    return reinterpret_cast<void*>(reinterpret_cast<int*>(tmp)+1U);
}

void SLPool::Free(void* _ptr){
    Block* ptReserved=reinterpret_cast <Block*>(reinterpret_cast <int*>(_ptr)-1U);
    Block* ptPost=this->mr_Sentinel.mp_Next;
    Block* ptPrev=&this->mr_Sentinel;
    int i=0;
    bool nFound=true;
    while(ptPost!=nullptr){
        if(ptPost>ptReserved){
            if(((ptPrev+ptPrev->mui_Length)==ptReserved)&&((ptReserved+ptReserved->mui_Length)==ptPost)){
                ptPrev->mp_Next=ptPost->mp_Next;
                ptPrev->mui_Length+=ptReserved->mui_Length+ptPost->mui_Length;
                ptReserved->mui_Length=0;
                ptPost->mui_Length=0;
            }
            else if((ptPrev+ptPrev->mui_Length)==ptReserved){
                ptPrev->mui_Length+=ptReserved->mui_Length;
                ptReserved->mui_Length=0;
                ptReserved=ptPrev;
            }
            else if((ptReserved+ptReserved->mui_Length)==ptPost){
                ptReserved->mp_Next=ptPost->mp_Next;
                ptPrev->mp_Next=ptReserved;
                ptReserved->mui_Length+=ptPost->mui_Length;
                ptPost->mui_Length=0;
            }
            else{
                ptReserved->mp_Next=ptPost;
                ptPrev->mp_Next=ptReserved;
            }
            ptReserved->p=nullptr;
            break;
        }
        else
            ptPrev=ptPrev->mp_Next;
        ptPost=ptPost->mp_Next;
    }
    if(ptPost==nullptr){
        if((ptPrev+ptPrev->mui_Length)==ptReserved){
            ptPrev->mui_Length+=ptReserved->mui_Length;
            ptReserved->mui_Length=0;
        }
        else{
            ptReserved->mp_Next=ptPost;
            ptPrev->mp_Next=ptReserved;
        }
        ptReserved->p=nullptr;
    }
}
void SLPool::MemoryMap(void){
    Block* tmp=(&this->mr_Sentinel)->mp_Next;
    for(unsigned int i=0,j=0;i<this->mui_NumberOfBlocks-1;j=0){
        if((mp_Pool+i)==tmp){
            j=(mp_Pool+i)->mui_Length;
            for(;j>0&&i<this->mui_NumberOfBlocks;j--,i++)
                std::cout<<" B"<<i<<"-"<<j<<" "<<"| |";
            tmp=tmp->mp_Next;
        }else{
            j=(mp_Pool+i)->mui_Length;
            for(;j>0&&i<this->mui_NumberOfBlocks;j--,i++)
                std::cout<<" B"<<i<<"-"<<j<<" "<<"|*|";
        }
    }std::cout<<std::endl<<std::endl;
}
