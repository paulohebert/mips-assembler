Compilar:
g++ main.cpp read.cpp registers.cpp label.cpp instructions.cpp write.cpp encode.cpp -std="c++17" -o assembler


Executar:
 ./assembler example.asm memory.mif
 ./assembler [arquivo de entrada] [arquivo de saida]