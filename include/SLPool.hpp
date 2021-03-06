/**
 * @file SLPoolBF.hpp
 * @brief Assinatura da classe SLPoolBF
 *
 * @author Modificado por Marciel Manoel Leal
 */
#ifndef SLPOOL_HPP
#define SLPOOL_HPP
#include "StoragePool.hpp"
#include <iostream>     //ostream size_t
#include <ctime>        //time_t
#include <cstddef>      //nullptr
#include <cstdlib>

/**
* @brief SLPool é uma classe que implementa um gerenciador de memória com a política de First-fit
*/
class SLPool:public StoragePool{
	public:
		struct Header{
			unsigned int mui_Length ;   //!<Guarda a quantidade de blocos em uma área, alocada ou não, caso o bloco seja o primeiro desta area
			SLPool *p;                  //!<Guard who is the owner of area
			Header () : mui_Length(0u) { /* Empty */ };
		};
		struct Block:public Header{
			enum { BlockSize = 16 }; //Each block has 16 bytes .
			union{
				Block* mp_Next;
				char mc_RawArea [BlockSize-sizeof(Header)];
			};
			Block () : Header () , mp_Next(nullptr) { /* Empty */ };
		};
	protected:
		unsigned int mui_NumberOfBlocks;    //!<Numero de blocos alocados pelo gerenciador de memória
		Block* mp_Pool ; //!< Pointer for array
		Block mr_Sentinel; //!< Head of list of empty areas
	public:
		/**
		 * Aloca uma quantidade de memória sequencial de tamanho em bytes igual _bytes
         * @brief Construtor de SLPool
         * @param _bytes é a quantidade de bytes que o gerenciador de memória irá ter
		 */
		explicit SLPool (size_t _bytes=1024);
		/**
		 * Libera a memória alocada pelo construtor
         * @brief Destrutor de SLPool
		 */
		virtual ~SLPool();
		/**
		 * @brief Aloca blocos de memória a partir da memória alocada pelo gerenciador de memória
		 * @param _bytes é a quantidade de bytes que o cliente deseja alocar
		 * @return Um ponteiro do tipo void* que aponta para o início da memória a ser alocada pelo new
		 */
		void* Allocate(size_t _bytes);
        /**
         * @brief Libera blocos de memória a partir de um ponteiro que aponta para um espaço de memória anteriormente alocado por Allocate
         * @param _ptr é um ponteiro que aponta para o início da memória a ser liberada
         * @see Allocate
         */
		void Free(void* _ptr);
		/**
		 * Caso o bloco esteja vazio é impresso| |
		 * |*|
         * @brief Imprime uma representação textual do gerenciador de memória
         * @see Allocate
         */
		void MemoryMap(void);


};
#endif // SLPOOL_HPP
