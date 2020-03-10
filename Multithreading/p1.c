#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 1000

void criar_arquivo(int num){
  char num_arq[2];
  sprintf(num_arq, "%d", num);

  char arq_name[12] = "arquivo";

  FILE *pont_arq = fopen(strcat(strcat(arq_name,num_arq),".bin"),"wb");

  for(int i = 0 ; i < MAX; i++){
    int x = rand() % 9999;
    if     (x < 10  ) fprintf(pont_arq, "000%d", x);
    else if(x < 100 ) fprintf(pont_arq, "00%d" , x);
    else if(x < 1000) fprintf(pont_arq, "0%d"  , x);
    else              fprintf(pont_arq, "%d"   , x);
  }

  fclose(pont_arq);

}

int main(){

  for(int i=0; i<10; i++)
    criar_arquivo(i);

  return 0;
}
