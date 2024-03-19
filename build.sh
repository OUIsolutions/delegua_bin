echo "adicionando data" 

gcc build/main.c && ./a.out
echo "compilando iso" 

gcc src/main.c -o install.o
echo "removendo lixo"
rm  src/delegua_source.h