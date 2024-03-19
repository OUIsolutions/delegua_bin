
#include "../dependencies/CTextEngine.h"
#include "../dependencies/doTheWorld.h"
#include "../dependencies/UniversalGarbage.h"

#include "constants.h"
DtwNamespace dtw ;
CTextStackModule stack;
int main(){
    dtw = newDtwNamespace();
    stack = newCTextStackModule();
    UniversalGarbage *garbage = newUniversalGarbage();

    CTextStack *texto_final = stack.newStack_string_empty();
    UniversalGarbage_add(garbage,stack.free,texto_final);

    DtwHash *hash = dtw.hash.newHash();
    UniversalGarbage_add(garbage,dtw.hash.free,hash);

    dtw.hash.digest_folder_by_content(hash,DELEGUA_SOURCE);

    stack.format(texto_final,"const char * %s = \"%s\";\n",ASSINATURA,hash->hash);

    dtw.write_string_file_content(SAIDA,texto_final->rendered_text);

    UniversalGarbage_free(garbage);
/*
    DtwTree *tree = dtw.tree.newTree();
    dtw.tree.add_tree_from_hardware(tree,DELEGUA_SOURCE, &(DtwTreeProps){
                    .content = DTW_INCLUDE,
                    .hadware_data=DTW_HIDE,
                    .path_atributes=DTW_INCLUDE
    });

    dtw.tree.dumps_json_tree_to_file(tree,"a.json",)
*/
}