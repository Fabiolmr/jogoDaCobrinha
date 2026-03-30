all: 
	@gcc *.c player/*.c cenario/*.c acoes/*.c -Wall -pedantic-errors -I./player -I./cenario -I./acoes -o exe -lm

run: all
	./exe