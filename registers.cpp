#include <iostream> //std::cout
#include <cstdlib> //std::exit
#include <string> //std::string
#include <algorithm> //std::find, std::find_if
#include "registers.h"

/* Retorna verdadeiro caso chegue ao final do nome do registrador */
bool end_reg(char const& ch) {
    return (ch == ' ' || ch == ',' || ch == ')');
}

/* Busca na string o registrador e retorna seu valor númerico */
Registers get_register(std::string& str) {
    auto begin = std::find(str.begin(), str.end(), '$'); //Busca o endereço para o começo da string contendo o nome do registrador
    if (begin != str.end()) {
        auto end = std::find_if(begin, str.end(), end_reg); //Busca o final do lexema do registrador
        std::string str_reg{begin + 1, end}; //Cria a string com o nome do registrador sem o caractere "$"
        auto reg = registers_table.find(str_reg); //Busca se existe na tabela o nome do registrador
        if (reg == registers_table.end()) {
            std::cout << "Erro - O registrador \"$" << str_reg << "\" não existe\n";
            std::exit(EXIT_FAILURE);
        }
        str.erase(begin, end); //Limpa o lexema do registrador na string
        return reg->second;
    }
    std::cout << "Erro - Registrador não encontrado\n";
    std::exit(EXIT_FAILURE);
}
