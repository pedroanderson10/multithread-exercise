#Makefile Trabalho 1 SO
all: SO

exec: SO
	./SO

SO : principal.o funcao.o
	gcc SO1.o SO1_funcao.o SO1_bi.h -o SO -lpthread

principal.o: SO1.c
	gcc -c SO1.c

funcao.o: SO1_funcao.c
	gcc -c SO1_funcao.c

erro :
	gcc -Wall -c SO1.c SO1_funcao.c

clean:
	rm *.o
