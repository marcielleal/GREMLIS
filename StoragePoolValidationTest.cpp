#include <cstddef>      //nullptr
#include <iostream>
#include "./include/StoragePool.hpp"
#include "./include/SLPool.hpp"
#include "./src/SLPoolBF.cpp"

#include "./src/mempool_common.cpp"

void StoragePoolValidationTest(StoragePool &p){   
    int* f;
    int* f1;
    int* f2;
    int* f3;
    int* f4;
    int* f5;
    f=new (p) int[12];
    std::cout<<"#####Alocação 12 inteiros######"<<std::endl;

    p.MemoryMap();
    f1=new (p) int[12];
    std::cout<<"#####Alocação 12 inteiros######"<<std::endl;
    p.MemoryMap();
    f2=new (p) int[12];
    std::cout<<"#####Alocação 12 inteiros######"<<std::endl;
    p.MemoryMap();
    for(int i=0;i<12;i++){
        f[i]=i;
        f2[i]=i;
        f1[i]=i;
    }
    delete f;
    std::cout<<"#####Liberação da primeira alocação(12 inteiros)######"<<std::endl;
    p.MemoryMap();
    delete f1;
    std::cout<<"#####Liberação da segunda alocação(12 inteiros)######"<<std::endl;
    p.MemoryMap();
    f3=new (p) int[24];
    std::cout<<"#####Alocação 24 inteiros######"<<std::endl;
    p.MemoryMap();
    f4=new (p) int[2];
    std::cout<<"#####Alocação 2 inteiros######"<<std::endl;
    p.MemoryMap();
    f5=new (p) int[2];
    std::cout<<"#####Alocação 2 inteiros######"<<std::endl;
    p.MemoryMap();
    delete f4;
    std::cout<<"#####Liberação da quinta alocação(2 inteiros)######"<<std::endl;
    p.MemoryMap();
    delete f2;
    std::cout<<"#####Liberação da terceira alocação(12 inteiros)######"<<std::endl;
    p.MemoryMap();
    delete f3;
    std::cout<<"#####Liberação da quarta alocação(24 inteiros)######"<<std::endl;
    p.MemoryMap();
    int* f7=new (p) int[47];
    std::cout<<"#####Alocação 47 inteiros######"<<std::endl;
    p.MemoryMap();
    delete f7;
    std::cout<<"#####Liberação da quarta alocação(47 inteiros). Área livre à direita######"<<std::endl;
    p.MemoryMap();
    delete f5;
    std::cout<<"#####Liberação da quarta alocação(5 inteiros). Área livre à esquerda e à direita######"<<std::endl;
    p.MemoryMap();
}
