#include <iostream> //std::cout
#include <string> //std::stoi
#include <queue> //Fila
#include <algorithm> //std::find, std::find_if, std::transform
#include <bitset> //std::bitset
#include <cstdlib> //std::exit
#include <cctype> //std::isalpha, std::tolower, std::isdigit
#include "instructions.h"
#include "registers.h"
#include "label.h"

/* Busca o começo de algum número iniciando com um digito ou com '-' para números negativos */
bool beg_imm(char const& ch) {
    return (std::isdigit(ch) || ch == '-');
}

/* Busca o fim do imediato */
bool end_imm(char const& ch) {
    return (ch == ' ' /*caso seja uma instrução normal do formato I*/ || ch == '(' /*caso a instrução seja lw ou sw*/);
}

/* Busca o imediato da instrução */
int get_immediate(std::string& str) {
    auto begin = std::find_if(str.begin(), str.end(), beg_imm); //Busca um número na string
    if(begin != str.end()) {
        auto end = std::find_if(begin, str.end(), end_imm); //Busca o final do número na string
        std::string imm{begin, end};
        str.erase(begin, end);
        /* Tenta converter uma string em um inteiro */
        try {
            /* Caso o prefixo do número for "0x" será interpretado como hexadecimal.
               Caso o prefixo seja "0"(Zero) será interpretado como octal.
               Caso contrário será decimal. */
            return std::stoi(imm, nullptr, 0); //Converte uma string contendo um número (Decimal, Hexadecimal, Octal) em um inteiro
        } catch(...) {
            std::cout << "Erro - Imediato \"" << imm << "\" inválido\n";
            std::exit(EXIT_FAILURE);
        }
    }
    std::cout << "Erro - O imediato nāo encontrado\n";
    std::exit(EXIT_FAILURE);
}

/* Ler os lexemas das instruções do formato R */
Instruction syntax_R(std::string& str, int func, long int address) {
    Instruction instruction;
    instruction.format = R;
    instruction.r.func = func;
    instruction.address = address;
    /* Caso seja a instruçāo "jr", a leitura da sintaxe é feita diferente das demais */
    if(func == 8){
        /* func $rs */
        instruction.r.rs = get_register(str);
        instruction.r.rd = 0;
        instruction.r.rt = 0;
    } else {
        /* func $rd, $rs, $rt */
        instruction.r.rd = get_register(str);
        instruction.r.rs = get_register(str);
        instruction.r.rt = get_register(str);
    }
    return instruction;
}

/* Ler os lexemas das instruções do formato I */
Instruction syntax_I(std::string& str, int opcode, long int address, std::unordered_map<std::string, long int>& symbols_table) {
    Instruction instruction; //Cria a instrução
    instruction.format = I;
    instruction.i.op = opcode;
    instruction.address = address;
    switch(opcode) {
        case 4: // Caso "beq"
        case 5: // Caso "bne"
            /* opcode $rs, $rt, label */
            instruction.i.rs = get_register(str);
            instruction.i.rt = get_register(str);
            instruction.i.label = address_label(str, symbols_table);
            break;
        case 35: // Caso "lw"
        case 43: // Caso "sw"
            /* opcode $rt, imm($rs) */
            instruction.i.rt = get_register(str);
            instruction.i.imm = get_immediate(str);
            instruction.i.rs = get_register(str);
            break;
        default:
            /* opcode $rt, $rs, imm */
            instruction.i.rt = get_register(str);
            instruction.i.rs = get_register(str);
            instruction.i.imm = get_immediate(str);
            break;
    }
    return instruction;
}

/* Ler os lexemas das instruções do formato J */
Instruction syntax_J(std::string& str, int opcode, long int address, std::unordered_map<std::string, long int>& symbols_table) {
    Instruction instruction; //Cria a instrução
    instruction.format = J;
    instruction.j.op = opcode;
    instruction.address = address;
    instruction.j.label = address_label(str, symbols_table); //Armazena o ponteiro para o endereço do label na tabela de símbolos para depois ser usada para consultar quando for fazer a conversão da instrução para binário
    return instruction;
}

/* Busca o nome da instrução e retorna um ponteiro contendo o opcode/function e o formato da instrução,
caso contrário retorna um ponteiro nulo avisando que não há nenhuma instrução na linha */
Instruction_Code const* get_instruction(std::string& str) {
    auto begin = std::find_if(str.begin(), str.end(), isalpha); //Busca um ponteiro para o primeiro caractere alfabetico
    if(begin != str.end()) {
        auto end = std::find(begin, str.end(), ' '); //Ponteiro para o final do nome da instrução
        std::string name{begin, end};
        str.erase(begin, end); //Apaga da linha o nome da instrução
        std::transform(name.begin(), name.end(), name.begin(), tolower); //Transforma a sequência de caracteres da string em letras minúsculas para tanto o lexema "ADD" e "add" sejam válidos
        auto instruction_code = instruction_set.find(name); //Busca as informações da instrução na tabela hash contendo as instruções
        if(instruction_code != instruction_set.end()) {
            return &(instruction_code->second); //Extrai e retorna o ponteiro para as informações da instrução
        } else {
            std::cout << "Erro - A instruçāo \"" << name << "\" nāo existe\n";
            std::exit(EXIT_FAILURE);
        }
    }
    return nullptr;
}
