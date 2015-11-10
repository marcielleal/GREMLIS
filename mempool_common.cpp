/*Selan*/
#include <iostream>
#include "StoragePool.hpp"
#include <cstdlib>
#include <unistd.h>
struct Tag {StoragePool* pool;};

void* operator new (size_t bytes, StoragePool &p) {
    std::cout<<"NEW SEM SO COM "<<bytes<<std::endl;
	Tag* const tag = reinterpret_cast<Tag*>(p.Allocate(bytes));
	tag->pool = &p;
	return (reinterpret_cast<void*>(tag + 1U)); 						//skip sizeof tag to get the raw data - block .
}

void* operator new[](size_t bytes, StoragePool &p){
    std::cout<<"NEW[] SEM SO COM "<<bytes<<std::endl;
	Tag* const tag = reinterpret_cast<Tag*>(p.Allocate(bytes));
	tag->pool = &p;
	return (reinterpret_cast<void*>(tag + 1U)); 						//skip sizeof tag to get the raw data - block .
}
void* operator new (size_t bytes){ // Regular new
    std::cout<<"NEW COM SO COM "<<bytes<<std::endl;
	Tag* const tag = reinterpret_cast<Tag*>(std::malloc(bytes+sizeof(Tag)));
	tag->pool = nullptr;
	return (reinterpret_cast<void*>(tag+1U));
}
void* operator new [](size_t bytes){ // Regular new
    std::cout<<"NEW[] COM SO COM "<<bytes<<std::endl;
	Tag* const tag = reinterpret_cast<Tag*>(std::malloc(bytes+sizeof(Tag)));
	tag->pool = nullptr;
	return (reinterpret_cast<void*>(tag+1U));
}
#include <unistd.h>
void operator delete (void *arg) noexcept{
	// We need to subtract 1 U ( in fact , pointer arithmetics ) because arg
	// points to the raw data ( second block of information ).
	// The pool id ( tag ) is located ‘ sizeof ( Tag ) ’ bytes before .
	Tag * const tag =reinterpret_cast <Tag*>(arg)-1U;

	if (nullptr!=tag->pool){ 	// Memory block belongs to a particular GM .
		std::cout<<"FREE SEM SO"<<std::endl;
		tag->pool->Free(reinterpret_cast <void*>(tag));
    }
    else{
		std::cout<<"FREE COM SO"<<std::endl;
		std::free(reinterpret_cast <void*>(tag)); 		// Memory block belongs to the operational system .
    }
}
