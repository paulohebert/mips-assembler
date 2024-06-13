#include <iostream> //std::cout
#include <fstream> //Manipula Arquivos, std::ifstream
#include <string> //std::string, std::getline
#include <cstdlib> //std::exit
#include <unordered_map> //Tabela Hash
#include <queue> //Fila
#include <bitset> //std::bitset
#include "instructions.h"
#include "label.h"
#include "encode.h"

void delete_comments(std::string& str) {
    size_t position = str.find('#'); //Busca a posição do caractere "#"
    /* Caso seja encontrado, apaga os caracteres até o final da linha */
    if(position != std::string::npos) {
        str.erase(position);
    }
}
    
void read(char *str, std::queue<std::bitset<32>>& binary_instructions) {
    std::ifstream file{str}; //Abre o arquivo para leitura
    /* Verifica se o arquivo pode ser aberto */
    if(file.good()) {
        std::unordered_map<std::string, long int> symbols_table; //Cria uma tabela hash para armazenar a tabela de símbolos (Labels)
        Instruction_Code const *code; //Ponteiro para o codigo da instrução
        std::string buffer, label;
        std::queue<Instruction> instructions; //Fila com os valores dos campos com base no formato da instrução
        long int address = 0x00000000; //Endereço da instrução
        /* Ler linha por linha o arquivo */
        while(std::getline(file, buffer)) {
            delete_comments(buffer); //Apaga os comentários da linha
            label = get_label(buffer); //Busca se tem algum label na linha e o retorna, caso contrário retorna uma string vazia 
            /* Caso seja encontrado o label o mesmo é adicionado à tabela de símbolos com seu respectivo endereço */
            if(!label.empty()) {
                symbols_table[label] = address;
            }
            code = get_instruction(buffer); //Busca se há alguma instrução na linha e retorna um ponteiro contendo o opcode/function e o formato da instrução, caso contrário retorna um ponteiro nulo
            if (code) {
                /* Ler os próximos lexemas da linha com base no formato da instrução */
                switch(static_cast<int>(code->format)) {
                    case R:
                        /* Adiciona uma instrução de formato R à fila */
                        instructions.push(syntax_R(buffer, code->func, address));
                        break;
                    case I:
                        /* Adiciona uma instrução de formato I à fila */
                        instructions.push(syntax_I(buffer, code->opcode, address, symbols_table));
                        break;
                    case J:
                        /* Adiciona uma instrução de formato J à fila */
                        instructions.push(syntax_J(buffer, code->opcode, address, symbols_table));
                        break;
                }
                address += 0x00000004; //Avança o endereço em 4 bytes para a próxima instrução
            }
        }
        converter(instructions, binary_instructions); //Converte a fila contendo os valores dos campos da instrução em um fila contendo as instrução em formato binário
    } else {
        std::cout << "Erro - Arquivo não encontrado\n";
        std::exit(EXIT_FAILURE);
    }
}
