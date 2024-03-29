
#include "../dependencies/CTextEngine.h"
#include "../dependencies/doTheWorld.h"
#include "../dependencies/UniversalGarbage.h"

#include "constants.h"
DtwNamespace dtw ;
CTextStackModule stack;

CTextStack * parseia_string_para_hexa(unsigned char *conteudo, int tamanho){
   CTextStack *resultado = stack.newStack_string_empty();
    for(int x =0; x < tamanho; x++){
            char parseado[20] ={0};
        sprintf(parseado,"\\x%X",(unsigned char)conteudo[x]);    
        stack.format(resultado,"%s",parseado);
    }
    return resultado;
}

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

    CTextStack *conteudos = stack.newStack_string_empty();
    UniversalGarbage_add(garbage,stack.free,conteudos);
    stack.format(conteudos,"unsigned  char *%s[] = (unsigned char*[]){",NOME_ARVORE);


    unsigned char *conteudo = NULL;
    UniversalGarbage_add_simple(garbage,conteudo);


    for(int i = 0; i < listage->size; i++){

        stack.format(caminhos,"\"%tc\",",parseia_string_para_hexa(
            listage->strings[i],strlen( listage->strings[i])
        ));
        
        bool e_binario = false;
        long tamanho = 0;
        conteudo = dtw.load_any_content(listage->strings[i],&tamanho,&e_binario);
        UniversalGarbage_resset(garbage,conteudo);

        stack.format(tamanhos,"%d,",tamanho);
        stack.format(sao_binarios,"%b,",e_binario);

        stack.format(conteudos,"\"%tc\",",parseia_string_para_hexa(conteudo,tamanho));

    } 
       
    caminhos->rendered_text[caminhos->size -1] = ' ';
    stack.format(caminhos,"};\n");

    tamanhos->rendered_text[tamanhos->size-1] = ' ';
    stack.format(tamanhos,"};\n");

    
    sao_binarios->rendered_text[sao_binarios->size-1] = ' ';
    stack.format(sao_binarios,"};\n");

    
    conteudos->rendered_text[conteudos->size-1] = ' ';
    stack.format(conteudos,"};\n");

    
    

    stack.format(texto_final,"%t",caminhos);
    stack.format(texto_final,"%t",tamanhos);
    stack.format(texto_final,"%t",sao_binarios);
    stack.format(texto_final,"%t",conteudos);

 


    char *delegua_start_script = dtw.load_string_file_content(DELEGUA_SCRIPT_PATH);
    UniversalGarbage_add_simple(garbage,delegua_start_script);
    
    int tamanho_script = strlen(delegua_start_script);
   
    stack.format(texto_final,"const char *%s = \"%tc\";",DELEGUA_SCRIPT_VAR,parseia_string_para_hexa(
        delegua_start_script, strlen(delegua_start_script)
    ));
    
 
    dtw.write_string_file_content(SAIDA,texto_final->rendered_text);
    UniversalGarbage_free(garbage);
}