#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

struct NODE {
  int chave;
  struct NODE* prox;
};

typedef struct NODE NO;

struct FilaEncadeada {
  NO cabeca;
  NO* prim;
  NO* ult;
  NO* ant;
  int card;
};
typedef struct FilaEncadeada FilaEnc;

void criarFila(FilaEnc *F) {
   F->card = 0;
   F->ult = NULL;
   F->ant = NULL;
   F->cabeca.prox = NULL;
}

FilaEnc F;
pthread_mutex_t count_mutex = PTHREAD_MUTEX_INITIALIZER;
int cont = 0;

void incluir_fila(FilaEnc *F,int x) {
   NO* novo = NULL;

   novo = (NO*) malloc(sizeof(NO));
   novo->chave = x;
   novo->prox = NULL;

   if(F->cabeca.prox == NULL){
      F->cabeca.prox = novo;
      //F->ant = F->cabeca;
   }else{
     //F->ant = F->ult;
     F->ult->prox = novo;
   }

   F->prim = F->cabeca.prox;
   F->ult = novo;
   (F->card)++;
}

void imprimir(FilaEnc F) {
  printf("VALORES INSERIDOS NA FILA : \n");
  NO* p = F.cabeca.prox;

  if(p == NULL) printf("FILA VAZIA\n");

  while(p != NULL){
    if     (p->chave < 10  ) printf("000%d ", p->chave);
    else if(p->chave < 100 ) printf("00%d " , p->chave);
    else if(p->chave < 1000) printf("0%d "  , p->chave);
    else                     printf("%d "   , p->chave);
    p = p->prox;
  }

   printf("\n");
}

void limpar_fila(){
  NO* no = F.prim;
  NO* aux = NULL;

  while(no != NULL){
    aux = no;
    no = no->prox;
    free(aux);
    F.card = F.card - 1;
  }
  F.cabeca.prox = NULL;
}

void *bubble(void *arg){
  NO *i,*j;
  int *valor = (int*)(arg);
  int aux;
  //printf("utlizando thread %d\n",valor);
  pthread_mutex_lock(&count_mutex);
  for(i = F.prim; i->prox != NULL; i = i->prox){
    //pthread_mutex_lock(&count_mutex);
    for(j = i->prox; j != NULL; j = j->prox){
      if(i->chave > j->chave){
        aux = i->chave;
        i->chave = j->chave;
        j->chave = aux;
      }
    }
    //pthread_mutex_unlock(&count_mutex);
  }
  pthread_mutex_unlock(&count_mutex);
}

void *receber_arquivo(void *arg) {

    char valores[5];

    int *valor = (int*)(arg);
    FILE *pont_arq;


    pthread_mutex_lock(&count_mutex);
      if(*valor == 0){
        printf("Executando thread 0...\n");
        pont_arq = fopen("arquivo0.bin", "rb");
      }if(*valor == 1){
        printf("Executando thread 1...\n");
        pont_arq = fopen("arquivo1.bin", "rb");
      }if(*valor == 2){
        printf("Executando thread 2...\n");
        pont_arq = fopen("arquivo2.bin", "rb");
      }if(*valor == 3){
        printf("Executando thread 3...\n");
        pont_arq = fopen("arquivo3.bin", "rb");
      }if(*valor == 4){
        printf("Executando thread 4...\n");
        pont_arq = fopen("arquivo4.bin", "rb");
      }if(*valor == 5){
        printf("Executando thread 5...\n");
        pont_arq = fopen("arquivo5.bin", "rb");
      }if(*valor == 6){
        printf("Executando thread 6...\n");
        pont_arq = fopen("arquivo6.bin", "rb");
      }if(*valor == 7){
        printf("Executando thread 7...\n");
        pont_arq = fopen("arquivo7.bin", "rb");
      }if(*valor == 8){
        printf("Executando thread 8...\n");
        pont_arq = fopen("arquivo8.bin", "rb");
      }if(*valor == 9){
        printf("Executando thread 9...\n");
        pont_arq = fopen("arquivo9.bin", "rb");
      }
      if(pont_arq == NULL){
        printf("Não foi possível abrir o arquivo\n");
      }
        //printf("%s inserindo na lista\n", msg);

      while(fgets(valores, 5, pont_arq) != NULL){
        incluir_fila(&F, atoi(valores));
        cont++;
      }

    fclose(pont_arq);
    printf("CONTADOR = %d\n", cont);
    pthread_mutex_unlock(&count_mutex);
}

