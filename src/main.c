
#include "../dependencies/CTextEngine.h"
#include "../dependencies/doTheWorld.h"
#include "../dependencies/UniversalGarbage.h"
#include "delegua_source.h"
#include "constants.h"

DtwNamespace dtw ;
CTextStackModule stack;
int main(){
    dtw = newDtwNamespace();
    stack = newCTextStackModule();
    UniversalGarbage *garbage = newUniversalGarbage();

    DtwTree *tree = dtw.tree.newTree();
    UniversalGarbage_add(garbage,dtw.tree.free,tree);

    DtwTransaction *transacao = dtw.transaction.newTransaction();
    UniversalGarbage_add(garbage,dtw.transaction.free,transacao);

    dtw.tree.loads_json_tree(tree,DELEGUA_SOURCE);
    for(int i = 0; i < tree->size;i++){
        

        DtwTreePart *part = tree->tree_parts[i];
        char *path = dtw.path.get_path(part->path);
        if(!part->content_exist_in_memory){
            continue;
        }

        printf("adicionando a transação: %s\n",path);      
        dtw.transaction.write_any(transacao,path,part->content,part->content_size,part->is_binary);
    }
    printf("escrevendo transacao\n");
    dtw.transaction.commit(transacao,SAIDA_DELEGUA);
    
    UniversalGarbage_free(garbage);
}