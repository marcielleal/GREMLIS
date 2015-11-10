#include "SLPool.hpp"
#include <new>

template<typename T>
void clear(T* ptr,size_t num){
    bool *p=reinterpret_cast<bool*> (ptr);
    unsigned int i=sizeof(T)*num;
    for(unsigned int j=0;j<i;j++){
        *p=0;
        p++;
    }
}

SLPool::SLPool(size_t _bytes){
	this->mui_NumberOfBlocks=(_bytes/sizeof(Block)) + (_bytes%sizeof(Block)!=0) +1;

	//this->mp_Pool=(Block*)std::malloc(this->mui_NumberOfBlocks*sizeof(Block));
	this->mp_Pool=new Block[this->mui_NumberOfBlocks];
	this->mp_Pool->mui_Length=this->mui_NumberOfBlocks-1;
	this->mp_Pool->mp_Next=nullptr;

	this->mr_Sentinel=this->mp_Pool[this->mui_NumberOfBlocks-1];     //Ultimo bloco
	this->mr_Sentinel.mp_Next=mp_Pool;    //Aponta pro inicio das areas
}

SLPool::~SLPool(){
    std::cout<<"WHATS WRONG ?"<<std::endl;
    //std::free(mp_Pool);
    delete(mp_Pool);
}

void* SLPool::Allocate(size_t _bytes){
    size_t num=((_bytes+sizeof(Header))/sizeof(Block)) + ((_bytes+sizeof(Header))%sizeof(Block)!=0);
    Block *tmp=(&this->mr_Sentinel)->mp_Next;
    Block *bef_tmp=&this->mr_Sentinel;
    bool nFound=true;

    while((tmp!=nullptr)&&nFound){
        if(tmp->mui_Length>=num){//Area maior ou igual a pedida
            #ifdef DEBUG
            std::cout<<"-----------------------------"<<std::endl;
            std::cout<<"ALLOCATE ANYONE"<<std::endl;
            std::cout<<"tmp: "<<tmp<<std::endl;
            std::cout<<"tmp NEXT: "<<tmp->mp_Next<<std::endl;
            std::cout<<"bef_tmp: "<<bef_tmp<<std::endl;
            std::cout<<"bef_tmp NEXT: "<<bef_tmp->mp_Next<<std::endl;
            std::cout<<"PTSENTINEL: "<<&this->mr_Sentinel<<std::endl;
            std::cout<<"PTSENTINEL NEXT: "<<(&this->mr_Sentinel)->mp_Next<<std::endl;
            std::cout<<"NUM: "<<num<<std::endl;
            std::cout<<"-----------------------------"<<std::endl;
            #endif // DEBUG
            if(tmp->mui_Length==num){//Area igual
                std::cout<<"ALOCATION1!!"<<std::endl;
                bef_tmp->mp_Next=tmp->mp_Next;
            }else{
                std::cout<<"ALOCATION2!!"<<std::endl;
                bef_tmp->mp_Next=tmp+num;
                bef_tmp->mp_Next->mp_Next=tmp->mp_Next;
                bef_tmp->mp_Next->mui_Length=tmp->mui_Length-num;
                tmp->mui_Length=num;
            }nFound=false;
            if(mr_Sentinel.mp_Next==tmp)//WHY?
                mr_Sentinel.mp_Next=tmp->mp_Next;
            //tmp->mp_Next=nullptr;
            #ifdef DEBUG
            std::cout<<"-----------------------------"<<std::endl;
            std::cout<<"ALLOCATE AFTER"<<std::endl;
            std::cout<<"tmp: "<<tmp<<std::endl;
            std::cout<<"tmp NEXT: "<<tmp->mp_Next<<std::endl;
            std::cout<<"bef_tmp: "<<bef_tmp<<std::endl;
            if(bef_tmp!=nullptr)
                std::cout<<"bef_tmp NEXT: "<<bef_tmp->mp_Next<<std::endl;
            std::cout<<"PTSENTINEL: "<<&this->mr_Sentinel<<std::endl;
            std::cout<<"PTSENTINEL NEXT: "<<(&this->mr_Sentinel)->mp_Next<<std::endl;
            std::cout<<"NUM: "<<num<<std::endl;
            std::cout<<"-----------------------------"<<std::endl;
            #endif // DEBUG
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
            #ifdef DEBUG
            std::cout<<"-----------------------------"<<std::endl;
            std::cout<<"DELETE ANYONE"<<std::endl;
            std::cout<<"PTPOST: "<<ptPost<<std::endl;
            std::cout<<"PTPOST NEXT: "<<ptPost->mp_Next<<std::endl;
            std::cout<<"PTRESERVED: "<<ptReserved<<std::endl;
            std::cout<<"PTRESERVED NEXT: "<<ptReserved->mp_Next<<std::endl;
            std::cout<<"PTPREV: "<<ptPrev<<std::endl;
            std::cout<<"PTPREV NEXT: "<<ptPrev->mp_Next<<std::endl;
            std::cout<<"PTSENTINEL: "<<&this->mr_Sentinel<<std::endl;
            std::cout<<"PTSENTINEL NEXT: "<<(&this->mr_Sentinel)->mp_Next<<std::endl;
            std::cout<<"-----------------------------"<<std::endl;
            #endif // DEBUG
            if(((ptPrev+ptPrev->mui_Length)==ptReserved)&&((ptReserved+ptReserved->mui_Length)==ptPost)){
                std::cout<<"DELETE TWO AREAS"<<std::endl;
                ptPrev->mp_Next=ptPost->mp_Next;
                ptPrev->mui_Length+=ptReserved->mui_Length+ptPost->mui_Length;
                ptReserved->mui_Length=0;
                ptPost->mui_Length=0;
            }
            else if((ptPrev+ptPrev->mui_Length)==ptReserved){
                std::cout<<"DELETE LEFT"<<std::endl;
                ptPrev->mui_Length+=ptReserved->mui_Length;
                ptReserved->mui_Length=0;
                ptReserved=ptPrev;
            }
            else if((ptReserved+ptReserved->mui_Length)==ptPost){
                std::cout<<"DELETE RIGHT"<<std::endl;
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
            //if(ptReserved->mui_Length>1)
              //  clear(ptReserved+1,ptReserved->mui_Length-1);
            #ifdef DEBUG
            std::cout<<"-----------------------------"<<std::endl;
            std::cout<<"AFTER DELETION"<<std::endl;
            std::cout<<"PTPOST: "<<ptPost<<std::endl;
            std::cout<<"PTPOST NEXT: "<<ptPost->mp_Next<<std::endl;
            std::cout<<"PTRESERVED: "<<ptReserved<<std::endl;
            std::cout<<"PTRESERVED NEXT: "<<ptReserved->mp_Next<<std::endl;
            std::cout<<"PTPREV: "<<ptPrev<<std::endl;
            std::cout<<"PTPREV NEXT: "<<ptPrev->mp_Next<<std::endl;
            std::cout<<"PTSENTINEL: "<<&this->mr_Sentinel<<std::endl;
            std::cout<<"PTSENTINEL NEXT: "<<(&this->mr_Sentinel)->mp_Next<<std::endl;
            std::cout<<"-----------------------------"<<std::endl;
            #endif // DEBUG
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
        //clear(ptReserved+1,ptReserved->mui_Length-1);
    }
}
#ifdef DEBUG
#include "mempool_common.cpp"
int main(void){
    SLPool p(1024);
/*
    int *f=new (p) int[12];
    int *f1=new (p) int[12];
    int *f2=new (p) int[12];
    int *f3=new (p) int[12];
    int *f4=new (p) int[12];
    int *f5=new (p) int[12];
    int *f6=new (p) int[12];
    int *f7=new (p) int[12];
    int *f8=new (p) int[33];
        int i;
        for(i=0;i<12;i++){
            f[i]=i;
            f1[i]=i;
            f2[i]=i;
            f3[i]=i;
            f4[i]=i;
            f5[i]=i;
            f6[i]=i;
            f7[i]=i;
        }

        for(int i=0;i<12;i++)
            std::cout<<f[i]<<" ";
        std::cout<<std::endl;
        for(int i=0;i<12;i++)
            std::cout<<f1[i]<<" ";
        std::cout<<std::endl;
        for(int i=0;i<12;i++)
            std::cout<<f2[i]<<" ";
        std::cout<<std::endl;
        for(int i=0;i<12;i++)
            std::cout<<f3[i]<<" ";
        std::cout<<std::endl;
        for(int i=0;i<12;i++)
            std::cout<<f4[i]<<" ";
        std::cout<<std::endl;
        for(int i=0;i<12;i++)
            std::cout<<f5[i]<<" ";
        std::cout<<std::endl;
        for(int i=0;i<12;i++)
            std::cout<<f6[i]<<" ";
        std::cout<<std::endl;*/

        std::cout<<std::endl;


        int* f;
        int* f1;
        int* f2;
        int* f3;
        int* f4;
        int* f5;
        f=new (p) int[12];
        f1=new (p) int[12];
        f2=new (p) int[12];
        for(int i=0;i<12;i++){
            f[i]=i;
            f2[i]=i;
            f1[i]=i;
        }
        std::cout<<p<<'\n';
        delete f;
        std::cout<<p<<'\n';
        delete f1;
        f3=new (p) int[24];
        std::cout<<p<<'\n';
        std::cout<<"PRIMEIRAAAAAAAAAAAAAAAAAAAAA"<<std::endl;
        f4=new (p) int[2];
        std::cout<<p<<'\n';
        std::cout<<"SEGUNDAAAAAAAAAAAAAAAAAAAAA"<<std::endl;
        f5=new (p) int[2];
        delete f4;
        delete f2;
        delete f3;

        int* f7=new (p) int[47];
        std::cout<<p<<'\n';

    return 0;
}
#endif
