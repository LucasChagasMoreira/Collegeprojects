all: tp.o ordenacao.o
	@gcc tp.o ordenacao.o -o exe -lm  -Wall 
	rm -r *.o
ordenacao.o: ordenacao.c
	@gcc ordenacao.c -c -Wall 
tp.o: tp.c
	@gcc tp.c -c -Wall
run:
	@./exe