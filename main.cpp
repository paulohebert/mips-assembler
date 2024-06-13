#include <iostream> //std::cout
#include <string> //std::string
#include <queue> //Fila
#include <bitset> //Container para armazenar os bits da instrução
#include "read.h"
#include "write.h"

int main(int argc, char **argv) {
    if(argc < 2) {
        std::cout << "Erro - O argumento do arquivo de entrada não foi informado\n";
        return 1;
    } else if (argc > 3) {
        std::cout << "Erro - Excesso de argumentos\n";
        return 2;
    }
    std::queue<std::bitset<32>> instructions; //Cria uma fila para armazenar as instruções
    std::string name{argc == 3 ? argv[2] : "memoria.mif"}; //Verifica se foi informado o argumento para o arquivo de saída e armazena o seu nome, caso contrário define um valor padrão
    read(argv[1], instructions);
    if(instructions.empty()) {
        std::cout << "Montagem Concluída sem Gerar Arquivo de Saída\n";
        return 0;
    }
    write(name, instructions);
    std::cout << "Montagem Concluída com Sucesso \n";
    return 0;
}