void criar_threads(){
  pthread_t t0,t1,t2,t3,t4,t5,t6,t7,t8,t9;
  int a0 = 0, a1 = 1, a2 = 2, a3 = 3, a4 = 4, a5 = 5, a6 = 6, a7 = 7, a8 = 8, a9 = 9;

  pthread_create(&t0, NULL, receber_arquivo, (void*)(&a0) );
  pthread_create(&t1, NULL, receber_arquivo, (void*)(&a1) );
  pthread_create(&t2, NULL, receber_arquivo, (void*)(&a2) );
  pthread_create(&t3, NULL, receber_arquivo, (void*)(&a3) );
  pthread_create(&t4, NULL, receber_arquivo, (void*)(&a4) );
  pthread_create(&t5, NULL, receber_arquivo, (void*)(&a5) );
  pthread_create(&t6, NULL, receber_arquivo, (void*)(&a6) );
  pthread_create(&t7, NULL, receber_arquivo, (void*)(&a7) );
  pthread_create(&t8, NULL, receber_arquivo, (void*)(&a8) );
  pthread_create(&t9, NULL, receber_arquivo, (void*)(&a9) );

  pthread_join(t0, NULL);
  pthread_join(t1, NULL);
  pthread_join(t2, NULL);
  pthread_join(t3, NULL);
  pthread_join(t4, NULL);
  pthread_join(t5, NULL);
  pthread_join(t6, NULL);
  pthread_join(t7, NULL);
  pthread_join(t8, NULL);
  pthread_join(t9, NULL);

}

void ordenar_1thread(){
  long int inicio, fim;
  pthread_t t0;
  int a0 = 0;

    //ORDENAÇÃO 1 thread
  inicio = clock();
  pthread_create(&t0, NULL, bubble, (void*)(&a0) );
  pthread_join(t0, NULL);
  fim = clock();
  //printf("Tempo final : %.2lf segundos\n", (double)(fim-inicio)/1000000);

  imprimir(F);
  printf("\nTempo final : %.2lf segundos\n", (double)(fim-inicio)/1000000);
  printf("PRIMEIRO : %d\n", F.prim->chave);
  printf("ULTIMO : %d\n", F.ult->chave);

}

void ordenar_2thread(){
  long int inicio, fim;
  pthread_t t0,t1;
  int a0 = 0, a1 = 1;

   //ORDENAÇÃO 2 threads
  inicio = clock();
  pthread_create(&t0, NULL, bubble, (void*)(&a0) );
  pthread_create(&t1, NULL, bubble, (void*)(&a1) );
  pthread_join(t0, NULL);
  pthread_join(t1, NULL);
  fim = clock();
  //printf("Tempo final : %.2lf segundos\n", (double)(fim-inicio)/1000000);

  imprimir(F);
  printf("\nTempo final : %.2lf segundos\n", (double)(fim-inicio)/1000000);
  printf("PRIMEIRO : %d\n", F.prim->chave);
  printf("ULTIMO : %d\n", F.ult->chave);
}

void ordenar_4thread(){
  long int inicio, fim;
  pthread_t t0,t1,t2,t3;
  int a0 = 0, a1 = 1, a2 = 2, a3 = 3;

    //ORDENAÇÃO 4 threads
  inicio = clock();
  pthread_create(&t0, NULL, bubble, (void*)(&a0) );
  pthread_create(&t1, NULL, bubble, (void*)(&a1) );
  pthread_create(&t2, NULL, bubble, (void*)(&a2) );
  pthread_create(&t3, NULL, bubble, (void*)(&a3) );
  pthread_join(t0, NULL);
  pthread_join(t1, NULL);
  pthread_join(t2, NULL);
  pthread_join(t3, NULL);
  fim = clock();
  //printf("Tempo final : %.2lf segundos\n", (double)(fim-inicio)/1000000);

  imprimir(F);
  printf("\nTempo final : %.2lf segundos\n", (double)(fim-inicio)/1000000);
  printf("PRIMEIRO : %d\n", F.prim->chave);
  printf("ULTIMO : %d\n", F.ult->chave);

}

void salvar_arquivo() {
  NO* p = F.prim;
  //printf("CHAVE : %d", p->chave);

  FILE *pont_arq = fopen("output.bin","wb");

  while(p != NULL){
    int x = p->chave;
    if     (x < 10  ) fprintf(pont_arq, "000%d", x);
    else if(x < 100 ) fprintf(pont_arq, "00%d" , x);
    else if(x < 1000) fprintf(pont_arq, "0%d"  , x);
    else              fprintf(pont_arq, "%d"   , x);
    p = p->prox;
  }

  fclose(pont_arq);

   printf("\n");
}
