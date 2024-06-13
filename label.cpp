#include <iostream> //std::cout
#include <string> //std::string
#include <algorithm> //std::find, std::find_if
#include <cstdlib> //std::exit
#include <cctype>  //std::isalpha, std::isalnum, std::isspace
#include <unordered_map> //Tabela Hash

/* Verifica se há algum caractere inválido no label */
bool valid_label(std::string const& label) {
    for (char const& c : label) {
        if(!std::isalnum(c) && c != '_') return false;
    }
    return true;
}

bool beg_label(char const& ch) {
    return std::isalpha(ch) || ch == '_'; //Retorna verdadeiro caso o caractere seja uma letra alfabetica ou "_"
}

/* Busca e retorna um ponteiro para o local onde o label está armazenado na tabela de símbolos */
std::unordered_map<std::string, long int>::pointer address_label(std::string& str, std::unordered_map<std::string, long int>& symbols_table) {
    auto begin = std::find_if(str.begin(), str.end(), beg_label); //Ponteiro para o início do label
    if(begin != str.end()) {
        auto end = std::find(begin, str.end(), ' '); //Ponteiro para o próximo caractere após o fim do label
        std::string label{begin, end}; //Cria o label
        str.erase(begin, end); //Apaga o label da linha
        if(valid_label(label)) {
            auto it_label = symbols_table.find(label);
            /* Verifica se o label já foi declarado antes de ser utilizado pela instrução */
            if(it_label == symbols_table.end()){
                symbols_table[label] = -1; //Adiciona o label na tabela de símbolos com um endereço temporário
                it_label = symbols_table.find(label); //Atualiza o iterador depois da criação do label
            }
            return &(*it_label); //Converte o iterador em ponteiro e retorna o local onde o label está armazenado
        }
        /* Encerra o programa caso o label seja inválido */
        std::cout << "Erro - O label \"" << label << "\" nāo é válido\n";
        std::exit(EXIT_FAILURE);
    }
    /* Encerra o programa caso o label da instrução não seja encontrado */
    std::cout << "Erro - Label nāo encontrado\n";
    std::exit(EXIT_FAILURE);
}

std::string get_label(std::string& str) {
    std::string label;
    auto end = std::find(str.begin(), str.end(), ':'); //Busca e retorna o ponteiro para o caracter ":"
    /* Verifica se foi encontrado o caractere ":", caso o ponteiro não aponte para o último elemento da string */
    if(end != str.end()) {
        auto begin = std::find_if(str.begin(), end, beg_label); //Busca o ponteiro para o início do label
        label = std::string(begin, end); //Cria o label a partir dos ponteiro de início e fim
        /* Verifica se é um label inválido */
        if(!valid_label(label)){
            std::cout << "Erro - O label \"" << label << "\" nāo é válido\n";
            std::exit(EXIT_FAILURE);
        }
        str.erase(begin, end + 1); //Apaga o "label:" da linha
        /* Verifica se tem algum elemento antes do label */
        for (auto ch = str.begin(); ch != begin; ch++) {
            if (!std::isspace(*ch)) {
                std::cout << "Erro - Sintaxe inválida\n";
                std::exit(EXIT_FAILURE);
            }
        }
    }
    return label;
}