/**
 * @file StoragePool.hpp
 * @brief Assinatura da classe StoragePool
 *
 * @author Selan Rodrigues dos Santos
 * @author Modificado por Marciel Manoel Leal
 */
#ifndef SORAGEPOOL_HPP
#define SORAGEPOOL_HPP
#include <iostream>
/**
 * Classe abstrata que serve como base para implementação de um gerenciador de memória
 */
class StoragePool{
	public:
		/**
		 * Destrutor da classe
		 */
		virtual ~StoragePool(){};
		/**
		 * A função Allocate requisita uma quantidade de memória expressa em bytes
		 * passada como argumento.
		 */
		virtual void* Allocate(size_t _bytes)=0;
		/**
		 * A função Free recebe um ponteiro para uma região reservada e
		 * a libera para uso posterior pelo GM.
		 */
		virtual void Free (void * _ptr) = 0;
		/**
		 * Caso o bloco esteja vazio é impresso: | |
		 * Caso o bloco esteja ocupado é impresso: |*|
         * @brief Imprime uma representação textual do gerenciador de memória
         * @see Allocate
         */
		virtual void MemoryMap(void)=0;
};
#endif
