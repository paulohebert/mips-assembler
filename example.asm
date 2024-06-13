main:
    # Teste das instruções R #
    add $s0, $s1, $s2
    sub $a0, $s0, $s1
    and $t0, $a0, $a1
    or $t1, $s0, $a0
    xor $s0, $s0, $zero
    slt $t0, $s0, $s1
    jr $ra
    # Teste das instruções I #
    addi $a0, $zero, -1
    beq $a0, $s0, exit
    bne $t0, $zero, main
    lw $s7, 4($sp)
    sw $s0, 4($sp)
    # Teste das instruções J #
    jal main
    j exit
    # Outros Testes #
    ADD $s0, $a0, $zero #Com letras maiúsculas
    or $4, $8, $9 #Com a numeração do registrador
    addi $s0, $0, 0xfff #Com um valor em hexadecimal
    addi $a0, $0, 010 #Com um valor em octal
exit: