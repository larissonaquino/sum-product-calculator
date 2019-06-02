#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include "Lista.h"

#define MAXSIZE 1000000

Lista * l1;
Lista * l2;
Lista * l3;

char * op1;
char * op2;

void menu();
void operand1();
void operand2();
void convertToInt(Lista * l, char * op);
void showSum(Lista * l1, Lista * l2);
void showProduct();
Lista * clone();

int main() {
	l1 = criar();
	l2 = criar();
	l3 = criar();
	op1 = malloc(MAXSIZE*sizeof(char));
	op2 = malloc(MAXSIZE*sizeof(char));
	//printf("v: %d\n", (int)(19/10)%10);
	operand1();
	operand2();
	
	menu();
	
	destruir(l1);
	destruir(l2);
	destruir(l3);
	free(op1);
	free(op2);
	
	return 0;
}

void operand1(){
	limpar(l3);
	setbuf(stdin, NULL);
	printf("\nOperando 1: ");
	fgets(op1, MAXSIZE, stdin);
	convertToInt(l1, op1);
}

void operand2(){
	limpar(l3);
	setbuf(stdin, NULL);
	printf("\nOperando 2: ");
	fgets(op2, MAXSIZE, stdin);
	convertToInt(l2, op2);
}

void convertToInt(Lista * l, char * op){
	int i;
	char c[3];
	
	limpar(l);
	c[1] = '\0';
	
	for(i = 0; i < strlen(op)-1; i++){
		c[0] = *(op+i);
		inserir_ultimo(l, atoi(c));
	}
}

void showSum(Lista * l1, Lista * l2){
	int i, j;
	int maior = tamanho(l1) >= tamanho(l2) ? tamanho(l1) : tamanho(l2);
	int sum, carriage = 0;
	int val1, val2;
	
	limpar(l3);
	
	for(i = maior, j = 0; i >= 0; i--, j++){			
		//val1 = ler_pos(l1, (tamanho(l1)-1) - j) == -1 ? 0 : ler_pos(l1, (tamanho(l1)-1) - j);
		//val2 = ler_pos(l2, (tamanho(l2)-1) - j) == -1 ? 0 : ler_pos(l2, (tamanho(l2)-1) - j);
		
		val1 = tamanho(l1)-1-j < 0 ? 0 : ler_pos(l1, tamanho(l1)-1-j);
		val2 = tamanho(l2)-1-j < 0 ? 0 : ler_pos(l2, tamanho(l2)-1-j);
		
		sum = val1 + val2 + carriage;
		
		if(sum >= 10){
			inserir_primeiro(l3, sum-10);
			carriage = 1;
		}
		else if(!(i == 0 && sum == 0)){
			inserir_primeiro(l3, sum);
			carriage = 0;
		}		
	}
	
//	while(!ler_pos(l3, 0)){
//		remover_primeiro(l3);
//	}
}

void showProduct(){
	Lista * aux1 = criar();
	Lista * aux2 = criar();
	
	int i, j, last1, last2;
	int prod, carriage = 0;
	int val1, val2;
	
	limpar(l3);
	
	if(tamanho(l1) <= tamanho(l2)){
		
		for(i = tamanho(l1), last1 = 0; i >= 0; i--, last1++){
			val1 = tamanho(l1)-1-last1 < 0 ? 0 : ler_pos(l1, tamanho(l1)-1-last1);
			
			for(j = tamanho(l2), last2 = 0; j >= 0; j--, last2++){
				val2 = tamanho(l2)-1-last2 < 0 ? 0 : ler_pos(l2, tamanho(l2)-1-last2);
				prod = (val1 * val2) + carriage;
				
				if(prod >= 10){
					inserir_primeiro(aux1, prod%10);				
					carriage = (int) (prod/10)%10;
					//if(tamanho(l2) > 2) j++;
				}
				else{
					if(!(j == 0 && prod == 0))
						inserir_primeiro(aux1, prod);
					carriage = 0;
				}
			}
			
			if(!(i < tamanho(l1))){
				aux2 = clone(aux1);
				limpar(aux1);
			}
			else{
				inserir_ultimo(aux1, 0);
				showSum(aux1, aux2);
				aux2 = clone(l3);
				limpar(aux1);
			}
		}
	}
	else{
		for(i = tamanho(l2), last2 = 0; i >= 0; i--, last2++){
			val2 = tamanho(l2)-1-last2 < 0 ? 0 : ler_pos(l2, tamanho(l2)-1-last2);
			
			for(j = tamanho(l1), last1 = 0; j >= 0; j--, last1++){
				val1 = tamanho(l1)-1-last1 < 0 ? 0 : ler_pos(l1, tamanho(l1)-1-last1);
				prod = (val1 * val2) + carriage;
				
				if(prod >= 10){
					inserir_primeiro(aux1, prod%10);				
					carriage = (int) (prod/10)%10;
					//if(tamanho(l2) > 2) j++;
				}
				else{
					if(!(j == 0 && prod == 0))
						inserir_primeiro(aux1, prod);
					carriage = 0;
				}
			}
			
			if(!(i < tamanho(l2))){
				aux2 = clone(aux1);
				limpar(aux1);
			}
			else{
				inserir_ultimo(aux1, 0);
				showSum(aux1, aux2);
				aux2 = clone(l3);
				limpar(aux1);
			}
		}
	}
	
	while(!ler_pos(l1, 0)){
		remover_primeiro(l1);
	}
	
	while(!ler_pos(l2, 0)){
		remover_primeiro(l2);
	}
		
	showSum(aux1, aux2);

	destruir(aux1);
	destruir(aux2);
}

Lista * clone(Lista * l){
	Lista * cl = criar();
	int i;
	
	for(i = 0; i < tamanho(l); i++){
		inserir_ultimo(cl, ler_pos(l, i));
	}

	return cl;	
}


// ---------------------- MENU PRINCIPAL ----------------------
void menu(){
	
	while(1){
		system("cls");
		
		printf("\n\t ------ UNLIMITED CALCULATOR ------\n\n");
		printf("1 - Definir o valor do operando 1\n");
		printf("2 - Definir o valor do operando 2\n");
		printf("3 - Mostrar soma\n");
		printf("4 - Mostrar produto\n");
		printf("5 - Sair do programa\n");
		
		printf("\nLista 1: ");
		imprimir(l1);
		printf("\nLista 2: ");
		imprimir(l2);
		printf("\nLista 3: ");
		imprimir(l3);
		
		switch(getch()){
			case '1':
				operand1();
				break;
			case '2':
				operand2();
				break;
			case '3':
				showSum(l1, l2);
				break;
			case '4':
				showProduct();
				break;
			case '5':
				printf("\nSaindo...\n");
				exit(1);
				break;
		}
	}
}

