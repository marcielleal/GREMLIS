#ifndef EVENT_HPP
#define EVENT_HPP
#include <ctime>        //time_t
/**
 * StoragePoolTest necessita de uma TAD que guarde informações sobre um ponteiro criado por ela e em quanto tempo ele deve ser liberado, esta
 * classe vem para auxiliar essa função.
 * @brief Guarda informações de um ponteiro a ser liberado e em quanto tempo ele deve ser liberado
 * @see StoragePoolTest
 */
class Event{
    private:
        void* ptr;//!< @brief Guarda um ponteiro genérico que aponta para um espaço de memória que deve ser liberado no tempo time
        std::time_t time;//!< @brief Guarda um time_t indicando em qual tempo ptr deve ser liberado
    public:
        /**
         * @brief Construtor de Event
         * @param _ptr é o valor que inicializará o atributo ptr
         * @param _time é o valor que inicializará o atributo time
         * @see ptr time
         */
        Event(void* _ptr,std::time_t _time);
        /**
         * @brief Construtor vazio de Event
         */
        Event();
        /**
         * @brief Construtor de Event
         * @return O valor do atributo ptr
         * @see ptr
         */
        void* getMemoryPtr();
        /**
         * @brief Captura o valor do atributo time
         * @return O valor do atributo time
         * @see time
         */
        std::time_t getTime();
        /**
         * Compara a instância atual de um tipo Event com outro Event.
         * Por exemplo, se houver uma comparação do tipo e1<e2, sendo e1 e e2 objetos do tipo Event:
         * O método operator< de e1 é chamado tendo como parâmetro e2.
         * @brief Sobrescrita do operator <
         * @param rhs é o objeto do tipo Event que será comparado com a instância atual desta classe(this)
         * @return true se o rhs é maior que a instância atual dessa classe, false se não for
         */
        bool operator<(Event rhs) const;
};
#endif //EVENT_HPP
