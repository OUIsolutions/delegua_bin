
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


    //DELEGUA_SOURCE

    DtwStringArray * listage = dtw.list_files_recursively(DELEGUA_SOURCE,true);
    UniversalGarbage_add(garbage,dtw.string_array.free,listage);

    stack.format(texto_final,"int %s = %d;\n",NOME_ARVORE_TOTAL,listage->size);


    CTextStack * caminhos = stack.newStack_string_empty();
    UniversalGarbage_add(garbage,stack.free,caminhos);
    stack.format(caminhos,"char *%s[] = (char*[]){",NOME_ARVORE_CAMINHO);

    CTextStack *tamanhos = stack.newStack_string_empty();
    UniversalGarbage_add(garbage,stack.free,tamanhos);
    stack.format(tamanhos,"int %s[] = (int[]){",NOME_ARVORE_TAMANHO);
   
    CTextStack *sao_binarios = stack.newStack_string_empty();
    UniversalGarbage_add(garbage,stack.free,sao_binarios);
    stack.format(sao_binarios,"bool %s[] = (bool[]){",NOME_ARVORE_SAO_BINARIOS);


    unsigned char *conteudo = NULL;
    UniversalGarbage_add_simple(garbage,conteudo);


    for(int i = 0; i < listage->size; i++){

        stack.format(caminhos,"\"%s\",",listage->strings[i]);
        
        bool e_binario = false;
        long tamanho = 0;
        conteudo = dtw.load_any_content(listage->strings[i],&tamanho,&e_binario);
        UniversalGarbage_resset(garbage,conteudo);

        stack.format(tamanhos,"%d,",tamanho);
        stack.format(sao_binarios,"%s,","true");
    } 
       
   
    stack.self_substr(caminhos,0,-2);
    stack.format(caminhos,"};\n");


    
    stack.format(texto_final,"%t",caminhos);
   // stack.format(texto_final,"%t",caminhos);
    //stack.format(texto_final,"%t",sao_binarios);

 


    char *delegua_start_script = dtw.load_string_file_content(DELEGUA_SCRIPT_PATH);
    UniversalGarbage_add_simple(garbage,delegua_start_script);
    
    int tamanho_script = strlen(delegua_start_script);
   
    stack.format(texto_final,"const char *%s = \"",DELEGUA_SCRIPT_VAR);


    
    for(int i; i < tamanho_script; i++ ){
        printf("tamanho: %d\n",tamanho_script);
        UniversalGarbage_free(garbage);
        return 0;    

        char parseado[20] ={0};
        sprintf(parseado,"\\x%X",(unsigned char)delegua_start_script[i]);    
        stack.format(texto_final,"%s",parseado);
    }
    

    stack.format(texto_final,"\";\n");

 
    dtw.write_string_file_content(SAIDA,texto_final->rendered_text);
    UniversalGarbage_free(garbage);
}