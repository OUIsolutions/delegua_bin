
// Códigos ANSI para cores de texto
#define VERMELHO   "\x1b[31m"
#define VERDE "\x1b[32m"
#define AMARELO "\e[0;33m"
#define RESET "\x1b[0m"

#include "../dependencies/CTextEngine.h"
#include "../dependencies/doTheWorld.h"
#include "../dependencies/UniversalGarbage.h"
#include "delegua_source.h"
#include "constants.h"

DtwNamespace dtw;
CTextStackModule stack;

int main() {
    dtw = newDtwNamespace();
    stack = newCTextStackModule();

   if (geteuid() != 0) {
        printf(VERMELHO "Você precisa rodar esse código com sudo \n"RESET);
        return 1;
    } 
    UniversalGarbage *garbage = newUniversalGarbage();

    printf(VERMELHO "removendo elementos anteriores\n" RESET);
    dtw.remove_any(PASTA_DELEGUA);
    dtw.remove_any(STARTER_SCRIPT);




    DtwTransaction *transacao = dtw.transaction.newTransaction();
    UniversalGarbage_add(garbage, dtw.transaction.free, transacao);
  
    
    for (int i = 0; i < DELEGUA_TAMANHO; i++) {
        char *caminho =  DELEGUA_SOURCE_CAMINHOS[i];
        unsigned char *conteudo = DELEGUA_SOURCE[i];
        bool e_binario = DELEGUA_SOURCE_SAO_BINARIOS[i];
        long tamanho = DELEGUA_SOURCE_TAMANHOS[i];


        dtw.transaction.write_any(transacao, caminho, conteudo, tamanho, e_binario);
    }
    printf(VERDE"escrevendo transacao\n");
    dtw.transaction.commit(transacao, SAIDA_DELEGUA);

    printf(VERDE"adicionando ponto de start\n");

    dtw.write_string_file_content(STARTER_SCRIPT, DELEGUA_START);

    printf(VERDE "dando permissão de execução\n");

    system(PERMISSAO_START);
    system(PERMISSAO_NODE);
    UniversalGarbage_free(garbage);
    printf(VERDE"delegua instalado com sucesso\n");
    printf(VERDE"rode com: delegua_bin *argumentos \n");

    printf(RESET);
    return 0;
}
