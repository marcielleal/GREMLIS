
#ifndef RANDOM_HPP
#define RANDOM_HPP
/**
 * @brief Random gera números aleatórios
 */
class Random{
    public:
		/**
		 * @brief Construtor de Random
		 * @param i é um inteiro usado 
		 */
        Random(int i=0);
        /**
         * @brief Gera um número aleatório no intervalo de [low,high]
         * @param low é o número mínimo do intervalo
         * @param high é o número máximo do intervalo
         * @return Um número aleatório
         */
        int getInt (int low, int high);
};
#endif // RANDOM_HPP
