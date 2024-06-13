#ifndef REGISTERS_H
#define REGISTERS_H
#include <unordered_map>
#include <string>
#define SET_R(key, value) {key, value}, {std::to_string(value), value},

enum Registers {
    ZERO,
    AT,
    V0, V1,
    A0, A1, A2, A3,
    T0, T1, T2, T3, T4, T5, T6, T7,
    S0, S1, S2, S3, S4, S5, S6, S7,
    T8, T9,
    K0, K1,
    GP,
    SP,
    FP,
    RA
};

inline std::unordered_map<std::string, Registers> const registers_table{
    SET_R("zero", ZERO)
    SET_R("at", AT)
    SET_R("v0", V0) SET_R("v1", V1)
    SET_R("a0", A0) SET_R("a1", A1) SET_R("a2", A2) SET_R("a3", A3)
    SET_R("t0", T0) SET_R("t1", T1) SET_R("t2", T2) SET_R("t3", T3) SET_R("t4", T4) SET_R("t5", T5) SET_R("t6", T6) SET_R("t7", T7) SET_R("t8", T8) SET_R("t9", T9)
    SET_R("s0", S0) SET_R("s1", S1) SET_R("s2", S2) SET_R("s3", S3) SET_R("s4", S4) SET_R("s5", S5) SET_R("s6", S6) SET_R("s7", S7)
    SET_R("k0", K0) SET_R("k1", K1)
    SET_R("gp", GP)
    SET_R("sp", SP)
    SET_R("fp", FP)
    SET_R("ra", RA)
};

Registers get_register(std::string&);

#endif
