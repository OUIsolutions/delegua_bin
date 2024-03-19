
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




    DtwTree *tree = dtw.tree.newTree();
    UniversalGarbage_add(garbage,dtw.tree.free,tree);

    dtw.tree.add_tree_from_hardware(tree,DELEGUA_SOURCE, &(DtwTreeProps){
                    .content = DTW_INCLUDE,
                    .hadware_data=DTW_HIDE,
                    .path_atributes=DTW_INCLUDE
    });

    char *result  = dtw.tree.dumps_json_tree(tree, &(DtwTreeProps){
                    .minification = DTW_NOT_MIMIFY,
                    .ignored_elements=DTW_HIDE,
                    .content = DTW_INCLUDE,
                    .hadware_data=DTW_HIDE,
                    .path_atributes=DTW_INCLUDE
    });
    
    UniversalGarbage_add_simple(garbage,result);
    int tamanho_result = strlen(result);

    stack.format(texto_final,"char %s[%d] = {",NOME_ARVORE,tamanho_result+1);

    for(int i = 0;  i < tamanho_result -1; i++){
        stack.format(texto_final,"%d ,",result[i]);
    }
    stack.format(texto_final,"%d,0 };\n",result[tamanho_result-1]);

    char *delegua_start_script = dtw.load_string_file_content(DELEGUA_SCRIPT_PATH);
    UniversalGarbage_add_simple(garbage,delegua_start_script);
    
    int tamanho_script = strlen(delegua_start_script);

    stack.format(texto_final,"char %s[%d] = {",DELEGUA_SCRIPT_VAR,tamanho_script+1);
    
     for(int i = 0;  i < tamanho_script -1; i++){
        stack.format(texto_final,"%d ,",delegua_start_script[i]);
    }
    stack.format(texto_final,"%d,0 };\n",delegua_start_script[tamanho_script-1]);

    dtw.write_string_file_content(SAIDA,texto_final->rendered_text);
    UniversalGarbage_free(garbage);
}