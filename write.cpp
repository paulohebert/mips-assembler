#include <iostream> //std::cout
#include <fstream> //std::ofstream
#include <string> //std::string
#include <queue> //Fila
#include <bitset> //std::bitset

void write(std::string const& name, std::queue<std::bitset<32>>& instructions) {
    std::ofstream outfile{name}; //Cria e abre o arquivo de saída
    if(outfile.good()) {
        std::bitset<32> bits, last = instructions.back();
        /* Percorre a fila de instruções binárias */
        while (!instructions.empty()) {
            bits = instructions.front(); //Salva o elemento que está no começo da fila
            int size = 32; //O número de bits em cada instrução
            /* Percorre os bits da instrução */
            while (size--) {
                outfile << bits[size]; //Inseri o bit no arquivo
                /*Quebra linha a cada 8 bits caso não seja o último bit da última instrução */
                if(size % 8 == 0 && !(size == 0 && bits == last)) {
                    outfile << '\n';
                }
            }
            instructions.pop(); //Tira o primeiro elemento da fila
        }
    } else {
        std::cout << "Erro - O arquivo \"" << name << "\" não pode ser criado\n";
        std::exit(EXIT_FAILURE);
    }
}
