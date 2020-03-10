#ifndef SO1_BI_H
#define SO1_BI_H

struct NODE ;
typedef struct NODE NO;
struct FilaEncadeada;
typedef struct FilaEncadeada FilaEnc;
void criarFila(FilaEnc *F);
void incluir_fila(FilaEnc *F, int x);
void imprimir(FilaEnc F);
void limpar_fila();
void *bubble(void *arg);
void *receber_arquivo(void *arg);
void criar_threads();
void ordenar_1thread();
void ordenar_2thread();
void ordenar_4thread();
void salvar_arquivo();

#endif
