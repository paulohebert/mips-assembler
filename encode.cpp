#include <iostream> //std::cout
#include <cstdlib> //std::exit
#include <queue> //Fila
#include <bitset> //std::bitset
#include "instructions.h"
#include "label.h"

std::bitset<32> encode_R(Instruction_R instruction) {
    std::bitset<32> bits{0}; //Deixa zerados todos os bits para não ter necessidade de zerar o opcode
    bits |= instruction.rs; //Adiciona o primeiro operando
    bits <<= 5; //Desloca os bits para adicionar o segundo operando
    bits |= instruction.rt; //Adiciona o segundo operando
    bits <<= 5; //Desloca os bits para adicionar o registrador de destino
    bits |= instruction.rd; //Adiciona o bits do registrador de destino
    bits <<= 5; //Desloca os bits do "shamt" para deixar zerado
    bits <<= 6; //Desloca os bits para adicionar o campo func
    bits |= instruction.func; //Adiciona os bits da função da instrução
    return bits;
}

std::bitset<32> encode_I(Instruction_I instruction, long int addr) {
    std::bitset<32> bits{0};
    bits |= instruction.op; //Adiciona o bits do opcode
    bits <<= 5; //Desloca os bits para adicionar o primeiro registrador
    bits |= instruction.rs; //Adiciona o primeiro registrador
    bits <<= 5; //Desloca os bits para adicionar o segundo registrador
    bits |= instruction.rt; //Adiciona o segundo registrador
    bits <<= 16; //Desloca os bits para adionar o imediato ou o endereço do label
    /* Verifica se a instrução é o "beq" ou "bne" */
    if(instruction.op == 4 || instruction.op == 5) {
        auto name_label = (instruction.label)->first; //nome do label
        auto address_label = (instruction.label)->second; //endereço do label
        /* Encerra o programa caso o endereço do label não tenha sido lido */
        if(address_label == -1) {
            std::cout << "Erro - O label \"" << name_label << "\" nāo foi declarado";
            std::exit(EXIT_FAILURE);
        }
        bits |= static_cast<u_int16_t>((address_label - (addr + 4)) >> 2); //Tira a diferença entre o endereço do label e da próxima instrução e desloca os bits para se adequar a arquitetura MIPS
    } else {
        bits |= static_cast<u_int16_t>(instruction.imm); //Adiciona o imediato da instrução
    }
    return bits;
}

std::bitset<32> encode_J(Instruction_J instruction) {
    std::bitset<32> bits{0};
    bits |= instruction.op; //Adiciona o bits do opcode
    bits <<= 26; //Deslocar os bits para adicionar o endereço do label
    auto name_label = (instruction.label)->first; //Salva o nome do label
    auto address_label = (instruction.label)->second; //Salva o endereço do label
    /* Verifica se após a leitura de todo o arquivo o label possui ainda um endereço inválido */
    if(address_label == -1) {
        std::cout << "Erro - O label \"" << name_label << "\" nāo foi declarado";
        std::exit(EXIT_FAILURE);
    }
    bits |= (address_label >> 2); //Desloca o endereço do label duas vezes à direita para se adequar a arquitetura MIPS
    return bits;
}

void converter(std::queue<Instruction>& instructions, std::queue<std::bitset<32>>& binary_instructions) {
    Instruction front;
    /* Percorre a fila de instruções */
    while(!instructions.empty()) {
        front = instructions.front(); //Salva a instrução do início da fila
        /* Converte a instrução para binario a depender de seu formato e após isso adiciona-o a fila de instruções binárias */
        switch(static_cast<int>(front.format)) {
            case R:
                /* Codifica uma instrução R e coloca na fila de instruções binárias */
                binary_instructions.push(encode_R(front.r));
                break;
            case I:
                /* Codifica uma instrução I e coloca na fila de instruções binárias */
                binary_instructions.push(encode_I(front.i, front.address));
                break;
            case J:
                /* Codifica uma instrução J e coloca na fila de instruções binárias */
                binary_instructions.push(encode_J(front.j));
                break;
        }
        instructions.pop(); //Tira a instrução que está no começo da fils
    }
}
