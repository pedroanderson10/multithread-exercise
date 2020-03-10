#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <time.h>
#include "SO1_bi.h"

struct NODE {
  int chave;
  struct NODE* prox;
};

typedef struct NODE NO;

struct FilaEncadeada {
  NO cabeca;
  NO* prim;
  NO* ult;
  int card;
};
typedef struct FilaEncadeada FilaEnc;

FilaEnc F;

int main() {
   printf("     TRABALHO DE SO     \n");
   criarFila(&F);
   criar_threads();
   imprimir(F);
   printf("\nPRIMEIRO : %d\n", F.prim->chave);
   printf("ULTIMO : %d\n", F.ult->chave);


   int t;
   printf("\nInsira quantidade de threads com que deseja ordenar a fila (1, 2 ou 4) : \n");
   scanf("%d", &t);

   if     (t == 1) ordenar_1thread();
   else if(t == 2) ordenar_2thread();
   else if(t == 4) ordenar_4thread();

   salvar_arquivo();

   return 0;
}
