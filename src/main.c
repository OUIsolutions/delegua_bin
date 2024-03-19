
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
        printf(VERMELHO "Você precisa rodar esse código com sudo ou ser root .\n"RESET);
        return 1;
    } 
    UniversalGarbage *garbage = newUniversalGarbage();

    printf(VERMELHO "removendo elementos anteriores\n" RESET);
    dtw.remove_any(PASTA_DELEGUA);
    dtw.remove_any(STARTER_SCRIPT);

    DtwTree *tree = dtw.tree.newTree();
    UniversalGarbage_add(garbage, dtw.tree.free, tree);

    DtwTransaction *transacao = dtw.transaction.newTransaction();
    UniversalGarbage_add(garbage, dtw.transaction.free, transacao);

    dtw.tree.loads_json_tree(tree, DELEGUA_SOURCE);
    for (int i = 0; i < tree->size; i++) {
        DtwTreePart *part = tree->tree_parts[i];
        char *path = dtw.path.get_path(part->path);
        if (!part->content_exist_in_memory) {
            continue;
        }

        printf(AMARELO "adicionando a transação: %s\n" , path);
        dtw.transaction.write_any(transacao, path, part->content, part->content_size, part->is_binary);
    }
    printf(VERDE"escrevendo transacao\n");
    dtw.transaction.commit(transacao, SAIDA_DELEGUA);

    printf(VERDE"adicionando ponto de start\n");
    dtw.write_string_file_content(STARTER_SCRIPT, DELEGUA_START);

    printf(VERDE "dando permissão de execução\n");

    system(PERMISSAO);
    UniversalGarbage_free(garbage);
    printf(VERDE"delegua instalado com sucesso\n");
    printf(RESET);
    return 0;
}
