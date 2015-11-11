# GREMLIS
Gerenciador de memória(GM) com lista encadeada

###Descrição
Projeto solicitado pelo Professor Selan Rodrigues, na disciplina de Estruturas de Dados Básicas I.
Implementa algumas classes que permitem o gerenciamento de memória sem precisar recorrer diretamente ao sistema operacional.

Para criar um GM p, faz-se:

* StoragePool p(numero_de_bytes);

Para solicitar memória de um GM p, faz-se:

* tipo_de_dado ponteiro= new (p) tipo_de_dado;

Para incluir em qualquer projeto, basta incluir as pastas include e src no projeto

###Operator new
Caso seja uma requisição a partir de um GM, se não houver espaço suficiente dentro do GM para a memória requisitada, é levantado uma exceção do tipo bad_alloc e encerra o programa.
Por isso, essa exceção deve ser tratado por programas cliente.
	
###Autor:
* Marciel Manoel Leal - marcielmanoel15@gmail.com

###Compilação dos testes

#####Teste de tempo
* g++ -Wall -std=c++11 -o StoragePoolTest StoragePoolTest.cpp

#####Teste de validação do GM
* g++ -Wall -std=c++11 -o StoragePoolValidationTest StoragePoolValidationTest.cpp

###Disponível em: 
https://github.com/marcielleal/GREMLINS
