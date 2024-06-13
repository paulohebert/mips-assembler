#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H
#include <unordered_map>
#include <string>
#define SET(str, code, format) {str, {code, format}},

enum FORMAT { R, I, J};

struct Instruction_R {
    int rd, rs, rt, func;
};

struct Instruction_I {
    int op, rs, rt, imm;
    std::unordered_map<std::string, long int>::pointer label;
};

struct Instruction_J {
    int op;
    std::unordered_map<std::string, long int>::pointer label;
};

struct Instruction {
    union {
        Instruction_R r;
        Instruction_I i;
        Instruction_J j;
    };
    long int address;
    FORMAT format;
};

struct Instruction_Code {
    union {
        int opcode, func;
    };
    FORMAT format;
};

/* Tabela hash contendo os nomes das instruções com seu respectivo valor e formato */
inline std::unordered_map<std::string, Instruction_Code> const instruction_set{
    SET("add", 32, R) SET("addi", 8, I) SET("sub", 34, R)
    SET("and", 36, R) SET("or", 37, R) SET("xor", 38, R)
    SET("beq", 4, I) SET("bne", 5, I) SET("j", 2, J) SET("jal", 3, J) SET("jr", 8, R)
    SET("slt", 42, R)
    SET("lw", 35, I) SET("sw", 43, I)
};

Instruction syntax_R(std::string&, int, long int);

Instruction syntax_I(std::string&, int, long int, std::unordered_map<std::string, long int>&);

Instruction syntax_J(std::string&, int, long int, std::unordered_map<std::string, long int>&);

Instruction_Code const* get_instruction(std::string&);

#endif