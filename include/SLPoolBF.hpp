/**
 * @file SLPoolBF.hpp
 * @brief Assinatura da classe SLPoolBF
 *
 * @author Modificado por Marciel Manoel Leal
 */
#ifndef SLPOOLBF_HPP_INCLUDED
#define SLPOOLBF_HPP_INCLUDED
#include "SLPool.hpp"
/**
* @brief SLPoolBF é uma classe que implementa um gerenciador de memória com a política de Best-fit
*/
class SLPoolBF:public SLPool{
    public:
        /**
         * Aloca uma quantidade de memória sequencial de tamanho em bytes igual _bytes
         * @brief Construtor de SLPoolBF
         * @param _bytes é a quantidade de bytes que o gerenciador de memória irá ter
         */
        explicit SLPoolBF (size_t _bytes):SLPool(_bytes){/*Empty*/};
        /**
         * Libera a memória alocada pelo construtor
         * @brief Destrutor de SLPool
         */
        virtual ~SLPoolBF(){/*Empty*/};
        /**
         * @brief Aloca blocos de memória a partir da memória alocada pelo gerenciador de memória
         * @param _bytes é a quantidade de bytes que o cliente deseja alocar
         * @return Um ponteiro do tipo void* que aponta para o início da memória a ser alocada pelo new
         */
        void* Allocate(size_t _bytes);
};


#endif // SLPOOLBF_HPP_INCLUDED
