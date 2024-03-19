
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
                    .minification = DTW_MIMIFY,
                    .ignored_elements=DTW_HIDE,
                    .content = DTW_INCLUDE,
                    .hadware_data=DTW_HIDE,
                    .path_atributes=DTW_INCLUDE
    });
    
    UniversalGarbage_add_simple(garbage,result);
    int tamanho_result = strlen(result);


  //  stack.format(texto_final,"const char *%s = \"%sc\";\n",NOME_ARVORE,dtw_base64_encode((unsigned char*)result,tamanho_result));
    stack.format(texto_final,"const char *%s = \"",NOME_ARVORE);

    for(int i; i < tamanho_result; i++ ){
        char parseado[20] ={0};
        sprintf(parseado,"\\x%X",(unsigned char)result[i]);
        stack.format(texto_final,"%s",parseado);
    }

    stack.format(texto_final,"\";\n");



    char *delegua_start_script = dtw.load_string_file_content(DELEGUA_SCRIPT_PATH);
    UniversalGarbage_add_simple(garbage,delegua_start_script);
    
    int tamanho_script = strlen(delegua_start_script);
   
    stack.format(texto_final,"const char *%s = \"",DELEGUA_SCRIPT_VAR);

    for(int i; i < tamanho_script; i++ ){
        char parseado[20] ={0};
        sprintf(parseado,"\\x%X",(unsigned char)delegua_start_script[i]);
        stack.format(texto_final,"%s",parseado);
    }

    stack.format(texto_final,"\";\n");

    
    dtw.write_string_file_content(SAIDA,texto_final->rendered_text);
    UniversalGarbage_free(garbage);
}