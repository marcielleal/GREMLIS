/**
 * @file mempool_common.cpp
 * @brief Implementação dos operators new e delete
 *
 * @author Selan Rodrigues dos Santos
 * @author Modificado por Marciel Manoel Leal
 *
 */
#include <iostream>
#include "StoragePool.hpp"

#ifndef MEMPOOL_COMMON
#define MEMPOOL_COMMON
struct Tag {StoragePool* pool;};

void* operator new (size_t bytes, StoragePool &p) {
	Tag* const tag = reinterpret_cast<Tag*>(p.Allocate(bytes));
	tag->pool = &p;
	return (reinterpret_cast<void*>(tag + 1U));
}

void* operator new[](size_t bytes, StoragePool &p){
	Tag* const tag = reinterpret_cast<Tag*>(p.Allocate(bytes));
	tag->pool = &p;
	return (reinterpret_cast<void*>(tag + 1U)); 		
}
void* operator new (size_t bytes){ // Regular new
	Tag* const tag = reinterpret_cast<Tag*>(std::malloc(bytes+sizeof(Tag)));
	tag->pool = nullptr;
	return (reinterpret_cast<void*>(tag+1U));
}
void* operator new [](size_t bytes){ // Regular new
	Tag* const tag = reinterpret_cast<Tag*>(std::malloc(bytes+sizeof(Tag)));
	tag->pool = nullptr;
	return (reinterpret_cast<void*>(tag+1U));
}

void operator delete (void *arg) noexcept{
	Tag * const tag =reinterpret_cast <Tag*>(arg)-1U;
	if (nullptr!=tag->pool){ 	
		tag->pool->Free(reinterpret_cast <void*>(tag));
    }
    else{
		std::free(reinterpret_cast <void*>(tag)); 		
    }
}
#endif
