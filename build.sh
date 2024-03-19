echo "adicionando data" 

clang build/main.c && ./a.out
echo "compilando iso" 

clang src/main.c -o install.o
echo "removendo lixo"
rm  src/delegua_source.h